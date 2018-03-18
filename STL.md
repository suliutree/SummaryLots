## STL


#### 内存分区

        1.堆：由程序员手动分配和释放，完全不同于数据结构中的堆，分配方式类似链表。由malloc（C语言）或new（C++）来分配，free
        （C语言）和delete（C++）释放。若程序员不释放，程序结束时由系统释放。
        
        2.栈：由编译器自动分配和释放，存放函数的参数值、局部变量的值等。操作方式类似数据结构中的栈。
        
        3.全局（静态）存储区：存放全局变量和静态变量。包括DATA段（全局初始化区）与BSS段（全局未初始化区）。其中，初始化的全局
        变量和静态变量存放在DATA段，未初始化的全局变量和静态变量存放在BSS段。程序结束后有系统释放。
        其中BSS段的特点是：在程序执行之前BSS段会自动清0。所以，未初始化的全局变量和静态变量在程序执行之前就已经成0了。
        
        4.文字常量区：常量字符串就放在这里，程序结束后由系统释放。
        
        5.程序代码区：存放函数体的二进制代码。
        

<br>

#### vector

        1.vector头文件：#include <vector>
        
        2.vector在头文件中定义如下：
        namespace std {
                template <class T, class Allocator = allocator<T> >
                class vector;
        }
        vector的元素可以是任意类型T，但必须具备assignable（可赋值的）和copyable（可赋值的）两个性质。第二个template参数可
        有可无，用来定义内存模型，缺省的模型是C++标准程序库提供的allocator。
        
        3.在末端添加或删除元素时，vector的性能相当好。可是如果你在前端或中部安插或删除元素，性能就不怎么样了，因为操作点之
        后的每一个元素都必须移动到另一个位置，而每一次移动都得调用assignment操作符。
        
        4.vector性能优异的秘籍之一就是配置比其所容纳的元素所需更多的内存。当vector申请的内存被用尽时，vector会重新申请一片
        新的内存，通常新申请的内存会是原来内存的两倍.一旦内存重新配置，和vector元素相关的所有references，pointers，iterators
        都会失效。
        
        5.vector各项操作：
                vector<Elem> c                  产生一个空的vector
                vector<Elem> c1(c2)             产生另一个同型的vector的副本
                vector<Elem> c(n)               利用元素的default构造函数生成一个大小为n的vector
                vector<Elem> c(n, elem)         产生一个大小为n的vector，每个元素的值都是elem
                vector<Elem> c(begin, end)      产生一个vector，以区间[begin, end)作为元素初值
                c.~vector<Elem>()               销毁所有元素并释放内存
                
                c.size()        返回当前元素的数量
                c.empty()       判断vector是否为空
                c.max_size()    返回可容纳的元素的最大值
                c.capacity()    返回重新分配空间前所能容纳的元素最大数量
                c.reserve()     如果vector容量不足，扩大之
                c1 compare c2   compare可为 ==, !=, <, >, <=, >=
                
                c1 = c2                 将c2全部元素赋值给c1
                c.assign(n, elem)       复制n个elem，赋值给c
                c.assign(beg, end)      将区间[begin, end)内的元素赋值给c
                c1.swap(c2)             将c1和c2元素互换
                
                c.at(index)     返回索引index所标示的元素，如果index越界，则抛出out_of_range的异常
                c[index]        返回索引index所表示的元素，不进行范围检查
                c.front()       返回第一个元素，不检查元素是否存在
                c.back()        返回最后一个元素，不检查元素是否存在
                
                c.begin()       返回一个随机存取迭代器，指向第一个元素
                c.end()         返回一个随机存取迭代器，指向最后一个元素的下一个位置
                c.rbegin()      返回一个逆向迭代器，指向逆向迭代的第一个元素
                c.rend()        返回一个逆向迭代器，指向逆向迭代的最后一个元素的下一个位置
                vector迭代器持续有效，除非发生两种情况：
                        1.使用者在一个较小的索引位置上安插或移动元素
                        2.由于容量变化而引起的内存重新分配
                        
                c.insert(it, elem)              在it位置上插入一个elem副本并返回新元素的位置
                c.insert(it, n, elem)           在it位置上插入n个elem副本，无返回值
                c.insert(it, begin, end)        在it位置上插入区间[begin, end)内的所有元素的副本，无返回值
                c.push_back(elem)               在尾部添加一个elem副本
                c.pop_back()                    移除最后一个元素（不回传）
                c.erase(it)                     移除it位置上的元素，返回下一个元素的位置
                c.erase(begin, end)             移除区间[begin, end)区间内的所有元素，返回下一个元素的位置
                c.resize(num)                   将元素数量改为num（如果size()变大了，多出来的新元素都需以default构造函数构造完成）
                c.resize(num, elem)             将元素数量改为num（如果size()变大了，多出来的新元素都是elem的副本）
                c.clear()                       将容器清空
                

