//mp4writer.cpp   
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
#include "mp4writer.h"   
   
/**************************************************************/   
/* video output */   
   
AVFrame *picture, *tmp_picture;   
uint8_t *video_outbuf;   
int frame_count, video_outbuf_size;   
   
/* add a video output stream */   
static AVStream *add_video_stream(AVFormatContext *oc, int codec_id)   
{   
    AVCodecContext *c;   
    AVStream *st;   
   
    st = av_new_stream(oc, 0);   
    if (!st) {   
        fprintf(stderr, "Could not alloc stream\n");   
        exit(1);   
    }   
   
    c = st->codec;   
    c->codec_id = (CodecID)codec_id;   
    c->codec_type = CODEC_TYPE_VIDEO;   
   
    /* put sample parameters */   
    c->bit_rate = 400000;   
    /* resolution must be a multiple of two */   
    c->width = 352;   
    c->height = 288;   
    /* time base: this is the fundamental unit of time (in seconds) in terms  
       of which frame timestamps are represented. for fixed-fps content,  
       timebase should be 1/framerate and timestamp increments should be  
       identically 1. */   
    c->time_base.den = STREAM_FRAME_RATE;   
    c->time_base.num = 1;   
    c->gop_size = 12; /* emit one intra frame every twelve frames at most */   
    c->pix_fmt = STREAM_PIX_FMT;   
    if (c->codec_id == CODEC_ID_MPEG2VIDEO) {   
        /* just for testing, we also add B frames */   
        c->max_b_frames = 2;   
    }   
    if (c->codec_id == CODEC_ID_MPEG1VIDEO){   
        /* needed to avoid using macroblocks in which some coeffs overflow  
           this doesnt happen with normal video, it just happens here as the  
           motion of the chroma plane doesnt match the luma plane */   
        c->mb_decision=2;   
    }   
    // some formats want stream headers to be seperate   
    if(!strcmp(oc->oformat->name, "mp4") || !strcmp(oc->oformat->name, "mov") || !strcmp(oc->oformat->name, "3gp"))   
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;   
   
    return st;   
}   
   
static AVFrame *alloc_picture(int pix_fmt, int width, int height)   
{   
    AVFrame *picture;   
    uint8_t *picture_buf;   
    int size;   
   
    picture = avcodec_alloc_frame();   
    if (!picture)   
        return NULL;   
    size = avpicture_get_size(pix_fmt, width, height);   
    picture_buf = (uint8_t*)malloc(size);   
    if (!picture_buf) {   
        av_free(picture);   
        return NULL;   
    }   
    avpicture_fill((AVPicture *)picture, picture_buf,   
                   pix_fmt, width, height);   
    return picture;   
}   
   
static void open_video(AVFormatContext *oc, AVStream *st)   
{   
    AVCodec *codec;   
    AVCodecContext *c;   
   
    c = st->codec;   
   
    /* find the video encoder */   
    codec = avcodec_find_encoder(c->codec_id);   
    if (!codec) {   
        fprintf(stderr, "codec not found\n");   
        exit(1);   
    }   
   
    /* open the codec */   
    if (avcodec_open(c, codec) < 0) {   
        fprintf(stderr, "could not open codec\n");   
        exit(1);   
    }   
   
    video_outbuf = NULL;   
    if (!(oc->oformat->flags & AVFMT_RAWPICTURE)) {   
        /* allocate output buffer */   
        /* XXX: API change will be done */   
        video_outbuf_size = 200000;   
        video_outbuf = (uint8_t*)malloc(video_outbuf_size);   
    }   
   
    /* allocate the encoded raw picture */   
    picture = alloc_picture(c->pix_fmt, c->width, c->height);   
    if (!picture) {   
        fprintf(stderr, "Could not allocate picture\n");   
        exit(1);   
    }   
   
    /* if the output format is not YUV420P, then a temporary YUV420P  
       picture is needed too. It is then converted to the required  
       output format */   
    tmp_picture = NULL;   
    if (c->pix_fmt != PIX_FMT_YUV420P) {   
        tmp_picture = alloc_picture(PIX_FMT_YUV420P, c->width, c->height);   
        if (!tmp_picture) {   
            fprintf(stderr, "Could not allocate temporary picture\n");   
            exit(1);   
        }   
    }   
}   
   
/* prepare a dummy image */   
static void fill_yuv_image(AVFrame *pict, int frame_index, int width, int height)   
{   
    int x, y, i;   
   
    i = frame_index;   
   
    /* Y */   
    for(y=0;y<height;y++) {   
        for(x=0;x<width;x++) {   
            pict->data[0][y * pict->linesize[0] + x] = x + y + i * 3;   
        }   
    }   
   
    /* Cb and Cr */   
    for(y=0;y<height/2;y++) {   
        for(x=0;x<width/2;x++) {   
            pict->data[1][y * pict->linesize[1] + x] = 128 + y + i * 2;   
            pict->data[2][y * pict->linesize[2] + x] = 64 + x + i * 5;   
        }   
    }   
}   
   
