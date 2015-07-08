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
        
        2.namespace std {
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
