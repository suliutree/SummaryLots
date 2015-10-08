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
        须在编译期间知道数组的大小） 。这时候万一你的编译器不允许 “static整数型class常量” 完成 “in class 初值设定”,
        可改为所谓的 “the enum hack” 补偿做法。其理论基础是： “一个属于枚举类型（enumerated type） 的数值可权充int被
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
            ● 为驳回编译器自动 （暗自）提供的机能， 可将相应的成员函数声明为private并且不予实现。 使用像Uncopyable这样
        的base class（见P39）也是一种做法。
        
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
            ● polymorphic（带多态性质的）base classes应该声明一个virtual析构函数。如果class带有任何virtual函数，它就应该拥
        有一个virtual析构函数。
            ● classes的设计目的如果不是作为base classes使用，或不是为了具备多态性，就不该声明virtual析构函数。
        
<br>
####条款8：别让异常逃离析构函数

            C++并不禁止析构函数吐出异常，但它不鼓励你这样做。如果某个操作可能在失败是抛出异常，而又存在某种需要必须处理
        该异常，难么这个异常必须来自析构函数以外的某个函数。
        
        请记住：
            ● 析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下他们
        （不传播）或结束程序。
            ● 如果客户需要对某个操作函数运行期间抛出的异常作出反应，那么class应该提供一个普通函数（而非在析构函数中）执行
        该操作。
 
<br>
####条款9：绝不在构造和析构过程中调用virtual函数

            Base class构造期间virtual函数绝对不会下降到derived classes阶层。取而代之的是，对象的作为就像隶属base类型一样。
        也就是说，在base classes构造期间，virtual函数不是virtual函数。
            根本原因是，在derived class对象的base class构造期间，对象的类型是base class而不是derived class。
            相同的道理也适用于析构函数。
            
        请记住：
            ● 在构造和析构期间不要调用virtual函数，因为这类调用从不降至derived class（比起当前执行构造函数和析构函数的那
        层）。

<br>
####条款10.令operator=返回一个reference to *this

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
                ● 令赋值（assignment）操作符返回一个reference to *this。
        
<br>
####条款12.复制对象时勿忘其每一个成分

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
            ● copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”。
            ● 不要尝试以某个copying函数实现另一个copying函数。应该讲=将共同机能放进第三个函数中（通常叫init），并由两个
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
                ● 如果你调用new时使用了[]，你必须在调用对应delete时也使用[]。如果你调用new时没有使用[]，那么也不该对应
            调用delete时使用[]。
        
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
            ● 尽量以pass-by-reference-to-const替换pass-by-value。前者通常比较高效，并可避免切割问题。
            ● 以上规则并不适用内置类型，以及STL的迭代器和函数对象。对它们而言，pass-by-value往往比较适当。
            
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
            ● 尽可能延后变量定义式的出现。这样做可增加程序的清晰度并改善程序效率。
            
<br>
####条款30：透彻了解inlining的里里外外

            inline只是对编译器的一个申请，不是强制命令。
            inline函数通常一定被置于头文件内，因为大多数建置环境（build environments）在编译过程中进行inlining，而为了将
        一个“函数调用”替换为“被调用函数的本体”，编译器必须知道那个函数长什么样子。
            Templates通常也被置于头文件内，因为它一旦被使用，编译器为了将它具现化，需要知道它长什么样子。（某些建置环境
        可以再连接期才执行template具现化）
            大部分编译器拒绝将太复杂（例如带循环或递归）的函数inlining，而所有对virtual函数的调用（除非是最平淡无奇的）也
        都会使inlining落空。因为virtual意味“等待，直到运行期才确定调用哪个函数”，而inline意味“执行前，先将调用动作替换为
        被调用函数的本体”。
            如果程序要取某个inline函数的地址，编译器通常必须为此函数生成一个outlined函数本体，毕竟编译器不可能提出一个指针
        指向并不存在的函数。与此并提的是，编译器通常不对“通过函数指针而进行的调用”实施inlining，者意味着对inlining函数的调
        用有可能被inlined，也可能不被inlined，取决于该调用的实施方式。
        例：
            inline void f() {...} //假设编译器有意愿inline“对f的调用”
            void (*pf)() = f; //pf指向f
            ...
            f(); //这个调用将被inlined，因为它是一个正常的调用。
            pf(); //这个调用或许不被inlined，因为它通过函数指针达成。
            
            实际上构造函数和析构函数往往是inlining的糟糕候选人，因为编译器在编译期间会安插一些代码到程序中。
            程序库设计者必须评估“将函数声明为inline”的冲击：inline函数无法随着程序库的升级而升级。一旦一个inline函数被修改，
        所有用到此函数的程序都必须被重新编译。但对于non-inline函数，一旦它有任何修改，只需重新连接就好。
            若从纯粹实用观点出发，有一个事实比其他因素更重要：大部分调试器面对inline函数都束手无策。毕竟你如何在一个并不存
        在的函数内设立断点呢？
        
        请记住:
            ● 将大多数inlining限制在小型，被频繁调用的函数身上。这可使日后的调试过程和二进制升级更容易，也可使潜在的代码膨胀
        问题最小化，使程序速度提升机会最大化。
            ● 不要只因为function templates出现在头文件，就将它们声明为inline。
        