static void write_video_frame(AVFormatContext *oc, AVStream *st)   
{   
    int out_size, ret;   
    AVCodecContext *c;   
   
    c = st->codec;   
   
    if (frame_count >= STREAM_NB_FRAMES) {   
        /* no more frame to compress. The codec has a latency of a few  
           frames if using B frames, so we get the last frames by  
           passing the same picture again */   
    } else {   
        if (c->pix_fmt != PIX_FMT_YUV420P) {   
            /* as we only generate a YUV420P picture, we must convert it  
               to the codec pixel format if needed */   
            fill_yuv_image(tmp_picture, frame_count, c->width, c->height);   
            img_convert((AVPicture *)picture, c->pix_fmt,   
                        (AVPicture *)tmp_picture, PIX_FMT_YUV420P,   
                        c->width, c->height);   
        } else {   
            fill_yuv_image(picture, frame_count, c->width, c->height);   
        }   
    }   
   
   
    if (oc->oformat->flags & AVFMT_RAWPICTURE) {   
        /* raw video case. The API will change slightly in the near  
           futur for that */   
        AVPacket pkt;   
        av_init_packet(&pkt);   
   
        pkt.flags |= PKT_FLAG_KEY;   
        pkt.stream_index= st->index;   
        pkt.data= (uint8_t *)picture;   
        pkt.size= sizeof(AVPicture);   
   
        ret = av_write_frame(oc, &pkt);   
    } else {   
        /* encode the image */   
        out_size = avcodec_encode_video(c, video_outbuf, video_outbuf_size, picture);   
        /* if zero size, it means the image was buffered */   
        if (out_size > 0) {   
            AVPacket pkt;   
            av_init_packet(&pkt);   
   
            pkt.pts= av_rescale_q(c->coded_frame->pts, c->time_base, st->time_base);   
            if(c->coded_frame->key_frame)   
                pkt.flags |= PKT_FLAG_KEY;   
            pkt.stream_index= st->index;   
            pkt.data= video_outbuf;   
            pkt.size= out_size;   
   
            /* write the compressed frame in the media file */   
            ret = av_write_frame(oc, &pkt);   
        } else {   
            ret = 0;   
        }   
    }   
    if (ret != 0) {   
        fprintf(stderr, "Error while writing video frame\n");   
        exit(1);   
    }   
    frame_count++;   
}   
   
static void close_video(AVFormatContext *oc, AVStream *st)   
{   
    avcodec_close(st->codec);   
    av_free(picture->data[0]);   
    av_free(picture);   
    if (tmp_picture) {   
        av_free(tmp_picture->data[0]);   
        av_free(tmp_picture);   
    }   
    av_free(video_outbuf);   
}   
   
/**************************************************************/   
/* media file output */   
void writemp4_init(const char* filename, AVOutputFormat*& fmt, AVFormatContext*& oc, AVStream*& video_st)   
{      
 //   AVOutputFormat *fmt;   
 //   AVFormatContext *oc;   
 //   AVStream *video_st;   
    int i;   
   
    /* initialize libavcodec, and register all codecs and formats */   
    av_register_all();   
   
    /* auto detect the output format from the name. default is  
       mpeg. */   
    fmt = guess_format(NULL, filename, NULL);   
    if (!fmt) {   
        printf("Could not deduce output format from file extension: using MPEG.\n");   
        fmt = guess_format("mpeg", NULL, NULL);   
    }   
    if (!fmt) {   
        fprintf(stderr, "Could not find suitable output format\n");   
        exit(1);   
    }   
   
    /* allocate the output media context */   
    oc = av_alloc_format_context();   
    if (!oc) {   
        fprintf(stderr, "Memory error\n");   
        exit(1);   
    }   
    oc->oformat = fmt;   
    snprintf(oc->filename, sizeof(oc->filename), "%s", filename);   
   
    /* add the audio and video streams using the default format codecs  
       and initialize the codecs */   
    video_st = NULL;      
    if (fmt->video_codec != CODEC_ID_NONE) {   
        video_st = add_video_stream(oc, fmt->video_codec);   
    }     
   
    /* set the output parameters (must be done even if no  
       parameters). */   
    if (av_set_parameters(oc, NULL) < 0) {   
        fprintf(stderr, "Invalid output format parameters\n");   
        exit(1);   
    }   
   
    dump_format(oc, 0, filename, 1);   
   
    /* now that all the parameters are set, we can open the audio and  
       video codecs and allocate the necessary encode buffers */   
    if (video_st)   
        open_video(oc, video_st);   
     
   
    /* open the output file, if needed */   
    if (!(fmt->flags & AVFMT_NOFILE)) {   
        if (url_fopen(&oc->pb, filename, URL_WRONLY) < 0) {   
            fprintf(stderr, "Could not open '%s'\n", filename);   
            exit(1);   
        }   
    }   
   
    /* write the stream header, if any */   
    av_write_header(oc);   
};   
   
void writemp4_release(AVOutputFormat* fmt, AVFormatContext* oc, AVStream* video_st)   
{   
    /* close each codec */   
    if (video_st)   
        close_video(oc, video_st);       
   
    /* write the trailer, if any */   
    av_write_trailer(oc);   
   
    /* free the streams */   
    for(int i = 0; i < oc->nb_streams; i++) {   
        av_freep(&oc->streams[i]->codec);   
        av_freep(&oc->streams[i]);   
    }   
   
    if (!(fmt->flags & AVFMT_NOFILE)) {   
        /* close the output file */   
        url_fclose(&oc->pb);   
    }   
   
    /* free the stream */   
    av_free(oc);   
}; 

http://www.pudn.com/Download/item/id/285939.html
