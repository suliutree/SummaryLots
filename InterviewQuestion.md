

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
        
<br>
####14.归并排序是怎样的过程？归并排序的复杂度？

        归并排序的时间复杂度是 O(nlogn)，空间复杂度是 O(n)。
        
        归并排序的过程：
        1）假定待排序的表中有n个记录，则可视为n个有序的子表，每个子表长度为1，然后两两归并，得到[n/2]个长度为2或1的有序
        表；
        2）再进行两两归并，……如此重复，直到合并成一个长度为n的有序表为止，这种排序方法称为二路归并排序。

<br>
####15.遇到内存泄漏问题，一般会采取什么过程去找原因？

        针对大型程序而言：
        Windows平台下面Visual Studio调试器和 C 运行时（CRT）库为我们提供了检测和识别内存泄漏的有效方法，原理大致如下：
        内存分配要通过CRT在运行时实现，只要在分配内存和释放内存时分别做好记录，程序结束时对比分配内存和释放内存的记录
        就可以确定是不是有内存泄漏。
        
        避免内存泄漏：
            1）养成良好的习惯，确保malloc/new和free/delete配对；
            2）检测内存泄漏的关键原理就是检查malloc/new和free/delete是否匹配，一些检测内存泄漏的工具就是利用此原理。要
            做到这点，就是利用宏或者钩子，在用户程序与运行库之间加了一层，用于记录内存分配的情况。
 
<br>
####16.对字符串进行处理，字符串里面有连续的空格，写一个函数，去掉多余的空格

        函数如下：
        
        void DeleteRedundantBlank(char* str)
        {
        	if (str == NULL)
        		return;
        
        	int indexOfOrigin = 0;
        	int indexOfNew = 0;
        
        	while (str[indexOfOrigin] == ' ')
        		indexOfOrigin++;
        
        	while (str[indexOfOrigin] != '\0')
        	{
        		if (str[indexOfOrigin] == ' ')
        		{
        			str[indexOfNew] = str[indexOfOrigin];
        			int i = 1;
        			while (str[indexOfOrigin + i] == ' ')
        				i++;
        			indexOfOrigin += i;
        			indexOfNew++;
        		}
        		else
        		{
        			str[indexOfNew] = str[indexOfOrigin];
        			indexOfOrigin++;
        			indexOfNew++;
        		}
        	}
        
        	str[indexOfNew] = '\0';
        }

<br>
####17.构造函数的功能？

        构造函数是特殊的成员函数，与其他成员函数不同，构造函数和类同名，而且没有返回类型。一个类可以有多个构造函数，
        每个构造函数必须有与其他构造函数不同数目或类型的形参。
        
        构造函数的功能主要用于在类的对象创建时定义初始化的状态。

<br>
####18.析构函数的功能？释放的是哪里的内存？

        析构函数也是一个特殊的成员函数，它的作用于构造函数相反。析构函数不返回任何值，没有函数类型，也没有函数参数。
        因此它不能被重载。一个类可以有多个构造函数，但只能有一个析构函数。
        
        析构函数的功能主要是用于释放资源。

<br>
####19.迭代器失效

        vector迭代器失效测试
        
        void vectorTest()
        {
            vector<int> container;
            for (int i = 0; i < 10; i++)
            {
                container.push_back(i);
            }
        
            vector<int>::iterator iter;
             for (iter = container.begin(); iter != container.end(); iter++)
            {
                    if (*iter > 3)
                      container.erase(iter);
            }
        
             for (iter = container.begin(); iter != container.end(); iter++)
            {
                    cout<<*iter<<endl;
            }
        }
       
       会出现 Debug Assertion Failed! 的错误。
       
       对于序列式容器，比如vector，删除元素时，指向被删除元素之后的任何元素的迭代器都将失效。因为顺序容器的内存时连续
       分配的，删除一个元素会导致后面所有的元素向前移动一个位置。
       erase方法可以返回下一个有效的iterator，代码修改如下：
       
       void vectorTest()
        {
            vector<int> container;
            for (int i = 0; i < 10; i++)
            {
                container.push_back(i);
            }
        
            vector<int>::iterator iter;
            for (iter = container.begin(); iter != container.end(); )
            {
                    if (*iter > 3)
                      iter = container.erase(iter);    //erase的返回值是删除元素下一个元素的迭代器
                    else
                    {
                        iter++;
                    }
            }
        
             for (iter = container.begin(); iter != container.end(); iter++)
            {
                    cout<<*iter<<endl;
            }
        }
        
        输出：0 1 2 3

