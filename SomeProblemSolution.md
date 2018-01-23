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
    <br>
    1）OpenGL中的ModelView矩阵变换是一个马尔科夫过程：上一次的变换结果对本次变换有影响，上次ModelView变换后物体在世界坐标系下的位置是本次ModelView变换的起点(本次变换应该是以世界坐标系的原点进行)。默认时本次变换和上次变换不独立。
    <br>
    2）OpenGL物体建模实际上是分两步走的。第一步，在世界坐标系的原点位置绘制出该物体；第二步，通过ModelView变换矩阵对世界坐标系原点处的物体进行仿射变换，将该物体移动到世界坐标系的目标位置处。
    <br>
    3）将ModelView变换放在glPushMatrix和glPopMatrix之间可以使本次变换和上次变换独立。
    <br>
    4）凡是使用glPushMatrix()和glPopMatrix()的程序一般可以判定是采用世界坐标系建模。即世界坐标系固定，ModelView矩阵移动物体。
    
<br>

#### 材质

        光与物体表面交互的一切，都是由材质及其属性来决定的，材质决定了每个物体表面最终呈现出来是什么颜色。
        在计算机图形学中，一个物体的“形”与“色”是完全分开的，物体的形状由一组顶点（Vertex）构成的网格（Mesh）组成，而物体的表面着色则由称为材质（Material）的东西决定。所以材质通常包含纹理（Textures），着色器（Shaders）以及其它一些着色方程需要的参数，所有这些数据构成一个对象被附加到一个物体上，在渲染时这些数据被传输至GPU内存，GPU执行其中的着色器对该物体表面着色，这个过程包括贴图，光照以及其它相关的计算。
    
<br>

#### GLSL中的变量（uniform, attribute, varying）

    （1）uniform 变量
    <br>
        uniform 变量是外部程序传递给（vertex和fragment）shader的变量。因此它是 application 通过函数 glUniform**() 函数赋值的。在（vertex和fragment）shader程序内部，uniform 变量就像C语言里面的常量（const），它不能被 shader 程序修改。
    <br>
        如果 uniform 变量在 vertex 和 fragment 两者之间声明方式完全一样，则它可以在 vertex 和 fragment 共享使用。相当于一个被 vertex 和 fragment shader 共享的全局变量。
    <br>
        uniform 变量一般用来表示：变换矩阵，材质，光照参数和颜色等信息。
    
    （2）attribute 变量
    <br>
        attribute 变量是只能在 vertex shader 中使用的变量。fragment sghader 中不能声明 attribute 变量，变量也不能被 fragment shader 使用。
    <br>
        一般用 attribute 变量来表示一些顶点数据，如：顶点坐标，法线，纹理坐标，顶点颜色等。在 application 中，一般用函数 glBindAttribLocation() 来绑定每个 attribute 变量的位置，然后用函数 glVertexAttribPointer() 为每个 atribute 变量赋值。
    
    （3）varying 变量
    <br>
        varying 变量是 vertex 和 fragment shader 之间用来传递数据的。一般 vertex shader 修改 varying 变量的值，然后 fragment shader 使用该 varying 变量的值。因此 varying 变量在 vertex 和 fragment shader 二者之间的声明必须是一致的。 application 不能使用此变量。

<br>

#### Visual Studio 中查看动态库具体的加载位置

        程序运行之后，通过 调试  -> 窗口 -> 模块，可以查看所加载的动态库具体的位置。

<br> 

#### 在动态库存在的情况下出现无法定位当相应的动态库

        动态库明明存在，却弹出无法定位到相应的动态库，这时候要确定下这个 dll 和其 lib 是否匹配，检查其是否是最新编译出来的。

<br>

#### 使用常识估算许多基本算法的阶

    * 简单循环
    <br>
        如果某个简单循环从1运行到 n ，那么算法很可能就是 O(n) ——时间随n线性增加。其例子有穷举查找、找到数组中的最大值、以及生成校验和。
    
    * 嵌套循环
    <br>
        如果你需要在循环中嵌套另外的循环，那么你的算法就变成了 O(m x n)，这里的 m 和 n 是两个循环的界限。这通常发生在简单的排序算法中，比如冒泡排序：外循环依次扫描数组中的每个元素，内循环确定在排序结果的何处放置该元素。这样的排序算法往往是 O(n^2)。
        
    * 二分法
    <br>
        如果你的算法在每次循环时把事物集合一分为二，那么它可能是对数型 O(lg(n)) 算法。对有序列表的二分查找、遍历二叉树、以及查找机器字中的第一个置位了的位，都可能是 O(lg(n))算法。
     
    * 分而治之
    <br>
        划分其输入，并独立的在两个部分上进行处理，然后再把结果组合起来的算法可能是 O(nlg(n))。经典的例子是快速排序，其工作方式是：把数据划分为两半，并递归的对每一半进行排序。
    
    * 组合
    <br>
        只要算法考虑事物的排列，其运行时间就有可能失去控制。这是因为排列涉及到阶乘（从数字 1 到 5 有 5! = 5x4x3x2x1 = 120种排列）。得出5个元素的组合算法所需要的时间：6个元素需要6倍的时间，7个元素需要42倍的时间。其例子包括许多公认的难题算法——旅行商问题、把东西最优的包装进容器中，划分一组数、使每一组都有相同的总和，等等。在特定的问题领域中，常常用启发式方法（heuristics）减少这些类型的算法的运行时间。
 
 <br>
 
 #### DirectX 与 OpenGL 中矩阵的不同以及相关的矩阵变换
 
    http://www.cnblogs.com/graphics/archive/2012/08/02/2616017.html

<br>

#### 函数命名时一些常见的互补术语

    Add/Remove <br>
    Begin/End <br>
    Create/Destroy <br>
    Enable/Disable <br>
    Insert/Delete <br>
    Lock/Unlock <br>
    Next/Previous <br>
    Open/Close <br>
    Push/Pop <br>
    Send/Receive <br>
    Show/Hide <br>
    Source/Target <br>
