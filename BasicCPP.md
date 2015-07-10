##C++基础知识

####内存分区

        1.堆：由程序员手动分配和释放，完全不同于数据结构中的堆，分配方式类似链表。由malloc（C语言）或new（C++）来分配，free
        （C语言）和delete（C++）释放。若程序员不释放，程序结束时由系统释放。
        
        2.栈：由编译器自动分配和释放，存放函数的参数值、局部变量的值等。操作方式类似数据结构中的栈。
        
        3.全局（静态）存储区：存放全局变量和静态变量。包括DATA段（全局初始化区）与BSS段（全局未初始化区）。其中，初始化的全局
        变量和静态变量存放在DATA段，未初始化的全局变量和静态变量存放在BSS段。程序结束后有系统释放。
        其中BSS段的特点是：在程序执行之前BSS段会自动清0。所以，未初始化的全局变量和静态变量在程序执行之前就已经成0了。
        
        4.文字常量区：常量字符串就放在这里，程序结束后由系统释放。
        
        5.程序代码区：存放函数体的二进制代码。



####类和继承

        #define NAME_SIZE 50
        
        class Person {
                int id;                 // 所有成员默认为私有（private）
                char name[NAME_SIZE];
                
        public:
                void aboutMe()
                {
                        cout << "I am a person.";
                }
        };
        
        class Student {
        public:
                void aboutMe()
                {
                        cout << "I am a student.";
                }
        };
        
        Student* p = new Student();
        p->aboutMe();   // 打印“I am a student.”
        delete p;       // 务必释放之前分配的内存
        
        在C++中，所有数据成员和方法均默认为私有（private），可用关键字public修改其属性。



####构造函数和析构函数

        对象创建时会自动调用类的构造函数，如果没有定义构造函数，编译器会自动生成一个默认的构造函数（Default Constructor）。
        自定义构造函数：
                Person(int a) {
                        id  = a;
                }
                或者
                Person(int a) : id(a) { // 成员初值列
                        ...
                }
                在真正对象创建之前，且在构造函数余下代码调用前，数据成员id就会被赋值。在常量数据成员赋值时（只能赋值
                一次），这种写法特别适用。
        
        析构函数会在对象删除时执行清理工作。对象销毁时会自动调用析构函数。我们不会显示的调用析构函数，因此它不能带参数。
                ~Person() {
                        delete obj;     // 释放之前这个类里分配的内存
                }



####虚函数

        类的一个成员定义为一个虚函数的实际意义在于让C++知道该函数并无意义，它的作用只是为了让派生类进行函数重载保留位
        置。
        
        纯虚函数的定义方法就是在类的虚函数后面加上“ = 0 ”标记，类中一旦出现了纯虚函数的定义，那么此类为抽象类，不能实
        例化。
        
        class Person {
                int id;
                char name[NAME_SIZE];
        public:
                virtual aboutMe() {
                        cout << "I am a person.";
                }
                
                virtual bool addCourse(string s) = 0;
        };
        
        class Student : public Person {
        public:
                void aboutMe {
                        cout << "I am a Student.";
                }
                
                bool addCourse(string s) {
                        cout << "Added Course " << s << "to student." << endl;
                        return true;
                }
        };
        
        Person* p = new Student();
        p->aboutMe();   // 打印“I am a student.”
        p->addCourse("History");
        delete p;
        
        虚析构函数：
                class Person {
                public:
                        ~Person() {
                                cout << "Deleteing a person." << endl;
                        }
                };
                
                class Student : public Person {
                public:
                        ~Student() {
                                cout << "Deleting a student." << endl;
                        }
                };
                
                Person* p = new Student();
                delete p;
                
                打印输出如下：
                Deleting a student.
                Deleting a person.
        
        虚函数工作原理：
                虚函数需要虚函数表（Virtual Table）才能实现。如果一个类有函数声明称虚拟的，就会生成一个vtable，存放
                这个类的虚函数地址。此外，编译器还会在类里加入隐藏的vptr变量（虚函数指针）。若子类没有覆写虚函数，该
                子类的vtable就会存放父类的函数地址。调用这个虚函数时，就会通过vtable解析函数的地址。
                在C++里，动态绑定就是通过vtable机制实现的。



####深拷贝和浅拷贝

        浅拷贝会将对象的所有成员的值拷贝到另一个对象里。除了拷贝所有对象的值，深拷贝还会进一步拷贝所有指针对象。
        
        struct Test {
                char* ptr;
        };
        
        void shallow_copy(Test& src, Test& dest) {
                dest.ptr = src.ptr;
        }
        
        void deep_copy(Test& src, Test& dest) {
                dest.ptr = (char *)malloc(strlen(src.ptr) + 1);
                strcpy(dest.ptr, src.ptr);
        }
        
        shallow_copy可能会导致大量编程运行时错误，尤其是在对象创建和销毁时。使用浅拷贝是必须非常小心，只有当开发人员
        真正知道自己在做些什么的时方可选用浅拷贝。多数情况下，使用浅拷贝是为了传递一块复杂的结构信息，但又不想真的复
        制一份数据。使用浅拷贝时，销毁对象必须非常小心。
        在实际开发中，浅拷贝很少使用。大部分情况都应该使用深拷贝。



