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

  
