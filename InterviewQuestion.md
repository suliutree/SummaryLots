

####1.如下函数，在32bit系统foo(2^31-3)的值是：（）

        int foo(int x)
        {
            return x&-x;
        }
        A:0 B:1 C:2 D:3
        
        解答：2^31-3的值是26，这里要注意的是负数在其内存中用补码表示。答案选C。

<br>
####2.运算符优先级

        unsigned char i=0x80; 
        printf("0x%x\n", ~i>>3+1); 
        输出什么？
        
        解答：输出是 0xfffffff7，因为+的优先级高于>>。一元操作符~的操作数必须是整型，结果为操作数的二进制反码。
        如果去掉unsigned，则输出0x7

<br>
####3.静态对象是否调用构造函数？

        #include <iostream>
        using namespace std;
        class A
        {
        public:
            A() { cout << "A's Constructor Called " << endl;  }
        };
        class B
        {
            static A a;
        public:
            B() { cout << "B's Constructor Called " << endl; }
        };
        int main()
        {
            B b;
            return 0;
        }
        
        解答：输出 B's Constructor Called。
        以上程序只是调用了B的构造函数，没有调用A的构造函数。因为静态成员变量只是在类中声明，没有定义。静态成员变量必须
        在类外使用作用域标识符显示定义。
        
        如果我们没有显示定义静态成员变量a就试图访问它，编译会出错，比如下面的程序编译出错：
            #include <iostream>
            using namespace std;
            
            class A
            {
                int x;
            public:
                A() { cout << "A's constructor called " << endl;  }
            };
            
            class B
            {
                static A a;
            public:
                B() { cout << "B's constructor called " << endl; }
                static A getA() { return a; }
            };
            
            int main()
            {
                B b;
                A a = b.getA();
                return 0;
            }
        输出：Compiler Error: undefined reference to `B::a
        
        如果我们加上a的定义，那么上面程序就可以正常运行，
        注意：如果A是个空类，没有数据成员x，则就算B中的a未定义也还是能运行成功的，即可以访问A。
            #include <iostream>
            using namespace std;
            
            class A
            {
                int x;
            public:
                A() { cout << "A's constructor called " << endl;  }
            };
            
            class B
            {
                static A a;
            public:
                B() { cout << "B's constructor called " << endl; }
                static A getA() { return a; }
            };
            
            A B::a;  // definition of a
            
            int main()
            {
                B b1, b2, b3;
                A a = b1.getA();
                return 0;
            }
            
            输出：
                A's constructor called 
                B's constructor called 
                B's constructor called 
                B's constructor called
        上面的程序调用B的构造函数3次，但是只调用A的构造函数一次，因为静态成员变量被所有对象共享，这也是它被称为类变量
        的原因。同时，静态成员变量也可以通过类名直接访问，比如下面的程序没有通过任何类对象访问，只是通过类访问a
            int main()
            {
                // static member 'a' is accessed without any object of B
                A a = B::getA();
                return 0;
            }
        输出：A's constructor called

<br>
####4.下面的代码会报错吗？为什么？

        class A {
        public:
             int m;
             void print() {  cout << "A\n";  } 
        };
         A *pa = 0;
         pa->print();
         
         解答：正常输出。
         上面的代码可以这样理解：
            void print(A *this) {  cout << "A\n";  } 
            A *pa = 0;
            print_A();
        也就是：并不是类没有初始化就不能调用类的成员函数，如果成员函数只是简单的打印输出，没有调用类成员就不会报段错误。

<br>
####5.下面的代码输出是什么？

        char *c[] = {"ENTER","NEW","POINT","FIRST"};  
        char **cp[] = { c + 3 , c + 2 , c + 1 , c};  
        char ***cpp = cp;  
        int main(void)  
        {  
            printf("%s",**++cpp);  
            printf("%s",*--*++cpp+3);  
            printf("%s",*cpp[-2]+3);  
            printf("%s\n",cpp[-1][-1]+1);  
            return 0;  
        }  
        
        解答：
        c是一个指针数组，每个数组元素都是char*类型的指针，值分别是那些字符串（的首地址）：
            c[0] = "ENTER" 
            c[1] = "NEW" 
            c[2] = "POINT" 
            c[3] = "FIRST"
        而[]和*本质上是一样的运算，即c[i] = *(c+i)。
        
        c和c+i都是char*[]类型，它可以退化成char**类型，再看cp，它正好是char**的数组，来看它的值：
            cp[0] = c + 3 
            cp[1] = c + 2 
            cp[2] = c + 1 
            cp[3] = c
        引用后就有：cp[0][0] = *(c + 3) = "FIRST"，以此类推。
        
        cp是char **[]类型，它可以退化成char ***类型，看最后的cpp，它正是char***类型，它是一个指针变量，和上面两个不同，
        上面两个是数组。
        
        分析过后，解析便一目了然：
        printf("%s",**++cpp);
            ++cpp的值是cp+1，引用一次后是cp[1]再引用是*cp[1]=c[2]="POINT"，输出是"POINT"。
        printf("%s",*--*++cpp+3); 
            再++cpp的值是cp+2，引用一次是cp[2]=c+1，再对这进行--，减后是c再引用是c[0]="ENTER"再+3，字符串指针指到"ER"，
            输出是"ER"。
        printf("%s",*cpp[-2]+3);
            这时cpp的值是cp+2，cpp[-2]=*(cpp-2)=*(cp+2-2)=cp[0]=c+3，再引用是c[3]="FIRST",+3 字符串指针指到"ST"，输出
            是"ST"。
        printf("%s\n",cpp[-1][-1]+1);
            cpp还是cp+2，cpp[-1]=*(cpp-1)=*(cp+2-1)=cp[1]=c+2，再[-1]得*(c+2-1)=c[1]="NEW",+1字符串指针指到"EW"，输出
            是"EW"。
    
<br>
####6.结构体

        #include <stdio.h>
        struct data
        {
         int a;
         unsigned short b;
        };
        int main(void)
        {
         data mData;
         mData.b = 0x0102;
         char *pData = (char *)&mData;
         printf("%d %d", sizeof(pData), (int)(*(pData + 4)));
         return 0;
        }
        
        解答：输出 4 2
        一般变量都是从高到低分配内存地址，但对于结构体来说，结构体的成员在内存中顺序存放，所占内存地址依次增高，第一个
        成员处于低地址处，最后一个成员处于最高地址处，但结构体成员的内存分配不一定是连续的，编译器会对其成员变量依据前
        面介绍的 “对齐”原则进行处理。
        
        此题的分配图如下：
                            struct data
                            [       ]   <----pData
        前4个为int a        [       ]
                            [       ]
                            [       ]
        后2个为ushort b     [  0x02 ]   <----pData+4
                            [  0x01 ]
        
        除了栈以外，堆、只读数据区、全局变量地址增长方向都是从低到高的。
        
<br>
####7.改变string变量的值？

        #include <iostream>
        #include <string>
        using namespace std;
        
        void chg_str(string str) {
            str = "ichgit";
        }
        
        int main() {
            string s = "sarrr";
            chg_str(s);
            printf("%s\n", s.c_str());
            cout << s << endl;
            return 0;
        }
        
        解答：输出 “sarrr”
        string是传值参数，不能修改其值。要想改变string变量的值，可以改为传地址方式：
        
            #include <iostream>
            #include <string>
            using namespace std;
            
            void chg_str(string *str) {
                *str = "ichgit";
            }
            
            int main() {
                string s = "sarrr";
                chg_str(&s);
                printf("%s\n", s.c_str());
                cout << s << endl;
                return 0;
            }

<br>
####8.静态变量的输出

        #include <stdio.h>
        int sum(int a) {
            int c = 0;
            static int b = 3; // 只执行一次
            c++;
            b += 2;
            return (a + b + c);
        }
        int main() {
            int i;
            int a = 2;
            for(i = 0; i < 5; ++i) {
                printf("%d\n", sum(a));
            }
            return 0;
        }
        
        解答：输出 8 10 12 14 16
        存储在静态数据区的变量会在程序刚开始运行时就完成初始化，也是唯一的一次初始化，此后该初始化不再执行，相当于一次执行
        后就作废，静态局部变量保存了前次被调用后留下的值。

<br>
####9.返回值加const修饰的必要性

        下面两种写法有区别吗？
            int GetInt(void) 
            const int GetInt(void)
        
        如果是下面两种呢？A为用户自定义对象。
            A GetA(void)
            const A GetA(void)
            
        解答：没有任何区别。
        如果函数返回值采用“值传递方式”，由于函数会把返回值复制到外部临时的存储单元中，加const 修饰没有任何价值。所以，
        对于值传递来说，加const没有太多意义。
        
        所以：
            不要把函数int GetInt(void) 写成const int GetInt(void)。
            不要把函数A GetA(void) 写成const A GetA(void)。
        
        在编程中要尽可能多的使用const（比如函数参数采用const&修饰），这样可以获得编译器的帮助，以便写出健壮性的代码。

<br>
####10.C++中sizeof的特殊问题

    定义一个空的数据类型，里面没有任何成员变量和成员函数，对该类型求sizeof，得到的结果是多少？
        答：是1，为什么不是0？空类型的实例中不包含任何信息，本来求sizeof应该是0，但是当我们声明该类型的实例时，它必须在
        内存中占有一定的空间，否则无法使用这些实例（也就不能求sizeof了），至于占用多少内存，由编译器决定，Visual Studio
        中每个空类型的实例占用1字节的空间。
        
    如果在该类型中添加一个构造函数和析构函数，再求sizeof，得到的结果是多少？
        答：还是1。调用构造函数和析构函数只需要知道函数的地址即可，而这些地址只与类型相关，而与类型的实例无关，编译器也
        不会因为这两个函数而在实例内添加任何额外的信息。
        PS：不管添加的是构造函数还是析构函数还是其它任何类型的函数，都是这个结果。
        
    那如果把析构函数标记为虚函数呢？
        答：C++的编译器一旦发现一个类型中有虚函数，就会为该类型生成虚函数表，并在该类型的每一个实例中添加一个指向虚函数
        表的指针，在32位机器上，一个指针占4字节空间，因此求sizeof得到4；如果是64位则为8。

<br>
####11.普通PC栈有多大？有什么办法测试？

        #include <stdio.h>
        int main(){
            int a[1000000];//局部变量
            return 0;
        }
        编译运行后，发现溢出错误。
        
        #include <stdio.h>
        int a[1000000];//全局变量
        int main(){
            return 0;
        }
        编译运行后正常。
        
        再来复习一下由C/C++编译程序的内存分区：
        
        1、栈区(stack sagment)：由编译器自动分配释放，存放函数的参数的值，局部变量的值等。在Windows下，栈是向低地址扩
        展的数据结构，是一块连续的内存的区域。这句话的意思是栈顶的地址和栈的最大容量是系统预先规定好的，在Windows下，
        栈的大小是1M，如果申请的空间超过栈的剩余空间时，将提示stack overflow。因此，能从栈获得的空间较小。
        
        2、堆区(heap sagment) ： 一般由程序员分配释放，若程序员不释放，程序结束时可能由系统回收 。它与数据结构中的堆
        是两回事。堆是向高地址扩展的数据结构，是不连续的内存区域。这是由于系统是用链表来存储的空闲内存地址的，自然是
        不连续的，而链表的遍历方向是由低地址向高地址。堆的大小受限于计算机系统中有效的虚拟内存。由此可见，堆获得的空
        间比较灵活，也比较大。
        
        3、全局区(静态区)(data sagment)：全局变量和静态变量的存储区域是在一起的，程序结束后由系统释放。数据区的大小由
        系统限定，一般很大，Windows32位操作系统下可以达到2GB，因此不会溢出。32位操作系统的地址空间为4G，但是留给程序
        的只是2G，因为另外的2G留给操作系统自用。Windows Server 2003可以支持的全局变量空间达到3G。
        
        4、文字常量区：常量字符串就是放在这里的， 程序结束后由系统释放。
        
        5、程序代码区：存放函数体的二进制代码。
        
        综上所述，局部变量空间是很小的，我们开一个a[1000000]就会导致栈溢出；而全局变量空间一般比较大，因此大小超过1M
        的变量尽量声明为全局变量或者静态变量。

<br>
####12.申请很多变量，导致栈溢出怎么解决？

        两种解决方法：
        1）增大栈内存的大小。
        2）使用堆内存。
        
            第二种方法比较可行，比如可以将数组定义改成指针，然后动态申请内存；也可以将局部变量变为全局变量，或者将局部
        变量变为静态变量。
        
<br>
####13.堆排序的算法复杂度？快速排序的算法复杂度？快排的过程？其收敛条件？快排是稳定的吗？可改造为稳定的吗？

        堆排序在最好的情况下，平均情况下以及最坏情况下的时间复杂度均为 O(nlogn)，空间复杂度为 O(1)，不稳定
        
        快速排序平均情况下的时间复杂度是 O(nlogn)，最坏情况下为 O(n^2)，空间复杂度为 O(logn)，不稳定
        
        快速排序的过程：
        1）首先选取当前表中的某一个元素（假设是第一个元素）作为基准值对表进行划分，则必须将表中比基准值大的元素向右移动，
        比基准值小的元素向左移动，是的一趟Partition()操作之后，表中的元素被基准值一分为二。
        2）对表进行划分之后，然后对两个表进行同样的排序操作（即递归的调用快速排序算法进行排序）。
        
        如快速排序的原型为：void QuickSort(int array[], int left, int right);
        则其收敛条件为 left >= right
        
        能不能改造成稳定的，我觉得是不能，但不确定有没有其他方法。
        
        额外知识：
            稳定排序：直接插入排序，冒泡排序，二路归并排序，基数排序
            不稳定排序：简单选择排序，希尔排序，堆排序，快速排序
        
        
        
        


