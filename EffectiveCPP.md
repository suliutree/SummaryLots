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
        
<br>
####条款07：为多态基类声明virtual析构函数

        C++明白指出，当derived class对象经由一个base class指针被删除，而该base class带这一个non-virtual析构函数，其结果
        未有定义——实际执行时通常是对象的derived成分没被销毁。
        任何class只要带有virtual函数都几乎确定应该也有一个virtual析构函数。如果class不含virtual函数，通常表示它并不意图
        被用作一个base class。当class不企图被当做base class，令其析构函数为virtual往往是个馊主意，因为这样会增加其对象的
        大小。
        如果希望让一个类成为抽象基类，你应该为它声明一个pure virtual析构函数。
        例如：
            class AWOV {
            public:
                virtual ~AWOV() = 0;
            };
        这个class有一个pure class函数，所以它是个抽象class，又由于它有个virtual析构函数，所以你不需要担心析构函数的问题。
        然而这里有个窍门：你必须为这个pure virtual析构函数提供一份定义：
            AWOV::~AWOV() {}        //pure virtual析构函数的定义
        析构函数的运作方式是最深层派生的那个class其析构函数最先被调用，然后是其每一个base class的析构函数被调用。编译器
        会在AWOV的derived classes的析构函数中创建一个对~AWOV的调用动作，所以你必须为这个函数提供一份定义。如果不这样做，
        连接器会发出抱怨。
            “给base classes一个virtual析构函数”，这个规则只适用于带多态性质的base class身上。这种base classes的设计目的
        是为了用来“通过base class接口处理derived class 对象”。
            并非所有base class的设计目的都是为了多态用途。例如标准string和STL容器都不被设计作为base classes使用，更别提
        多态了。某些classes设计的目的是作为base classes使用，但不是为了多态用途。
        
        请记住：
            polymorphic（带多态性质的）base classes应该声明一个virtual析构函数。如果class带有任何virtual函数，它就应该拥
        有一个virtual析构函数。
            classes的设计目的如果不是作为base classes使用，或不是为了具备多态性，就不该声明virtual析构函数。
        
<br>
####条款8：别让异常逃离析构函数

            C++并不禁止析构函数吐出异常，但它不鼓励你这样做。如果某个操作可能在失败是抛出异常，而又存在某种需要必须处理
        该异常，难么这个异常必须来自析构函数以外的某个函数。
        
        请记住：
            析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下他们
        （不传播）或结束程序。
            如果客户需要对某个操作函数运行期间抛出的异常作出反应，那么class应该提供一个普通函数（而非在析构函数中）执行
        该操作。
 
<br>
####条款9：绝不在构造和析构过程中调用virtual函数

            Base class构造期间virtual函数绝对不会下降到derived classes阶层。取而代之的是，对象的作为就像隶属base类型一样。
        也就是说，在base classes构造期间，virtual函数不是virtual函数。
            根本原因是，在derived class对象的base class构造期间，对象的类型是base class而不是derived class。
            相同的道理也适用于析构函数。
            
        请记住：
            在构造和析构期间不要调用virtual函数，因为这类调用从不降至derived class（比起当前执行构造函数和析构函数的那层）。

<br>
####10.令operator=返回一个reference to *this

        赋值可以写成连锁形式：
        x = y = z = 15;
        赋值采用右结合律：
        x = (y = (z = 15));
        为了实现“连续赋值"，赋值操作符必须返回一个reference指向操作符的左侧实参。这是你为classes实现赋值操作时应该遵循
        的协议：
        例：
            class Widget {
            public:
                ...
                Widget& operator=(const Widget& rhs) //返回类型是个reference，指向当前对象
                {
                    ...
                    return *this; //返回左侧对象
                }
                ...
            };
            这个协议不仅适用于以上的标准赋值形式，也适用于所有赋值相关运算，如“+=、-=、*=”等。
            
            请记住：
                令赋值（assignment）操作符返回一个reference to *this。
        
<br>
####12.复制对象时勿忘其每一个成分

            设计良好的面向对象系统会将对象内部封装起来，只留两个函数负责对象拷贝（复制），那便是copy构造函数和copy assignment
        操作符，我称为copying函数。
            任何时候只要你承担起“为derived class撰写copying函数”的重大责任，必须很小心的也复制其base class成分。
            
        例：
            class Customer {
            ...
            };
            
            public PriorityCustomer: public Customer {
            public:
                PriorityCustomer(const PriorityCustomer& rhs);
                PriorityCustomer& operator=(const PriorityCustomer& rhs);
                ...
            private:
                int priority;
            };
            
            PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
            : Customer(rhs), priority(rhs.priority)
            {
            }
            
            PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
            {
                Customer::operator=(rhs);
                priority = rhs.priority;
                return *this;
            }
            
        当你编写一个copying函数，请确保
        1）复制所有的local成员变量；
        2）调用所有base classes内的适当的copying函数。
        
        请记住：
            copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”。
            不要尝试以某个copying函数实现另一个copying函数。应该讲=将共同机能放进第三个函数中（通常叫init），并由两个
        copying函数共同调用。
            