<br>
####条款33：避免遮掩继承而来的名称

            C++名称遮掩规则（name-hiding rules）所做的唯一的事情就是：遮掩名称。
            对于继承来说，derived class作用域被嵌套在base class作用域内。
        例：
            class Base{
            private:
                int x;
            public:
                virtual void mf1() = 0;
                virtual void mf1(int);
                virtual void mf2();
                void mf3();
                void mf3(double);
                ...
            };
            
            class Derived: public Base {
            public:
                virtual void mf1();
                void mf3();
                void mf4();
                ...
            };
            以作用域为基础的“名称掩盖规则”并没有改变，因此base class内所有名为mf1和mf3的函数都被derived class内的mf1
        和mf3函数遮掩掉了。
            Dervied d;
            int x;
            ...
            d.mf1(); //没问题，调用Dervied::mf1
            d.mf1(x); //错误！因为Derived:mf1遮掩了Base::mf1
            d.mf2(); //没问题，调用Base::mf2
            d.mf3(); //没问题，调用Derived::mf3
            d.mf3(x); //错误！因为Derived::mf3遮掩了Base::mf3
            如你所见，上述规则都适用，即使base classes和derived classes内的函数有不同的参数类型也适用，而且不论函数
        是virtual或non-virtual一体适用。
            不幸的是你通常会想继承重载函数。实际上如果你正在使用public继承而又不继承那些重载函数，就是违反base和
        derived class之间的is-a关系，而条款32说过is-a是public继承的基石。
            你可以使用using声明达成目标：
            class Base {
            private:
                int x;
            public:
                virtual void mf1() = 0;
                virtual void mf1(int);
                virtual void mf2();
                void mf3();
                void mf3(double);
                ...
            };
            
            class Derived: public Base {
            public:
                using Base::mf1; //让Base class内名为mf1和mf3的所有东西
                using Base::mf3; //在Derived作用域内都可见（并且public）
                virtual void mf1();
                void mf3();
                void mf4();
                ...
            };
            现在继承机制将一如既往地运作：
            Derived d;
            int x;
            ...
            d.mf1(); //仍然没问题，调用Derived::mf1
            d.mf1(x); //现在没问题，调用Derived::mf1
            d.mf2(); //仍然没问题，调用Base::mf2
            d.mf3(); //没问题，调用Derived::mf3
            d.mf3(x); //现在没问题，调用Derived::mf3
            这意味着如果比继承base classes并加上重载函数，而你又希望重新定义或覆写（推翻）其中一部分，那么你必须为那些
        原本会被遮掩的每个名称引入一个using声明，否则某些你希望继承的名称会被遮掩。
        
        请记住：
            ● derived classes内的名称会遮掩base classes内的名称。在public继承下从来没有人希望如此。
            ● 为了让被遮掩的名称再见天日，可使用using声明式或转交函数（forwarding functions）。