<br>

#### stack

        1.stack头文件：#include <stack>
        
        2.stack在头文件中定义如下：
        namespace std {
                template <class T, class Container = deque<T> >
                class stack;
        }
        参数T代表stack的元素类型，带有默认值的第二个参数用来定义stack内部存放元素所用的实际容器，缺省采用deque。之所以采用
        deque而不是vector，是因为deque移除元素时会释放内存并且不必在重新分配时复制全部元素。实际上stack只是很单纯的把各项
        操作转化为内部容器的对应调用，你可以使用任何序列式容器来支持stack，只要他们支持back()，push_back()，pop_back()即可。
        
        由于stack系以底部容器完成其所有工作，所以往往不被归类为container（容器），而被归类为container adapter（配接器）。
        
        stack没有迭代器。
        
        3.stack的各项操作：
                
                stack::stack()  默认构造函数，产生一个空的stack
                
                explicit stack::stack(const Container& cont)    产生一个stack，并以容器cont内的元素为初值（复制）
                
                size_type stack::size() const   返回元素个数
                
                bool stack::empty() const       判断stack是否为空
                
                void stack::push(const value_type& elem)        将elem副本插入stack使其成为新的第一个元素
                
                value_type& stack::top()
                const value_type& stack::top() const    返回stack栈顶元素，调用者必须保证stack不为空，否则可能有未定义行为
                
                void stack::pop()       移除stack栈顶元素，调用者必须确保stack不为空，否则可能是未定义行为
                
                bool comparison(const stack& st1, const stack& st2)     返回两个同型stack的比较结果comparison可以是
                                                        operator=，operator!=，operator<， operator>，operator<=，operator>=
        

<br>

#### priority_queue

        1.priority_queue头文件：#include <queue>
        
        2.priority_queue在头文件中定义如下：
        namespace std {
                template <class T, class Container = vector<T>, class Compare = less<typename Container::value_type> >
                class priority_queue;
        }
        第一个参数T表示元素类型，第二个参数用来定义priority_queue内部存放元素所用的实际容器，默认采用vector。第三个参数定
        义出“用以搜索下一个最高优先元素”的排序准则，缺省下是以 operator < 作为比较准则。实际上priority_queue只是很单纯的
        把各项操作转化为内部容器对应的调用，你可以使用任何序列式容器来支持priority_queue，只要它们支持随机迭代器和front()，
        push_back()，pop_back()等动作就行。由于priority_queue需要用到STL heap算法，所以其内部容器必须支持随机存取迭代器。
        
        priority_queue没有迭代器。
        
        3.priority_queue各项操作：
        priori_queue::priority_queue()  默认构造函数，产生一个空的priority_queue
        
        explicit priority_queue::priority_queue(const ComFunc& op)      
        产生一个priority_queue，以op为排序准则
        
        priority_queue::priority_queue(const ComFunc& op, const Container& cont)        
        产生一个priority_queue，以op为排序准则，并以容器cont内的元素为初值（复制）
                                                                                        
        priority_queue::priority_queue(InputIterator beg, InputIterator end)    
        产生一个priority_queue，以区间[beg, end)内的元素为初值
                                                                                
        priority_queue::priority_queue(InputIterator beg, InputIterator end, const ComFunc& op, const Container& cont)
        产生一个priority_queue，以区间[beg, end)内的元素为初值，以op为排序准则及容器cont内的元素为初值
        
        size_type priority_queue::size() const  返回元素个数
        
        bool priority_queue::empty() const      判断priority_queue是否为空
        
        void priority_queue::push(const value_type& elem)       将elem的副本插入priority_queue
        
        const value_type& priority_queue::top() const   返回priority_queue的“下一个元素”，调用者必须确保priority_queue不
                                                        为空，否则可能出现未定义的行为
                                                        
        void priority_queue::pop()      移除priority_queue的“下一个”元素，调用者必须保证priority_queue不为空，否则可能出现
                                        未定义行为


<br>

