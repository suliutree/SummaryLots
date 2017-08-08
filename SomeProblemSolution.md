<br>

#### std::string to std::wstring

    string str = "hello world";
    wstring wstr (str.begin(), str.end());

<br>

#### char* to std::wstring
  
    char* str = "hello worlddd";<br>
    wstring wstr (str, str+strlen(str));

<br>  

#### std::string to wchar_t*

    std::wstring widestr = std::wstring(str.begin(), str.end());
    wchar_t* widecstr = widestr.c_str();

<br>

#### visual studio中自己常用快捷键 

    Shift + Alt + o 查找文件
    Ctrl + - 让光标移动到先前的位置
    Ctrl + Shift + - 让光标移动到下一个位置
    Alt + O .h文件与相应的.cpp文件的跳转
    Ctrl + } 匹配大括号
    Ctrl + Shift + } 选中匹配的括号内的文本
    Ctrl + Shift + F9 清除项目中的所有断点
    Ctrl + D，Ctrl + L 显示“局部变量”窗口
    Ctrl + F10 调试过程中运行到光标处
    Ctrl + F3 类似搜索功能
    Shift + F10 调试过程中跳出当前函数

<br>

#### SVN

    通过SVN Blame可以看到每行代码具体是谁提交的
    
<br>

#### 创建DLL需要注意的一些问题

        输出目录：与需要使用这个dll项目的输出目录是否相同
    <br>
        目标文件名：看整个项目是如何定义其名称（比如GGP中debug就是$(projectName)d，release中是$(projectName)）
    <br>
        导入库：正确的设置导入库，否则会出现无法打开文件“projectName.lib”的错误（链接器-高级-导入库）
    <br>
        预处理器：在预处理器的定义中添加该项目的导出 “***_EXPORTS”
    <br>
        附加库目录：把需要用到的第三方库之类的（放到合适的位置）设置成相对路径，
    <br>
        附加库目录的一般写法是这样的：
    <br>
        ..\..\Lib\$(platform)\$(configuration) // 这里platform表示win32和x64，configuration表示Debug和Release

<br>

#### 预定义处理

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

#### mutable关键字

    mutable是“可变的，易变的”，跟constant（即C++中的const）是反义词。
    在C++中，mutable是为了突破const的限制而设置的。被mutable修饰的变量（mutable只能用于修饰类的非静态数据成员），将永远处于可变的状态，即使是在一个const函数中。
    
<br>

#### 在父类中析构子类的成员变量所分配的内存

    在父类中增加一个虚函数，给一个空实现，这样就不会影响其他从该类继承的子类，然后在子类中重写该虚函数，内容为析构自身的成员变量。这样在父类的具体函数中调用该虚函数就能够析构子类成员变量所分配的内存。
    
<br>

#### 判断父类所指向的对象是否是某子类，可以将父类转换成某子类，判断其是否为空

        CVisualNode *pVNode = const_cast<CVisualNode *>(pVisualNode);
        CAxisLabel *pAxisLabel = dynamic_cast<CAxisLabel *>(pVNode);
        if (pAxisLabel != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }

<br>

#### vs2010中各类文件的作用

    vcxproj文件：工程文件，其中描述了工程的各项属性，修改该文件后再重新build时vs会重新build工程
    vcxproj.filter文件：可理解为视图文件，定义了工程在VS中打开后的目录结构，修改该文件后重新build时vs不会重新build工程
    vcxproj.user 是用户的一些相关配置

<br>

#### 调试九法
    
    1.理解系统
   <br>
    2.制造失败
    <br>
    3.不要想，而要看
    <br>
    4.分而治之
    <br>
    5.一次只改一个地方
    <br>
    6.保持审计跟踪
    <br>
    7.检查插头
    <br>
    8.获得全新的观点
    <br>
    9.如果你不修复bug，它将依然存在

<br>

#### 烘焙

    泛指一切将高维/高解析度/具体数据加工为低维/低解析度/特化数据的过程，通常是为了生成近似算法所需的数据，以提高运行时效率。
    
<br>

#### glPushMatrix() glPopMatrix()

    将本次需要执行的缩放、平移等操作放在glPushMatrix和glPopMatrix之间，配对使用可以消除上一次的变换对本次的影响，使本次变换是以世界坐标系的原点为参考点进行。
    1）OpenGL中的ModelView矩阵变换是一个马尔科夫过程：上一次的变换结果对本次变换有影响，上次ModelView变换后物体在世界坐标系下的位置是本次ModelView变换的起点(本次变换应该是以世界坐标系的原点进行)。默认时本次变换和上次变换不独立。
    2）OpenGL物体建模实际上是分两步走的。第一步，在世界坐标系的原点位置绘制出该物体；第二步，通过ModelView变换矩阵对世界坐标系原点处的物体进行仿射变换，将该物体移动到世界坐标系的目标位置处。
    3）将ModelView变换放在glPushMatrix和glPopMatrix之间可以使本次变换和上次变换独立。
    4）凡是使用glPushMatrix()和glPopMatrix()的程序一般可以判定是采用世界坐标系建模。即世界坐标系固定，ModelView矩阵移动物体。