<br>
####条款36：绝不重新定义继承而来的non-virtual函数

        例：
            Base B {
            public:
                void mf();
            ...
            };
            
            class D: public B {
            public:
                void mf();
            ...
            };
            
            D x;
            B* pB = &x; //获得一个指针指向x
            D* pD = &x; //获得另一个指针指向x
            pB->mf(); //调用B::mf
            pD->mf(); //调用D::mf
            你可能会相当惊讶，毕竟两者都通过对象x调用成员函数mf。造成这种两面行为的原因是，non-virtual函数如B::mf和D::mf
        都是静态绑定。这意味着通过pB调用的non-virtual函数永远是B所定义的版本，即使pB指向一个类型为“B派生之class”的对象。
            但另一方面，virtual函数却是动态绑定。如果mf是个virtual函数，不论是通过pB或pD调用mf，都会导致调用D::mf，因为
        pB和pD真正指的都是一个类型为D的对象。
        
<br>
####条款37：绝不重新定义继承而来的缺省参数值

            既然重新定义一个继承而来的 non-virtual函数永远是错误的，所以我们将本条款局限于“继承一个带有缺省参数值的
        virtual函数”。
            对象所谓的静态类型（static type），就是它在程序中被声明时所采用的类型。
        例：
            class Shape {
            public:
                enum ShapeColor {Red, Green, Blue};
                virtual void draw(ShapeColor color = Red) const = 0;
            ...
            };
            
            class Rectangle: public Shape {
            public:
                //注意，赋予不同的缺省参数值。这真糟糕！
                virtual void draw(ShaperColor color = Green) const;
            ...
            };
            
        现在考虑这些指针：
            Shape* ps; //静态类型为Shape*
            Shape* pr = new Rectangle; //静态类型为Shaper*
            本例中ps和pr都被声明为pointer-to-Shape类型，所以它们都以它为静态类型。不论它们真正指向什么，它们的静态类型
        都是Shape*。
            对象的所谓动态类型则是指“目前所指对象的类型”。也就是说，动态类型可以表现出一个对象将会有什么行为。以上例而
        言，pr动态类型是Rectangle*，ps没有动态类型，因为它尚未指向任何对象。
            virtual函数系动态绑定而来，意思是调用一个virtual函数时，究竟调用哪一份函数实现代码，取决于发出调用的那个对
        象的动态类型：
            pr->draw(Shape::Red); //调用Rectangle::draw(Shape::Red)
            virtual函数是动态绑定，而缺省参数值却是静态绑定的。意思是你可能会在“调用一个定义于derived class内的virtual
        函数”的同时，却使用base class为它所指定的缺省参数值：
            pr->draw(); 调用Rectangle::draw(Shape::Red)!
        
        请记住：
            ● 绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，而virtual函数——你唯一应该覆写的东西
        ——却是动态绑定的。
        
<br>
####条款40：明智而审慎的使用多继承

            使用virtual继承的那些classes所产生的对象往往比使用non_virtual继承的兄弟们体积大，访问virtual base classes
        的成员变量时，也比访问non-virtual base classes的成员变量速度慢。总之，你得为virtual继承付出代价。
            支持“virtual base classes 初始化”的规则比起non-virtual basees的情况远为复杂且不直观。virtual base的初始化
        责任是由继承体系中的最低层（most derived） class负责，中间层classes对其virtual bases的初始化都将被屏蔽。也就是
        说当一个新的derived class加入到继承体系的底层时，它必须承担其virtual bases（不论是直接还是间接）的初始化责任。
            在产生一个新的derived class对象时，所有virtual bases的构造函数总是先于所有non-virtual bases的构造函数被调
        用。
            我对virtual base classes（亦相当于对virtual继承）的忠告是：
            1.非必要不使用virtual base。
            2.如果你必须使用virtual base classes，尽可能避免在其中放置数据。
            如果你有个单一继承的设计方案，而它大约等价于一个多重继承的方案，那么但以继承的设计方案一定比较受欢迎。
        
        请记住：
            ● 多重继承比单一继承复杂。它可能导致歧义性，以及对virtual继承的需要。
            ● virtual继承会增加大小、速度、初始化（及赋值）复杂度等等成本。如果virtual base classes不带任何数据，将是
        最具使用价值的情况。
            ● 多重继承的确有正当用途。其中一个情节涉及“public继承某个Interface class”和“private继承某个协助实现的class”
        的两相组合。