#### set/multiset

        1.set/multiset头文件：#include <set>
        
        2.set/multiset在头文件中的定义：
        namespace std {
                template <class T, class Compare = less<T>, class Allocator = allocator<T> >
                class set;
                
                template <class T, class Compare = less<T>, class Allocator = allocator<T> >
                class multiset;
        }
        只要T是assignable、copyable、comparable的类型，都可以成为set或multiset的元素类型。
        
        multiset的特性以及用法和set完全相同，唯一的差别在于它允许键值重复。
        
        set/multiset的排序准则必须是strict weak ordering（严格弱序化），其意义是：
                1）必须是反对称的，对判断式op而言，如果op(x,y)为真，则op(y,x)为假。
                2）必须是可传递的，如果op(x,y)为真且op(y,z)为真则op(x,z)。
                3）必须是非自反的，op(x,x)永远为假。
                
        3.set/multiset通常都是以平衡二叉树来实现的，事实上set/multiset的实现版本大多以红黑树来实现，它保证结点安插时最
        多只会做两个重新连接动作，而且到达某一元素的最长路径最多只是最短路径深度的两倍。
        
        4.set/multiset的各项操作：
        set c                   产生一个空set/multiset
        set c(op)               以op为排序准则产生一个空set/multiset
        set c1(c2)              产生某一个set/multiset的副本
        set c(beg, end)         以区间[beg, end)内的元素产生一个set/multiset
        set c(beg, end, op)     以op为排序准则，以区间[beg, end)内的元素产生一个set/multise
        c.~set()                销毁所有元素，释放内存
        其中set可为下列形式：set<Elem>、set<Elem, op>、multiset<Elem>、multiset<Elem, op>
        
        c.size()        返回当前的元素数量
        c.empty()       判断c是否为空
        c.max_size()    返回可容纳的元素最大数值
        c1 compare c2   compare可为==，!=，<，>，<=和>=
        
        c.count(elem)           返回“元素值为elem”的元素个数
        c.find(elem)            返回“元素值为elem”的第一个元素的迭代器，如果找不到就返回end()
        c.lower_bound(elem)     返回elem的第一个可安插位置，也就是“元素值>=elem”的第一个元素位置
        c.upper_bound(elem)     返回elem的最后一个可安插位置，也就是“元素值>elem”的第一个元素位置
        c.equal_range(elem)     返回elem的第一个和最后一个位置，也就是“元素值==elem”的第一个元素区间，返回值为将
                                lower_bound()和upper_bound()的返回值做成一个pair返回
                                
        c1 = c2         将c2全部元素赋值给c1
        c1.swap(c2)     将c1和c2元素互换
        
        c.begin()       返回一个双向存取迭代器（将元素视为常数），指向第一个元素
        c.end()         返回一个双向存取迭代器（将元素视为常数），指向最后元素的下一个位置
        c.rbegin()      返回一个逆向迭代器，指向逆向迭代的第一个元素
        c.rend()        返回一个逆向迭代器，指向逆向迭代的最后元素的下一个位置
        
        c.insert(elem)          插入一个elem副本并返回新元素的位置
        c.insert(it, elem)      插入一个elem副本并返回新元素的位置（it是一个提示指出安插操作的搜寻起点）
        c.insert(beg, end)      插入区间[beg, end)内的所有元素副本，无返回值
        c.erase(elem)           移除“与elem相等”的所有元素，返回被移除元素的个数
        c.erase(it)             移除it位置上的元素，无返回
        c.erase(beg, end)       移除[beg, end)区间内的所有元素，无返回
        c.clear()               将容器清空
        
        set提供如下接口：
        pair<iterator, bool> insert(const value_type& elem);
                pair结构中的second成员表示安插是否成功；first成员返回新元素的位置或返回现存的同值元素位置
        iterator insert(iterator pos_hint, const value_type& elem);
        
        multiset提供如下接口：
        iterator insert(const value_type& elem);
        iterator insert(iterator pos_hint, const value_type& elem);
        
        example
        using C++ 11:
            std::set<std::string> str = {"John", "Kelly", "Amanda", "Kim"};
        Otherwise:
            std::string tmp[] = {"John", "Kelly", "Amanda", "Kim"};
            std::set<std::string> str(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));


<br>