<br>
####20.对于：const char *p = "Hello World"; 和 char q[] = "Hello World";分别求长度和所占用的空间大小？

        strlen(p); // 11
        sizeof(p); // 4（这里求出的是指针所占用的内存，而不是字符串）
        
        strlen(q); // 11
        sizeof(q); // 12

<br>
####21.求一个数组中第k大的数？

        快速选择算法（quick selection algorithm）:
        
        int Partition(int array[], int left, int right)
        {
        	int pivot = array[right];
        
        	while (left != right)
        	{
        		while (array[left] < pivot && left < right)
        			++left;
        		if (left < right)
        			swap(array[left], array[right--]);
        
        		while (array[right] > pivot && left < right)
        			--right;
        		if (left < right)
        			swap(array[left++], array[right]);
        	}
        
        	return left;
        }
        
        int QuickSelect(int array[], int left, int right, int k)
        {
        	if (left >= right)
        		return array[left]; // 
        
        	int index = Partition(array, left, right);
        	int size = index - left + 1; // 
        	if (size == k)
        	{
        		return array[left + k - 1];
        	}
        	else if (size > k)
        	{
        		QuickSelect(array, left, index - 1, k);
        	}
        	else
        	{
        		QuickSelect(array, index + 1, right, k - size);
        	}
        }

<br>
####22.从源路径中读取一个文件，写入到目标路径文件中，写代码实现？

        C++实现：
            #include <fstream>
            #include <string>
            
            using namespace std;
            
            int main()
            {
            	ifstream infile("in.txt");
            	ofstream outfile("out.txt");
            
            	string s;
            
            	while (getline(infile, s))
            		outfile << s << endl;
            
            	return 0;
            }
        
        C语言实现：
            #include <stdio.h>
            #include <stdlib.h> // exit函数
            
            int main()
            {
            	FILE* fp1;
            	FILE* fp2;
            
            	if ( (fp1 = fopen("in.txt", "r")) == NULL )
            	{
            		printf("can not open the file!");
            		exit(0);// 表示非正常退出
            	}
            
            	fp2 = fopen("out.txt", "w");
            		
            	char ch;
            	while ( (ch = fgetc(fp1)) != EOF)
            		fputc(ch, fp2);
            
            	return 0;
            }
        
<br>
####23.new和malloc都是堆分配，malloc后返回一个地址例如为p，如果p++后再free(p)，是否会出问题？

    在VS中进行测试：
        #include <stdio.h>
        #include <stdlib.h>
        
        int main()
        {
        	int* p = (int *)malloc(sizeof(int)*100);
        
        	p++; // 会显示堆被损坏的错误
        	free(p);
        
        	return 0;
        }
        
    会丢失释放的一些具体信息，如释放内存大小等。

<br>
####24.程序填空

        #include <stdio.h>
        void test(void *data)
        {
                unsigned int value = 填空处;
                printf("%d\n", value);
        }
        void main()
        {
                unsigned int data = 10;
                test(&data);
        }
        
        A.*data     B.(unsigned int)*data       C.(unsigned *)data      D.*(unsigned int*)data
        
        解答：选D。

<br>
####25.TCP/IP协议栈各个层次及分别的功能

        网络接口层：这是协议栈的最低层，对应OSI（开放系统互联）的物理层和数据链路层，主要完成数据帧的实际发送与接收。
        
        网络层：处理分组在网络中的活动，例如路由选择和转发，这一层主要包括IP、ARP、ICMP协议。
        
        传输层：主要功能是提供应用程序之间的通信，这一层主要是TCP/UDP协议。
        
        应用层：用来处理特定的应用，针对不同的应用提供了不同的协议，例如进行文件传输时用到FTP协议，发送Email是用到SMTP等。

<br>
####26.求二叉树结点的最大距离

        计算一个二叉树的最大距离有两种情况：
        情况A：路径经过左子树的最深结点，通过根结点，再到右子树的最深结点；
        情况B：路径不穿过根结点，而是左子树或右子树的最大距离路径，取其大者。
        
        只要计算这两种情况的路径距离，并取其大者，就是该二叉树的最大距离。
        
                            1                                       1
                        /       \                               /
                    2               3                           2
                /       \       /       \                   /       \
                4       5       6       7                   3       4
            /                       \                   /               \
            8                       9                   5               6
                        情况A                                   情况B
        
        情况A及B需要不同的信息：A需要子树的最大深度，B需要子树的最大距离。需要函数能在一个结点同时计算及传回这两个信息。
        代码如下：
        
        struct BinaryTreeNode
        {
        	int m_nValue;
        	BinaryTreeNode* m_pLeft;
        	BinaryTreeNode* m_pRight;
        };
        
        struct Result 
        {
        	int nMaxDistance;
        	int nMaxDepth;
        };
        
        Result GetMaxDistance(BinaryTreeNode* pRoot)
        {
        	if (pRoot == NULL)
        	{
        		Result empty = {0, -1}; //最大深度初始化为-1的目的是让调用方+1后，把无子树结点最大深度置为0
        		return empty;
        	}
        
        	Result lhs = GetMaxDistance(pRoot->m_pLeft);
        	Result rhs = GetMaxDistance(pRoot->m_pRight);
        
        	Result result;
        	result.nMaxDepth = max(lhs.nMaxDepth + 1, rhs.nMaxDepth + 1);
        	result.nMaxDistance = max( max(lhs.nMaxDistance, rhs.nMaxDistance), lhs.nMaxDepth + rhs.nMaxDepth + 2);
        	return result;
        }
        
