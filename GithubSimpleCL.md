1.mkdir tmp 在当前目录下创建一个新的目录tmp
<br>
2.cd tmp 切换到tmp目录下
<br>
3.git init 这里tmp目录作为一个本地仓库，初始库git库
<br>
4.touch test.md 在当前目录下创建文件test.md
<br>
5.git add test.md 将test.md文件增加到本地git库中
<br>
6.git commit -am 'commit' 提交，让上条增加文件命令生效
<br>
7.git remote add 向本地仓库中添加远程仓库地址，远程仓库地址别名是origin
<br>
8.git pull origin master 将orgin所代表的远程仓库地址里的master主干下载到本地仓库，即上传之前先进行一次同步
<br>
9.git push -u origin master 将本地仓库上传到origin所代表的远程仓库的master分支上
<br>
<br>
<br>

mkdir tmp
<br>
cd tmp
<br>
git init
<br>
touch test.md
<br>
git add test.md   (将文件一次性add的命令：git add .)
<br>
git commit -am 'commit'	
<br>
git remote add origin https://github.com/suliutree/SummaryLots  (以本仓库为例)
<br>
git pull origin master
<br>
git push -u origin master
<br>
<br>
<br>
	
	
git config --global user.email "you@example.com"
<br>
git config --global user.name "your name"