#### map/multimap

        1.map/multimap头文件：#include <map>
        
        2.map/multimap在头文件中的定义：
        namespace std {
                template <class key, class T, class Compare = less<key>, 
                          class Allocator = allocator<pair<const key, T> > >
                class map;
                
                template <class key, class T, class Compare = less<key>, 
                          class Allocator = allocator<pair<const key, T> > >
                class multimap;
        }
        第一个template参数为元素的key，第二个参数为元素的value。key和value必须具备assignable和copyable的性质，对排序而言
        key必须是comparable。第三个参数为排序准则，这个排序准则必须是strict weak ordering的,元素的次序由他们的key决定，
        和value无关，map/multimap根据元素的key自动对元素进行排序。
        
        和所有关联式容器一样，map/multimap通常以平衡二叉树来完成。
        
        3.map/multimap的各项操作：
        map c                   产生一个空map/multimap
        map c(op)               以op为排序准则产生一个空map/multimap
        map c1(c2)              产生某一个map/multimap的副本
        map c(begin, end)       以区间[begin, end)的元素产生一个map/multimap
        map c(begin, end, op)   以op为排序准则，以区间[beg, end)内的元素产生一个map/multimap
        c.~map()                销毁所有元素，释放内存
        其中map可为下列形式：map<Key, Elem>、map<Key, Elem, op>、multimap<Key, Elem>、multimap<Key, Elem, op>
        
        c.size()        返回当前元素的数量
        c.empty()       判断c是否为空
        c.max_size()    返回可容纳的元素最大数值
        c1 compare c2   compare可为==，!=，<，>，<=，>=
        
        c.count(elem)           返回“键值等于key”的元素个数
        c.find(elem)            返回“键值等于key”的第一个元素的迭代器，如果找不到就返回end()
        c.lower_bound(key)      返回“键值为key”之元素的第一个可安插位置，也就是“键值>=key”的第一个元素位置
        c.upper_bound(key)      返回“键值为key”之元素的最后一个可安插位置，也就是“键值>key”的第一个元素位置
        c.equal_range(key)      返回“键值为key”之元素的第一个和最后一个可安插位置，也就是“键值==key”的元素区间
        lower_bound()、upper_bound()和equal_range()行为与set相应的函数十分相似，唯一不同的是：元素是一个key/value pair。
        
        c1 = c2         将c2全部元素赋值给c1
        c1.swap(c2)     将c1和c2元素互换
        
        c.begin()       返回一个双向存取迭代器（将key视为常数），指向第一个元素
        c.end()         返回一个双向存取迭代器（将key视为常数），指向最后元素的下一个位置
        c.rbegin()      返回一个逆向迭代器，指向逆向迭代的第一个元素
        c.rend()        返回一个逆向迭代器，指向逆向迭代的最后元素的下一个位置
        这里的元素是一个key/value pair（pair<const key, T>）。
        
        c.insert(elem)          插入一个elem副本并返回新元素的位置
        c.insert(it, elem)      安插elem副本返回新元素的位置（it是一个提示指出安插操作的搜寻起点）
        c.insert(beg, end)      插入区间[beg, end)内的所有元素副本，无返回值
        c.erase(elem)           移除“value与elem相等”的所有元素，返回被移除元素的个数
        c.erase(it)             移除it位置上的元素，无返回
        c.erase(beg, end)       移除[beg, end)区间内的所有元素，无返回
        c.clear()               将容器清空
        这里的元素是一个key/value pair（pair<const key, T>）。


<br>

