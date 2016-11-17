<br>
####std::string to std::wstring

    string str = "hello world";<br>
    wstring wstr (str.begin(), str.end());

<br>
####char* to std::wstring
  
    char* str = "hello worlddd";<br>
    wstring wstr (str, str+strlen(str));

<br>  
####std::string to wchar_t*

    std::wstring widestr = std::wstring(str.begin(), str.end());<br>
    wchar_t* widecstr = widestr.c_str();

<br>
####visual studio中自己常用快捷键 

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
####SVN

    通过SVN Blame可以看到每行代码具体是谁提交的
    
<br>
####创建DLL需要注意的一些问题

    输出目录：与需要使用这个dll项目的输出目录是否相同
    目标文件名：看整个项目是如何定义其名称（比如GGP中debug就是$(projectName)d，release中是$(projectName)）
    导入库：正确的设置导入库，否则会出现无法打开文件“projectName.lib”的错误
    预处理器：在预处理器的定义中添加该项目的导出 “***_EXPORTS”
    附加库目录：把需要用到的第三方库之类的（放到合适的位置）设置成相对路径，
    
    附加库目录的一般写法是这样的：
    ..\..\Lib\$(platform)\$(configuration) // 这里platform表示win32和x64，configuration表示Debug和Release

<br>
####预定义处理

    如果项目是一个DLL，那么在ProjectNme.h中一般会有预定义处理
    
        #ifdef PROJECTNAME_EXPORTS
            #ifndef PROJECTNAME_PUBLIC
            #define PROJECTNAME_PUBLIC    __declspec(dllexport)
            #endif
        #else
            #ifndef PROJECTNAME_PUBLIC
            #define PROJECTNAME_PUBLIC    __declspec(dllimport)
            #endif
        #endif
    
    如果一个类需要被跨项目使用，这时就需要在定义类时，在类的名字前面加上PROJECTNAME_PUBLIC
    
<br>
####mutable关键字

    mutable是“可变的，易变的”，跟constant（即C++中的const）是反义词。
    在C++中，mutable是为了突破const的限制而设置的。被mutable修饰的变量（mutable只能用于修饰类的非静态数据成员），将永远处于可变的状态，即使是在一个const函数中。
    
<br>
####在父类中析构子类的成员变量所分配的内存

    在父类中增加一个虚函数，给一个空实现，这样就不会影响其他从该类继承的子类，然后在子类中重写该虚函数，内容为析构自身的成员变量。这样在父类的具体函数中调用该虚函数就能够析构子类成员变量所分配的内存。
    

  