<br>
####条款16.成对使用new和delete时要采用相同的形式

            当你使用new（也就是通过new动态生成一个对象），有两件事发生。第一，内存被分配出来（通过名为operator new的函
        数，见条款49和条款51）。第二，针对此内存会有一个（或更多）构造函数被调用。当你使用delete，也有两件事发生：针对
        此内存会有一个（或更多）析构函数被调用，然后内存才被释放。delete最大的问题在于：即将被删除的内存之内究竟有多少
        对象？
            单一对象的内存布局一般而言不同于数组的内存布局，数组所用的内存通常还包括“数组大小”的记录，以便delete知道需
        要调用多少次析构函数。单一对象内存则没有这笔记录。
            如果你使用delete是加上中括号（方括号），delete便认定指针指向一个数组，否则它便认定指针指向单一对象。
            
        例：
            std::string* stringPtr1 = new std::string;
            std::string* stringPtr2 = new std::string[100];
            ...
            delete stringPtr1;      //删除一个对象
            delete[] stringPtr2;    //删除一个有对象组成的数组
            游戏规则很简单：如果你调用new时使用了[]，你必须在调用对应delete时也使用[]。如果你调用new时没有使用[]，那么
        也不该对应调用delete时使用[]。
            
            这个规则对于喜欢使用typedef的人也很重要。考虑下面这个typedef：
        例：
            typedef std::string AddressLines[4];
            std::string* pal = new AddressLines; //注意，“new AddressLines”返回一个string*。
                                                 //就像“new string[4]”一样。
            ...
            delete pal; //行为未有定义!
            delete[] pal; //很好
            为避免此类错误，最好尽量不要对数组形式做typedef动作。
            
        请记住：
                如果你调用new时使用了[]，你必须在调用对应delete时也使用[]。如果你调用new时没有使用[]，那么
        也不该对应调用delete时使用[]。
        
<br>
####条款20.宁以 pass-by-reference-to-const替换pass-by-value

            Pass-by-reference-to-const的效率高的多，没有任何构造函数或析构函数被调用，因为没有任何新对象被创建。
            以by-reference方式传递参数也可以避免对象切割问题。当一个derived class对象以by-value的方式传递并被视为一个
        base class对象，base class的copy构造函数会被调用，而“造成此对象的行为像个derived class对象”的那些特化性质全被
        切割掉了，仅仅留下一个base class对象。
            referenc往往以指针实现出来，因此pass-by-reference通常意味着真正传递的是指针。因此如果你有个对象属于内置类、
        型（如int），pass-by-value往往比pass-by-reference的效率高些。这个忠告也适用于STL迭代器和函数对象。
            并不是小型types都是pass-by-value的合格候选人，对象小并不就意味着copying构造函数不昂贵。即使小型对象拥有并
        不昂贵的copy构造函数，还是可能有效率上的争议。某些编译器对待 “内置类型” 和 “用户自定义类型”的态度截然不同，纵
        使两者拥有相同的底层表述（underlying representation）。
            “小型的用户自定义类型不必然成为pass-by-value优良候选人”的另一个理由是，作为一个用户自定义类型，其大小容易
        有所变化。
            一般而言，你可以合理假设“pass-by-value并不昂贵”的唯一对象就是内置类型和STL的迭代器和函数对象。
        
        请记住：
            尽量以pass-by-reference-to-const替换pass-by-value。前者通常比较高效，并可避免切割问题。
            以上规则并不适用内置类型，以及STL的迭代器和函数对象。对它们而言，pass-by-value往往比较适当。
            
<br>
####条款26.尽量延后变量定义式出现的时间

            只要你定义了一个变量而其类型带有一个构造函数或析构函数，那么当程序控制流到达这个定义式时，你便得承受构造成
        本；当这个变量离开其作用域时，你便得承受析构成本。
            你不只应该延后变量的定义，直到非得使用该变量的前一刻为止，甚至应该尝试延后这份定义直到能够给它初值实参为止。
        如果这样，不仅能够避免构造（和析构）非必要对象，还可以避免无意义的default构造行为。
            “但循环怎么办？”如果变量只在循环内使用，那么把它定义于循环外并在每次循环迭代时赋值给它比较好，还是把它定义
        于循环内？
        例：
            //方法A：定义于循环内
            Widget w;
            for (int i = 0; i < n; ++i)
            {
                w = 取决于i的某个值;
                ...
            }
            和
            //方法B：定义于循环外
            for (int i = 0; i < n; ++i)
            {
                Widget w(取决于i的某个值);
                ...
            }
            如果classes的一个赋值成本低于一组构造+析构成本，做法A大体而言比较高效。否则做法B或许较好。此外，做法A造成
        名称w的作用域（覆盖整个循环）比做法B更大，有时会对程序的可理解性和易维护性造成冲突。因此除非（1）你知道赋值成
        本比“构造+析构”成本低，（2）你正在处理代码中效率高度敏感的部分，否则你应该使用做法B。
        
        请记住：
            尽可能延后变量定义式的出现。这样做可增加程序的清晰度并改善程序效率。
            
            
            
            
            
            
            
        