<br>
####27.用两个栈实现一个队列

        class MyQueue
        {
        public:
        	void enqueue(int value);
        	int dequeue();
        	bool isEmpty();
        
        private:
        	stack<int> inputStack;
        	stack<int> outputStack;
        };
        
        void MyQueue::enqueue(int value)
        {
        	inputStack.push(value);
        }
        
        int MyQueue::dequeue()
        {
        	int value;
        
        	if (!outputStack.empty())
        	{
        		value = outputStack.top();
        		outputStack.pop();
        		return value;
        	}
        
        	while (!inputStack.empty())
        	{
        		outputStack.push(inputStack.top());
        		inputStack.pop();
        	}
        
        	value = outputStack.top();
        	outputStack.pop();
        	return value;
        }
        
        bool MyQueue::isEmpty()
        {
        	return inputStack.empty() && outputStack.empty(); 
        }

<br>
####28.定义一个函数，实现左旋字符串，比如输入"abcdef"和2，则函数返回的结果为"cdefab"。

        void Reverse(char* pBegin, char* pEnd)
        {
            if (pBegin == NULL || pEnd == NULL)
                return;
            
            while (pBegin < pEnd)
            {
                char temp = *pBegin;
                *pBegin = *pEnd;
                *pEnd = temp;
                
                pBegin++;
                pEnd--;
            }
        }
        
        char* LeftRotate(char* pStr, int n)
        {
            if (pStr != NULL)
            {
                int length = strlen(pStr);
                if (length > 0 && n > 0 && n < length)
                {
                    char* pFirstStart = pStr;
                    char* pFirstEnd = pStr + n - 1;
                    char* pSecondStart = pStr + n;
                    char* pSecondEnd = pStr + length - 1;
                    
                    Reverse(pFirstStart, pFirstEnd);
                    Reverse(pSecondStart, pSecondEnd);
                    Reverse(pFirstStart, pSecondEnd);
                }
            }
            return pStr;
        }

<br>
####29.二叉树前序、中序和后序遍历的递归与非递归实现

        struct BinaryTreeNode
        {
            int m_nValue;
            BinaryTreeNode* m_pLeft;
            BinaryTreeNode* m_pRight;
        };
        
        前序遍历：
        1）递归实现
            
            void Preorder(BinaryTreeNode* pRoot)
            {
                if (pRoot == NULL)
                    return;
                printf("%d\t", pRoot->m_nValue);
                Preorder(pRoot->m_pLeft);
                Preorder(pRoot->m_pRight);
            }
            
        2）非递归实现
        
            void PreorderIteration(BinaryTreeNode* pRoot)
            {
                stack<BinaryTreeNode*> stack;
                BinaryTreeNode* p = pRoot; //遍历指针
                while (p || !stack.empty()) //栈不空或p不空时循环
                {
                    if (p != NULL)
                    {
                        stack.push(p);
                        printf("%d\t", p->m_nValue);
                        p = p->m_pLeft;
                    }
                    else
                    {
                        p = stack.top();
                        stack.pop();
                        p = p->m_pRight;
                    }
                }
            }
        
        
        中序遍历：
        1）递归实现
        
            void Inorder(BinaryTreeNode* pRoot)
            {
                if (pRoot == NULL)
                    return;
                Inorder(pRoot->m_pLeft);
                printf("%d\t", pRoot->m_nValue);
                Inorder(pRoot->m_pRight);
            }
                
        2）非递归实现
        
            void InorderIteration(BinaryTreeNode* pRoot)
            {
                stack<BinaryTreeNode*> stack;
                BinaryTreeNode* p = pRoot;
                while (p || !stack.empty())
                {
                    if (p != NULL)
                    {
                        stack.push(p);
                        p = p->m_pLeft;
                    }
                    else
                    {
                        p = stack.top();
                        stack.pop();
                        printf("%d\t", p->m_nValue);
                        p = p->m_pRight;
                    }
                }
            }
        
        
        后续遍历：
        1）递归实现
        
            void Postorder(BinaryTreeNode* pRoot)
            {
                if (pRoot == NULL)
                    return;
                Postorder(pRoot->m_pLeft);
                Postorder(pRoot->m_pRight);
                printf("%d\t", pRoot->m_nValue);
            }
            
        2）非递归实现
        
            void PostorderIteration(BinaryTreeNode* pRoot)
            {
                stack<BinaryTreeNode*> stack;
                BinaryTreeNode* p = pRoot;
                BinaryTreeNode* r = NULL; // 标记
                
                while (p || !stack.empty())
                {
                    if (p != NULL)
                    {
                        stack.push(p);
                        p = p->m_pLeft;
                    }
                    else
                    {
                        p = stack.top();
                        if (p->m_pRight && p->m_pRight != r)
                        {
                            p = p->m_pRight;
                            stack.push(p);
                            p = p->m_pRight;
                        }
                        else
                        {
                            p = stack.top();
                            stack.pop();
                            printf("%d\t", p->m_nValue);
                            r = p;
                            p = NULL;
                        }
                    }
                }
            }
            