####指针和引用

        指针存放有变量的地址，可直接作用于变量的所有操作都可以作用在指针上，比如访问和修改变量。指针的大小随着计算
        机体系结构不同而不同：在32位机器上为32位，在64位机器上为64位。
        
        引用是既有对象的另一个名字（别名），引用本身并不占用内存。与指针不同，引用不能为空，也不能重新赋值指向另一
        块内存。
        



####static

        不考虑类，static的作用主要有3条：
        1.隐藏。所有未加static前缀的全局变量和函数都具有全局可见性。如果加了static，就会对其他源文件隐藏。
        2.默认初始化为0，包括未初始化的全局静态变量与局部静态变量。其实为初始化的全局变量也具备这一属性，因为未初始化的
        全局变量与未初始化的静态变量是存储在同一块区域内的（BBS段）
        3.保持局部变量内容的持久。静态局部变量的生存期为整个源程序，作用域仍与局部变量相同。
        
        类中static的作用：
        C++重用了static这个关键字，并赋予它与前面不同的含义：表示属于一个类而不是属于此类的任何特定对象的变量和函数。
        1.静态数据成员
                static数据成员独立于该类的任意对象而存在。当某个类的实例修改了该静态成员变量，其修改值为该类的其他所有
                实例可见。static数据成员必须在类定义体的外部定义（正好一次）。
        2.静态成员函数
                1）静态成员之间可以相互访问，包括静态成员函数访问静态数据成员和访问静态成员函数。静态成员函数不能访问非
                静态数据成员和非静态成员函数，非静态成员函数可以任意的访问静态数据成员和静态成员函数。
                
                2）由于没有this指针的额外开销，因此静态成员函数与类的非静态成员函数相比速度上会有少许提升。



####C++中const的作用

        const修饰的内容不可改变，被const修饰的（数据成员，参数，返回值，成员函数）都受到强制保护，可以预防意外的变动，能
        提高程序的健壮性。
        
      

####C++中，static、const以及static const成员变量的初始化

        在C++中，static静态成员变量不能在类的内部初始化。在类的内部只是声明，定义必须在类定义体的外部，通常在类的实现文
        件中初始化。
        
        在C++中，const成员也不能在类的定义处初始化，只能通过构造函数初始化列表进行，并且必须有构造函数。const数据成员只
        在某个对象生存期内是常量，而对整个类而言却是可变的。因为类可以创建多个对象，不同的对象其const数据成员的值可以不
        同。所以不能在类的声明中初始化const数据成员，因为类的对象没被创建时，编译器不知道const数据成员的值是什么。
        
        要想建立在整个类中都恒定的常量，应该用类中的枚举常量来实现，或者static const。
        
        class Test {
        public:
                Test()::a(0) {}
                enum {size1 = 100, size2 = 200};
        private:
                const int a;    // 只能在构造函数初始化列表中初始化
                static int b;   // 在类的实现文件中定义并初始化
                const static int c;     // 与static const int c;相同，c为整型，故也可在此处初始化，但仍需在定义体外进行
                                        // 定义，注意c为非整型时，不能在此处初始化，整型包括char、short、int、long
        };
        
        int Test::b = 0;        // static成员变量不能在构造函数初始化列表中初始化，因为它不属于某个对象
        const int Test::c = 0;  // 给const static成员变量赋值时，不需要加static修饰符，但要加const



####在C++_中使用const比使用#define有更多的优点。

        1）const常量有数据类型，而宏常量没有数据类型。编译器可以对前者进行安全类型检查。而对后者只进行字符替换，没有类
        型安全检查，并且在字符替换时可能会产生意想不到的错误。
        
        2）使用常量可能比使用#define导致产生更小的目标代码，这是因为预处理器“盲目地将宏名称BUFSIZE替换为其代替的值100”
        可能导致目标代码出现多份100的备份，但常量就不会出现这种情况。
        
        3）const还可以执行常量折叠（将常量表达式计算求值，并用求得的值来替换表达式），即编译器在进行编译时可以通过必要
        的计算把一个复杂的常量表达式缩减成简单的。




####二维数组

        声明与初始化：
        int ia[3][4] = {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9, 10, 11}
        };
        
        int ia[3][4] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        
        动态声明a[m][n]：
        int **a = new int* [m];
        for (int i = 0; i < m; i++)
                a[i] = new int[n];
                
        for (int i = 0; i  < m; i++)
                delete[] a[i];
        delete[] a;

        
