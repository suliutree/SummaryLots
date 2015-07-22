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
        
        