<br>
####30.二叉树的层序遍历

        void LevelOrder(BinaryTreeNode* pRoot)
        {
            if (pRoot == NULL)
                return;
            
            queue<BinaryTreeNode*> queueTreeNode;
            queueTreeNode.push(pRoot);
            
            while (queueTreeNode.size() != 0)
            {
                BinaryTreeNode* pNode = queueTreeNode.front();
                queueTreeNode.pop();
                printf("%d\t", pNode->m_nValue);
                
                if (pNode->m_pLeft != NULL)
                    queueTreeNode.push(pNode->m_pLeft);
                if (pNode->m_pRight != NULL)
                    queueTreeNode.push(pNode->m_pRight);
            }
        }

<br>
####31.字符匹配算法KMP

        暴力匹配：
            int ViolentMatch(char* s, char* p)
            {
                int sLen = strlen(s);
                int pLen = strLen(p);
                int i = 0;
                int j = 0;
                
                while (i < sLen && j < pLen)
                {
                    if (s[i] == p[j])
                    {
                        i++;
                        j++;
                    }
                    else
                    {
                        i = i - j + 1;
                        j = 0;
                    }
                }
                
                if (j == pLen)
                    return i - j;
                else
                    return -1;
            }
        
        KMP算法：
        
            /*
            原始串：BBC ABCDAB ABCDABCDABDE
            匹配串：ABCDABD
             A B C D A B D
            -1 0 0 0 0 1 2
            BBC ABCDAB ABCDABCDABDE
                ABCDABD
            当字符串匹配到这里时 i = 10，j = 6，此时 j!=-1 而且当前字符不匹配
            执行 j = next[j]，j则为2，在执行下一步时会比较 s[10] 与 p[2]，如下：
            BBC ABCDAB ABCDABCDABDE
                    ABCDABD
            s[10]与p[2]不匹配，执行 j = next[j]，j则为0，下一步比较 s[10] 与 p[0]，如下：
            BBC ABCDAB ABCDABCDABDE
                      ABCDABD
            以此类推
            */
            int KMPSearch(char* s, char* p)
            {
                int sLen = strlen(s);
                int pLen = strlen(p);
                int i = 0;
                int j = 0;
                
                while (i < sLen && j < pLen)
                {
                    // 如果 j == -1（表示重新从子串的第一位开始比较） 或者当前字符匹配成功
                    if (j == -1 || s[i] == p[j])
                    {
                        i++;
                        j++;
                    }
                    else
                    {
                        j = next[j];
                    }
                }
                
                if (j == pLen)
                    return i - j;
                else
                    return -1;
            }
            
            
            void GetNext(char* p, int next[])
            {
                int pLen = strlen(p);
                next[0] = -1;
                int k = -1;
                int j = 0;
                
                while (j < pLen - 1)
                {
                    // p[k]表示前缀，p[j]表示后缀
                    if (k == -1 || p[j] == p[k])
                    {
                        ++k;
                        ++j;
                        next[j] = k;
                    }
                    else
                    {
                        k = next[k];
                    }
                }
            }
            
        参考我的数据结构与算法里的详细注释
        [KMPSearch]: <https://github.com/>
            
            
            
            
            
            
            
            
            
            
            
            