<br>
####条款42：了解typename的双重意义

            声明template参数时，不论使用关键字class或typename，意义完全相同。下面两个template声明式完全相同：
            template<class T> class Widget;
            template<typename T> class Widget;
            template内出现的名称如果相依于某个template参数，称之为从属名称（dependent names）。如果从属名称在class内呈
        嵌套状，我们称它为嵌套从属名称（nested dependent name）。
            嵌套从属名称肯能导致解析困难。
        例：
            template<typename C>
            void print2nd(const C& container)
            {
                C::const_iterator* x;
                ...
            }
            看起来好像我们声明x为一个local变量，它是个指针，指向一个C::const iterator。 但它之所以被那么认为， 只因为我
        们 “已经知道” C::const iterator是个类型。 如果C::const iterator不是个类型呢？如果C有个static成员变量而碰巧被命
        名为const iterator，或如果x碰巧是个global变量名称呢？那样的话上述代码就不再是声明一个local变量，而是一个相乘动
        作：C::const iterator乘以x。
            C++有个规则可以解析此一歧义状态：如果解析器在template中遭遇一个嵌套从属名称，它便假设这名称不是个类型，除非
        你告诉它是。所以缺省情况下嵌套从属名称不是个类型。此规则有个例外，稍后我会提到。所以下面的C++代码不是有效的：
            template<typename C> //这是无效的C++代码
            void print2nd(const C& container)
            {
                if (container.size() >= 2) {
                    C::const_iterator iter(container.begin()); //这个名称被假设为非类型
                    ...
                }
            }
            
            iter声明式只有在C::const_iterator是个类型时才合理，但我们并没有告诉C++说它是，于是C++假设它不是。所以我们
        必须告诉C++说C::const_iterator是个类型。只要紧邻它之前放置关键字typename即可：
            template<typename C> //这是合法的C++代码
            void print2nd(const C& container)
            {
                if (container.size() >= 2) {
                    typename C::const_iterator iter(container.begin());
                    ...
                }
            }
            typename只被用来验明嵌套从属类型名称；其他名称不该用它。
            “typename必须作为嵌套从属类型名称的前缀词”这一规则的例外是，typename不可以出现在base classes list内的嵌套
        从属类型名称之前，也不可在member initialization list（成员初值列）中作为base class修饰符。例如：
            template<typename T>
            class Derived: public Base<Y>::Nested { //base class list中不允许“typename”。
            public:
                explicit Derived(int x)
                : Base<T>::Nested(x) //mem.init.list中不允许“typename”。
                {
                    typename Base<T>::Nested temp; //嵌套从属类型名称，作为一个base class修饰符需加上typename。
                }
            }
        
        请记住：
            ● 声明template参数时，前缀关键字class和typename可互换。
            ● 请使用关键字typename表示嵌套从属名称；但不得在base class list（基类列）或member initialization liat（成
        员初值列）内以它作为base class的修饰符。


<br>
####条款44：将与参数无关的代码抽离templates

            在大多数平台上，所有指针类型都有相同的二进制表述，因此凡templates持有指针者（例如list<int*>, list<const int*>
        等等）往往应该对每一个成员函数使用唯一一份底层实现。这很具代表性的意味，如果你实现某些成员函数而它们操作强型
        指针（strongly type pointers，即T*），你应该令它们调用另一个操作无类型指针（untyped pointers，即void*）的函数，
        由后者完成实际工作。
        
        请记住：
            ● Templates生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系。
            ● 因非类型模板参数（non-type template parameters）而造成的代码膨胀，往往可消除，做法是以函数参数或class成
        员变量替换template参数。
            ● 因类型参数（type parameters）而造成的代码膨胀，往往可降低，做法是让带有完全相同二进制表述（binary 
        representations）的具现类型（instantiation types）共享实现码。
            
            
        
