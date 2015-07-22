##Effective C++

####条款01：视C++为一个语言联邦

        今天C++已经是个多重泛型编程语言（multiparadigm programming language），一个同时支持过程形式、面向对象形式、函数
        形式、泛型形式、元编程形式的语言。
        最简单的方法就是将C++视为一个由相关次语言组成的联邦而非单一的语言。幸运的是，次语言总共有四个：
        
        ● C。
        
        ● Object-Oriented C++。包括：class（包括构造函数和析构函数）、封装（encapsulation）、继承（inheritance）、多态
        （polymorphism）、virtual函数（动态绑定）等等。
        
        ● Template C++。这是C++泛型编程（generic programming）的部分。
        
        ● STL。STL是个template程序库，但它是非常特殊的一个。它对容器、迭代器、算法以及函数对象的规约有极佳的紧密配合与
        协调。
        

<br>
####条款02：尽量以const，enum，inline替换#define

        这个条款或许可以改为“另可用编译器替换预处理器”。
        通常C++要求你对所使用的任何东西提供一个定义式，但如果它是个class专属常量又是static且为整数类型（integraltype,
        例如int,char,bool） ，则可特殊处理。只要不取它们的地址，你可以声明并使用它们而无需提供定义式。
        
        class GamePlayer{
        private:
                static const int NumTurns = 5 ; //常量声明式
                int scores[NumTurns] ; //使用该常量
                ...
        };
        上面的是NumTurns的声明式而非定义式。如果你要取这个class专属常量的地址，你就必须另外提供定义式如下：
        const int GamePlayer::NumTurns; //NumTurns的定义；
        上面的这个式子应该放入一个实现文件而非头文件！由于它已经在声明时获得了初值，定义时不可以再设初值。
        
        旧式编译器也许不支持上述语法，他们不允许static成员在其声明式上获得初值。此外，所谓的 “in-class初值设定”也只允
        许对整数常量进行。如果你的编译器不支持上述语法，你可以将初值放在定义式：
        class CostEstimate{
        private:
                static const double FudgeFactor; //static class 常量声明， 位于头文件内
                ...
        };
        const double CostEstimate::FudgeFactor = 1.35; //static class 常量定义， 位于实现文件中
        
        一个例外是当你在class编译期间需要一个class常量值， 例如上面的GamePlayer::scores的数组声明式中（编译器坚持必
        须在编译期间知道数组的大小） 。这时候万一你的编译器不允许 “static整数型class常量” 完成 “in class 初值设定” ，                 可改为所谓的 “the enum hack” 补偿做法。其理论基础是： “一个属于枚举类型（enumerated type） 的数值可权充int被
        使用” ，于是GamePlayer可定义如下：
        class GamePlayer{
        private:
                enum { NumTurns = 5 } ;
                int scores[NumTurns] ;
                ...
        };

<br>
####条款03：尽可能使用const

        char greeting[] = "hello";
        char* p = greeting;                     // noo-const pointer, non-const data
        const char* p = greeting;               // non-const pointer, const data
        char* const p = greeting;               // const-pointer, non-const data
        const char* const p = greeting;         // const-pointer, const data
        ● 如果关键字const出现在星号左边，表示被指物是常量；如果出现在星号右边，表示指针自身是常量；如果出现在星号两边，
        表示被指物和指针两者都是常量。
        
        
        void f1(const Widget* pw);      // f1获得一个指针，指向一个常量（不变的）Widget对象
        void f2(Widget const * pw);     // f2也是
        ● 两种写法意义相同
        
        
        std::vector<int> vec;
        ...
        const std::vector<int>::iterator iter = vec.begin();    // iter的作用像个T* const，表示这个迭代器不得指向不同
                                                                // 的东西，但它所指的东西的值是可以改动的。
        *iter = 10;                                             // 没问题，改变iter所指物
        ++iter;                                                 // 错误！iter是const
        
        std::vector<int>::const_iterator it = vec.begin();      // iter的作用像个const T*，表示迭代器所指的东西不可改动
        *it = 10;                                               // 错误！*it是const
        ++it;                                                   // 没问题，改变it
        
        
        ● 令函数返回一个常量值，往往可以降低因客户错误而造成的意外，而又不至于放弃安全性和高效性。
        ● 至于const参数，除非你有需要改动的参数或local对象，否则请将他们声明为const。
        

<br>
####条款04：确定对象被使用前已先被初始化

        读取未初始化的值会导致不明确的行为。
        通常如果你使用C part of C++ （见条款01） 而且初始化可能招致运行期成本，那么就不保证发生初始化。 一旦进入non-C 
        parts of C++， 规则有些变化。 这就是为什么array （来自C part of C++）不保证其内容被初始化，而vector（来自STL 
        part of C++）却有此保证。
        C++规定，对象的成员变量的初始化动作发生在进入构造函数本体之前。所以，相对于在构造函数本体里为成员变量赋值，一
        个更好的办法是在member initialization list（成员初值列）里初始化成员变量。如果成员变量是const或references，它
        们就一定需要初值 （所以只能放在成员初值列中） ，不能被赋值。
        C++有着十分固定的“成员初始化次序” ：base classes更早于derived classes被初始化，而class的成员变量总是以其声明
        次序（类定义中的次序）被初始化。即使它们在成员初值列中以不同的次序出现 （很不幸那是合法的） ，也不会有任何影响。
        一旦你已经很小心地将“内置型成员变量”明确地加以初始化，而且也确保你的构造函数运用“成员初值列”初始化base classes
        和成员变量，那就只剩唯一一件事需要操心— “不同编译单元内定义之non-local static对象” 的初始化次序。


<br>
####条款05：了解C++ 默默编写并调用哪些函数

        如果你自己没声明，编译器就会为它声明（编译器版本）一个default 构造函数、一个copy 构造函数、 一个copy assignment
        操作符和一个析构函数。因此，如果你写下：
                class Empty{ } ;
        这就好像你写下这样的代码：
                class Empty{
                public:
                        Empty() { ... } // default 构造函数
                        Empty(const Empty& rhs) { ... } // copy 构造函数
                        ∼Empty() { ... } // 析构函数
                        Empty& operator=(const Empty& rhs) { ... } // copy assignment 操作符
                };
        惟有当这些函数被需要 （被调用） ，它们才会被编译器创建出来。
        所有这些函数都是public 且inline （见条款30） 。注意，编译器产生的析构函数是个non-virtual（见条款07） ，除非这个
        class 的base class 自身声明有virtual 析构函数。
        如果某个base classes 将copy assignment 操作符声明为private，编译器将拒绝为其derived classes 生成一个copy 
        assignment 操作符。
        

<br>
####条款06：若不想使用编译器自动生成的函数，就该明确拒绝

        所有编译器产生的函数都是public。为阻止这些函数被创建出来，你得自行声明它们。为使产生的类不支持copying，你可以
        将copy构造函数或copy assignment操作符声明为private。
        
        请记住：
        为驳回编译器自动 （暗自）提供的机能， 可将相应的成员函数声明为private并且不予实现。 使用像Uncopyable这样的base
        class （见P39）也是一种做法。
        
        
        
