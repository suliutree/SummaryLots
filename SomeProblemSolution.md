<br>
std::string to std::wstring

    string str = "hello world";<br>
    wstring wstr (str.begin(), str.end());

<br>
char* to std::wstring
  
    char* str = "hello worlddd";<br>
    wstring wstr (str, str+strlen(str));

<br>  
std::string to wchar_t*

    std::wstring widestr = std::wstring(str.begin(), str.end());<br>
    wchar_t* widecstr = widestr.c_str();

<br>
 visual studio中自己常用快捷键 

    Shift + Alt + o 查找文件
    Ctrl + - 让光标移动到先前的位置
    Ctrl + + 让光标移动到下一个位置
    Alt + O .h文件与相应的.cpp文件的跳转
    Ctrl + } 匹配大括号
    Ctrl + Shift + } 选中匹配的括号内的文本
    Ctrl + Shift + F9 清除项目中的所有断点
    Ctrl + D，Ctrl + L 显示“局部变量”窗口
    Ctrl + F10 调试过程中运行到光标处
    Ctrl + F3 类似搜索功能
    Shift + F10 调试过程中跳出当前函数

<br>
SVN

    通过SVN Blame可以看到每行代码具体是谁提交的
    
<br>
创建DLL需要注意的一些问题

    输出目录：与需要使用这个dll项目的输出目录是否相同
    目标文件名：看整个项目是如何定义其名称（比如GGP中debug就是$(projectName)d，release中是$(projectName)）
    导入库：正确的设置导入库，否则会出现无法打开文件“projectName.lib”的错误
    预处理器：在预处理器的定义中添加该项目的导出 “***_EXPORTS”
    附加库目录：把需要用到的第三方库之类的（放到合适的位置）设置成相对路径
    

  
