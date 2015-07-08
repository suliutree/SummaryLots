##STL

####内存分区

        1.堆：由程序员手动分配和释放，完全不同于数据结构中的堆，分配方式类似链表。由malloc（C语言）或new（C++）来分配，free
        （C语言）和delete（C++）释放。若程序员不释放，程序结束时由系统释放。
        
        2.栈：由编译器自动分配和释放，存放函数的参数值、局部变量的值等。操作方式类似数据结构中的栈。
        
        3.全局（静态）存储区：存放全局变量和静态变量。包括DATA段（全局初始化区）与BSS段（全局未初始化区）。其中，初始化的全局
        变量和静态变量存放在DATA段，未初始化的全局变量和静态变量存放在BSS段。程序结束后有系统释放。
        其中BSS段的特点是：在程序执行之前BSS段会自动清0。所以，未初始化的全局变量和静态变量在程序执行之前就已经成0了。
        
        4.文字常量区：常量字符串就放在这里，程序结束后由系统释放。
        
        5.程序代码区：存放函数体的二进制代码。
        
        
####vector
        
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
                
                
####stack
        
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
        

####priority_queue

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