#### string类（属于C++标准库，不属于STL，但其是STL兼容的，可以应用迭代器，算法）

        1.string类头文件：#include <string>
        
        2.string类的各项操作：
        string(const char *s);          用char类型字符串s初始化字符串
        string(int n, char c);           用n个字符c初始化字符串
        string类支持默认的构造函数和复制构造函数，如string s1，string s2 = "abc"，都是正确的写法
        当构造string太长而无法表达时会抛出length_error异常
        
        const char &operator[](int n) const;
        const char &at(int n) const;
        char &operator[](int n);                返回当前字符串中第n个字符的位置，不提供范围检查
        char &at(int n);                        返回当前字符串中第n个字符的位置，提供范围检查，若越界则抛出out_of_range异常
        const char *data() const;               返回一个非null终止的c字符数组
        const char *c_str() const;              返回一个以null终止的c字符数组
        int copy(char *s, int n, int pos = 0) const;    把当前串中以pos开始的n个字符拷贝到以s为起始位置的字符数组中，
                                                        返回实际拷贝的数目
                                                        
        int capacity() const;           返回当前容量
        int max_size() const;           返回string对象中可存放的最大字符串的长度
        int size() const;               返回当前字符串的大小
        int length() const;             返回当前字符串的长度
        bool empty() const;             判断当前字符串是否为空
        void resize(int len,char c);    把字符串当前大小置为len，并用字符c填充不足的部分
        
        string类重载运算符operator>>用于输入，同样重载运算符operator<<用于输出操作。
        getline(istream &in,string &s);         从输入流in中读取字符串到s中，以换行符'\n'分开
        
        string &operator=(const string &s);     把字符串s赋给当前字符串
        string &assign(const char *s);          用char类型字符串s赋值
        string &assign(const char *s,int n);    用char字符串s开始的n个字符赋值
        string &assign(const string &s);        把字符串s赋给当前字符串
        string &assign(int n,char c);           用n个字符c赋值给当前字符串
        string &assign(const string &s,int start,int n);                把字符串s中从start开始的n个字符赋给当前字符串
        string &assign(const_iterator first,const_itertor last);        把first和last迭代器之间的部分赋给字符串
        
        string &operator+=(const string &s);            把字符串s连接到当前字符串的结尾
        string &append(const char *s);                  把char类型字符串s连接到当前字符串结尾
        string &append(const char *s,int n);            把char类型字符串s的前n个字符连接到当前字符串结尾
        string &append(const string &s);                把字符串s连接到当前字符串的结尾
        string &append(const string &s,int pos,int n);  把字符串s中从pos开始的n个字符连接到当前字符串的结尾
        string &append(int n,char c);                   在当前字符串结尾添加n个字符c
        string &append(const_iterator first,const_iterator last);       把迭代器first和last之间的部分连接到当前字符串的结尾
        
        bool operator==(const string &s1,const string &s2) const;       比较两个字符串是否相等
        运算符">","<",">=","<=","!="均被重载用于字符串的比较；
        int compare(const string &s) const;                             比较当前字符串和s的大小
        int compare(int pos, int n,const string &s)const;               比较当前字符串从pos开始的n个字符组成的字符串与s的大小
        int compare(int pos, int n,const string &s,int pos2,int n2)const;       比较当前字符串从pos开始的n个字符组成的字符串
                                                                                与s中pos2开始的n2个字符组成的字符串的大小
        int compare(const char *s) const;
        int compare(int pos, int n,const char *s) const;
        int compare(int pos, int n,const char *s, int pos2) const;      同上，只不过字符串s变为了char类型的字符数组
        compare函数在>时返回1，<时返回-1，==时返回0
        
        string substr(int pos = 0,int n = npos) const;  返回pos开始的n个字符组成的字符串
        void swap(string &s2);                          交换当前字符串与s2的值
        
        int find(char c, int pos = 0) const;                    从pos开始查找字符c在当前字符串的位置
        int find(const char *s, int pos = 0) const;             从pos开始查找字符串s在当前串中的位置
        int find(const char *s, int pos, int n) const;          从pos开始查找字符串s中前n个字符在当前串中的位置
        int find(const string &s, int pos = 0) const;           从pos开始查找字符串s在当前串中的位置
        查找成功时返回所在位置，失败返回string::npos的值 
        int rfind(char c, int pos = npos) const;                从pos开始从后向前查找字符c在当前串中的位置
        int rfind(const char *s, int pos = npos) const;
        int rfind(const char *s, int pos, int n = npos) const;
        int rfind(const string &s,int pos = npos) const;
        从pos开始从后向前查找字符串s中前n个字符组成的字符串在当前串中的位置，成功返回所在位置，失败时返回string::npos的值 
        int find_first_of(char c, int pos = 0) const;           从pos开始查找字符c第一次出现的位置
        int find_first_of(const char *s, int pos = 0) const;
        int find_first_of(const char *s, int pos, int n) const;
        int find_first_of(const string &s,int pos = 0) const;
        从pos开始查找当前串中第一个在s的前n个字符组成的数组里的字符的位置。查找失败返回string::npos 
        int find_first_not_of(char c, int pos = 0) const;
        int find_first_not_of(const char *s, int pos = 0) const;
        int find_first_not_of(const char *s, int pos,int n) const;
        int find_first_not_of(const string &s,int pos = 0) const;
        从当前串中查找第一个不在串s中的字符出现的位置，失败返回string::npos 
        int find_last_of(char c, int pos = npos) const;
        int find_last_of(const char *s, int pos = npos) const;
        int find_last_of(const char *s, int pos, int n = npos) const;
        int find_last_of(const string &s,int pos = npos) const; 
        int find_last_not_of(char c, int pos = npos) const;
        int find_last_not_of(const char *s, int pos = npos) const;
        int find_last_not_of(const char *s, int pos, int n) const;
        int find_last_not_of(const string &s,int pos = npos) const;
        find_last_of和find_last_not_of与find_first_of和find_first_not_of相似，只不过是从后向前查找
        
        string &replace(int p0, int n0,const char *s);          删除从p0开始的n0个字符，然后在p0处插入串s
        string &replace(int p0, int n0,const char *s, int n);   删除p0开始的n0个字符，然后在p0处插入字符串s的前n个字符
        string &replace(int p0, int n0,const string &s);        删除从p0开始的n0个字符，然后在p0处插入串s
        string &replace(int p0, int n0,const string &s, int pos, int n);        删除p0开始的n0个字符，然后在p0处插入串s中
                                                                                从pos开始的n个字符
        string &replace(int p0, int n0,int n, char c);          删除p0开始的n0个字符，然后在p0处插入n个字符c
        string &replace(iterator first0, iterator last0,const char *s);         把[first0，last0）之间的部分替换为字符串s
        string &replace(iterator first0, iterator last0,const char *s, int n);  把[first0，last0）之间的部分替换为s的前n
                                                                                个字符
        string &replace(iterator first0, iterator last0,const string &s);       把[first0，last0）之间的部分替换为串s
        string &replace(iterator first0, iterator last0,int n, char c);         把[first0，last0）之间的部分替换为n个字符c
        string &replace(iterator first0, iterator last0,const_iterator first, const_iterator last);
        把[first0，last0）之间的部分替换成[first，last）之间的字符串
        
        string &insert(int p0, const char *s);
        string &insert(int p0, const char *s, int n);
        string &insert(int p0,const string &s);
        string &insert(int p0,const string &s, int pos, int n);
        前4个函数在p0位置插入字符串s中pos开始的前n个字符
        string &insert(int p0, int n, char c);          此函数在p0处插入n个字符c
        iterator insert(iterator it, char c);           在it处插入字符c，返回插入后迭代器的位置
        void insert(iterator it, const_iterator first, const_iterator last);    在it处插入[first，last）之间的字符
        void insert(iterator it, int n, char c);        在it处插入n个字符c
        
        iterator erase(iterator first, iterator last);  删除[first，last）之间的所有字符，返回删除后迭代器的位置
        iterator erase(iterator it);                    删除it指向的字符，返回删除后迭代器的位置
        string &erase(int pos = 0, int n = npos);       删除pos开始的n个字符，返回修改后的字符串
        
        string类提供了向前和向后遍历的迭代器iterator，迭代器提供了访问各个字符的语法，类似于指针操作，迭代器不检查范围。
        用string::iterator或string::const_iterator声明迭代器变量，const_iterator不允许改变迭代的内容。常用迭代器函数有：
        const_iterator begin()const;
        iterator begin();               返回string的起始位置
        const_iterator end()const;
        iterator end();                 返回string的最后一个字符后面的位置
        const_iterator rbegin()const;
        iterator rbegin();              返回string的最后一个字符的位置
        const_iterator rend()const;
        iterator rend();                返回string第一个字符位置的前面
        
        
<br>

#### STL中的算法

        1.使用STL中的算法，要包含头文件<algorithm>，某些STL算法用于数值处理，因此被定义于头文件<numeric>。
        
        2.所有STL算法都被设计用来处理一个或多个迭代器区间，第一个区间通常以起点和终点表示，至于其他区间，多数情况下只需
        提供起点足矣，其终点可以自动以第一个区间的元素数量推断出来，调用者必须保证这些区间的有效性。
        STL使用覆盖模式而非安插模式，所以调用者必须保证目标区间拥有足够的元素空间，当然也可以采用特殊的安插型迭代器将覆
        盖模式变为安插模式。
        
        3.尾词_if：如果算法有两种形式，参数个数都相同，但第一形式的参数要求传递一个值，第二形式的参数要求传递一个函数或
        仿函数，那么尾词_if就派上了用场，无尾词的那个要求传递数值，有尾词的那个要求传递函数或仿函数。不过并非所有“要求传
        递仿函数”的算法都有尾词_if，如果算法以额外参数来接受这样的函数或仿函数，那么不同版本的算法就可以采用相同的命名。
        尾词_copy：这个尾词用来表示在此算法中，元素不光被操作，还会被复制到目标区间。
        
        4.for_each()算法：UnaryProc for_each (InputIterator beg, InputIterator end, UnaryProc op);
                1）对区间[beg, end)中的每一个元素调用op(elem)
                2）返回op（已在算法内部被变动过）的一个副本
                3）op的任何返回值都会被忽略
                4）op可以变动元素
                5）复杂度：线性
        
        5.元素计数算法：
        difference_type count (InputIterator beg, InputIterator end, const T& value);
        difference_type count_if (InputIterator beg, InputIterator end, UnaryPredicate op);
        1）第一种形式会计算区间[beg, end)中的元素等于value的元素个数
        2）第二种形式会计算区间[beg, end)中令以下一元判断式结果为true的元素个数：op(elem)
        3）返回值型别为difference_type，是表现迭代器间距的型别
        4）注意op在函数调用过程中不应该改变自身状态
        5）op不应该改动传进来的参数
        6）关联式容器（set/multiset，map/multimap）提供了一个等效的成员函数count()用来计算等于某个value或key的元素个数
        7）时间复杂度：线性
        
        6.最大值最小值算法：
        InputIterator min_element (InputIterator beg, InputIterator end);
        InputIterator min_element (InputIterator beg, InputIterator end, CompFunc op);
        InputIterator max_element (InputIterator beg, InputIterator end);
        InputIterator max_element (InputIterator beg, InputIterator end, CompFunc op);
        1）所有这些算法都返回区间[beg, end)中的最大或最小值的位置
        2）上述无op参数版本以operator<进行元素比较
        3）op用来比较两个元素：op(elem1, elem2)如果第一个元素小于第二个元素，应当返回true
        4）如果存在多个最大或最小值，上述算法返回找到的第一个最大或最小值
        5）op不应该改动传进去的参数
        6）时间复杂度：线性
        
        7.搜寻元素算法：
        InputIterator find (InputIterator beg, InputIterator end, const T& value);
        InputIterator find_if (InputIterator beg, InputIterator end, UnaryPredicate op);
        1）第一种形式返回区间[beg, end)中的第一个“元素值等于value”的元素位置
        2）第二种形式返回区间[beg, end)中令一元判断式op(elem)结果为true的第一个元素的位置
        3）如果没有找到匹配元素，两种形式都返回end
        4）注意op在函数调用过程中不应该改变自身状态
        5）op不应该改动传进来的参数
        6）如果是已序区间，应使用lower_bound()，upper_bound()，equal_range()或binary_search()算法以获取更高的性能
        7）关联式容器（set/multiset，map/multimap）提供了一个等效的成员函数find()，拥有对数时间复杂度
        8）时间复杂度：线性
        
        InputIterator search_n (InputIterator beg, InputIterator end, Size count, const T& value);
        InputIterator search_n (InputIterator beg, InputIterator end, Size count, const T& value, BinaryPredicate op);
        1）第一种形式返回区间[beg, end)中的第一组“连续count个元素值全等于value”的元素位置
        2）第二种形式返回区间[beg, end)中的第一组“连续count个元素使op(elem, value)结果为true”的元素位置
        3）如果没有找到匹配元素，两种形式都返回end
        4）注意op在函数调用过程中不应该改变自身状态
        5）op不应该改动传进来的参数
        7）时间复杂度：线性
        
        ForwardIterator1 search (ForwardIterator1 beg, ForwardIterator1 end, 
                                        ForwardIterator2 searchBeg, ForwardIterator2 searchEnd);
        ForwardIterator1 search (ForwardIterator1 beg, ForwardIterator1 end, 
                                        ForwardIterator2 searchBeg, ForwardIterator2 searchEnd, BinaryPredicate op);
        1）两种形式都返回区间[beg, end)内“和区间[searchBeg, searchEnd)完全吻合”的第一个子区间内的第一个元素位置
        2）第一种形式中，子区间元素必须完全等于[searchBeg, searchEnd)的元素
        3）第二种形式中，子区间元素和[searchBeg, searchEnd)的对应元素必须使op(elem, searchElem)结果为true
        4）如果没有找到匹配子区间，两种形式都返回end
        5）注意op在函数调用过程中不应该改变自身状态
        6）op不应该改动传进来的参数
        7）时间复杂度：线性
        
        ForwardIterator find_end (ForwardIterator beg, ForwardIterator end, 
                                        ForwardIterator searchBeg, ForwardIterator searchEnd);
        ForwardIterator find_end (ForwardIterator beg, ForwardIterator end, 
                                        ForwardIterator searchBeg, ForwardIterator searchEnd, BinaryPredicate op);
        1）两种形式都返回区间[beg, end)内“和区间[searchBeg, searchEnd)完全吻合”的最后一个子区间内的第一个元素位置
        2）第一种形式中，子区间元素必须完全等于[searchBeg, searchEnd)的元素
        3）第二种形式中，子区间元素和[searchBeg, searchEnd)的对应元素必须使op(elem, searchElem)结果为true
        4）如果没有找到匹配子区间，两种形式都返回end
        5）注意op在函数调用过程中不应该改变自身状态
        6）op不应该改动传进来的参数
        7）时间复杂度：线性
        
        ForwardIterator find_first_of (ForwardIterator1 beg, ForwardIterator1 end, 
                                                ForwardIterator2 searchBeg, ForwardIterator2 searchEnd);
        ForwardIterator find_first_of (ForwardIterator1 beg, ForwardIterator1 end, 
                                                ForwardIterator2 searchBeg, ForwardIterator2 searchEnd, BinaryPredicate op);
        1）第一种形式返回第一个“既在区间[beg, end)中出现，也在区间[searchBeg, searchEnd)中出现”的元素位置
        2）第二种形式返回区间[beg, end)中的第一个这样的元素：他和区间[searchBeg, searchEnd)内的每一个元素进行op(elem,
        searchElem)结果都为ture
        3）如果没有找到匹配元素，两种形式都返回end
        4）注意op在函数调用过程中不应该改变自身状态
        5）op不应该改动传进来的参数
        6）你可以使用逆向迭代器来搜寻最后一个这样的元素
        7）时间复杂度：线性
        
        InputIterator adjacent_find (InputIterator beg, InputIterator end);
        InputIterator adjacent_find (InputIterator beg, InputIterator end, BinaryPredicate op);
        1）第一种形式返回区间[beg, end)中的第一对“连续两个相等元素”之中的第一个元素位置
        2）第二种形式返回区间[beg, end)中的第一对“连续两个元素均使op(elem, nextElem)结果为true“的其中第一个元素位置
        3）如果没有找到吻合元素，两种形式都返回end
        4）注意op在函数调用过程中不应该改变自身状态
        5）op不应该改动传进来的参数
        6）时间复杂度：线性
        
        bool equal (InputIterator1 beg, InputIterator1 end, InputIterator2 cmpBeg);
        bool equal (InputIterator1 beg, InputIterator1 end, InputIterator2 cmpBeg, BinaryPredicate op);
        1）第一种形式判断区间[beg, end)内的元素是否都和以cmpBeg开头的区间内的元素相等
        2）第二种形式判断区间[beg, end)内的元素和以cmpBeg开头的区间内的对应元素是否都能使op(elem, cmpElem)结果为true
        3）调用者必须保证以cmpBeg开头的区间具有足够的元素
        4）当序列不相等时，如果想要了解其间的不同，应使用mismatch()算法
        5）注意op在函数调用过程中不应该改变自身状态
        6）op不应该改动传进来的参数
        7）时间复杂度：线性
        
        pair<InputIterator1, InputIterator2> mismatch (InputIterator1 beg, InputIterator1 end, 
                                                                InputIterator2 cmpBeg);
        pair<InputIterator1, InputIterator2> mismatch (InputIterator1 beg, InputIterator1 end, 
                                                                InputIterator2 cmpBeg, BinaryPredicate op);
        1）第一种形式返回区间[beg, end)和以cmpBeg开头的区间之中的第一组两两相异的对应元素
        2）第二种形式返回区间[beg, end)和以cmpBeg开头的区间之中的第一组”使op(elem, cmpElem)结果为false“的对应元素
        3）如果没有找到相异点，就返回一个pair，以end和第二序列的对应元素组成。这并不意味着两个序列相等，因为第二序列
        有可能包含更多的元素
        4）调用者必须保证以cmpBeg开头的区间具有足够的元素
        5）如果想要了解两个序列是否相等，应使用equal()算法
        6）注意op在函数调用过程中不应该改变自身状态
        7）op不应该改动传进来的参数
        8）时间复杂度：线性
        
        bool lexicographical_compare (InputIterator1 beg1, InputIterator1 end1, 
                                                InputIterator2 beg2, InputIterator2 end2);
        bool lexicographical_compare (InputIterator1 beg1, InputIterator1 end1, 
                                                InputIterator2 beg2, InputIterator2 end2, CompFunc op);
        1）两种形式都用来判断区间[beg1, end1)的元素是否小于区间[beg2, end2)的元素。所谓”小于“是指本着”字典次序“的意义
        2）第一种形式使用operator<
        3）第二种形式使用op(elem1, elem2)来判断
        4）注意op在函数调用过程中不应该改变自身状态
        5）op不应该改动传进来的参数
        6）时间复杂度：线性
        
        8.复制元素算法
        OutputIterator copy (InputIterator sourceBeg, InputIterator sourceEnd,  OutputIterator destBeg);
        BidirectionalIterator1 copy_backward (BidirectionalIterator1 sourceBeg,  BidirectionalIterator1 sourceEnd,
                                                                                        BidirectionalIterator2 destEnd);
        1）这两个算法都将源区间[sourceBeg, sourceEnd)中的所有元素复制到以destBeg为起点或以destEnd为终点的目标区间里去
        2）返回目标区间内最后一个被复制的元素的下一个位置，也就是第一个未被覆盖的元素的位置
        3）destBeg或destEnd不可处于[sourceBeg, sourceEnd)区间内
        4）copy()正向遍历序列，copy_backward()逆向遍历序列
        5）STL没有所谓的copy_if()算法，所以如果要复制符合某特定准则的元素，请使用remove_copy_if()算法
        6）如果希望在复制过程中逆转元素次序，应该使用reverse_copy()
        7）调用者必须保证目标区间有足够的空间，否则就得使用insert迭代器
        8）如果想把容器内的所有元素赋值给另一容器，应当使用assignment操作符（当两个容器的型别相同时）或者使用容器的
        assign()成员函数（当两个容器的型别不同时）
        9）如果希望在复制过程中删除某元素，请使用remove_copy()和remove_copy_if()算法
        10）如果希望在复制过程中改变元素，请使用transform()或replace_copy()算法
        11）时间复杂度：线性
