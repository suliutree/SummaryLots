# SummaryLots
##设计模式
    
    设计模式（Design Pattern）是一套被反复使用、多数人知晓的、经过分类编目的、代码设计经验的总结。
    
    目的：使用设计模式是为了可重用代码、让代码更容易被他人理解、保证代码可靠性。
    
###单例模式
    
    有些对象我们只需要一个
    	比如：配置文件、工具类、线程池、缓存、日志对象等
    	
    如果创造出多个实例，就会导致许多问题
    	比如占用过多资源，不一致的结果等
    	
    单例模式保证整个应用中某个实例有且只有一个
    
    饿汉模式与懒汉模式的区别：
    饿汉模式：特点是加载类时比较慢，但运行时获取对象的速度比较快（因为在加载类时就已经创建了对象），线程安全的
	懒汉模式：特点是加载类时比较快，但运行时获取对象的速度比较慢（因为在加载类时并没有创建对象），线程不安全的
	
	
##操作系统

	进程与线程的区别
	
		1.进程是系统进行资源分配的基本单位，有独立的内存地址空间；线程是CPU调度的基本单位，没有单独的地址空间，
		有独立的栈，局部变量，寄存器，程序计数器等。
		
		2.创建进程开销大，包括创建虚拟地址空间等需要大量系统资源；创建线程开销小，基本上只有一个内核对象和一个
		堆栈。
		
		3.一个进程无法直接访问另一个进程的资源；同一个进程内的多个线程共享进程的资源。
		
		4.进程切换开销大（涉及当前执行进程CPU环境的保存以及新调度的进程CPU环境的设置），线程切换开销小（只需保
		存和设置少量寄存器的内容）；进程间通信开销大（需要借助操作系统），线程间通信开销小（可以直接读写进程数
		据段，如全局变量）。
		
		5.线程属于进程，不能独立执行。每个进程至少要有一个线程，成为主线程。
		
		
	进程通信的几种方式
	
		1.管道（Pipe）及有名管道（namedpipe）：管道可用于具有亲缘关系进程间的通信，有名管道克服了管道没有名字的
		限制，因此，除具有管道所具有的功能外，它还允许无亲缘关系进程间的通信；
		
		2.信号（Signal）：信号是比较复杂的通信方式，用于通知接受进程有某种事件发生，除了用于进程间通信外，进程
		还可以发送信号给进程本身；linux除了支持Unix早期信号语义函数sigal外，还支持语义符合Posix.1标准的信号函数
		sigaction（实际上，该函数是基于BSD的，BSD为了实现可靠信号机制，又能够统一对外接口，用sigaction函数重新
		实现了signal函数）；
		
		3.Message（消息队列）：消息队列是消息的链接表，包括Posix消息队列system V消息队列。有足够权限的进程可以
		向队列中添加消息，被赋予读权限的进程则可以读走队列中的消息。消息队列克服了信号承载信息量少，管道只能承
		载无格式字节流以及缓冲区大小受限等缺点。
		
		4.共享内存：使得多个进程可以访问同一块内存空间，是最快的可用IPC形式。是针对其他通信机制运行效率较低而设
		计的。往往与其它通信机制，如信号量结合使用，来达到进程间的同步及互斥。
		
		5.信号量（semaphore）：主要作为进程间以及同一进程不同线程之间的同步手段。
		
		6.套接口（Socket）：更为一般的进程间通信机制，可用于不同机器之间的进程间通信。起初是由Unix系统的BSD分支
		开发出来的，但现在一般可以移植到其它类Unix系统上：Linux和System V的变种都支持套接字。
		
	
	线程同步的几种方式
	
		线程同步的方式主要由4种：临界区（Critical Section）
					 互斥量（Mutex）
					 信号量（Semaphore）
					 事件（Event）
								 
		主要区别和特点如下：
		1.临界区：通过对多线程的串行化来访问公共资源或一段代码，速度快，适合控制数据访问。在任意时刻只允许一个线
		程对共享资源进行访问，如果有多个线程试图访问公共资源，那么在有一个线程进入后，其他试图访问公共资源的线程
		将被挂起，并一直等到进入临界区的线程离开，临界区在被释放后，其他线程才可以抢占。
		
		2.互斥量：采用互斥对象机制。只有拥有互斥对象的线程才有访问公共资源的权限，因为互斥对象只有一个，所以能保
		证公共资源不会同时被多个线程访问。互斥不仅能实现同一应用程序的公共资源安全共享，还能实现不同应用程序的公
		共资源安全共享。
		
		3.信号量：它允许多个线程在同一时刻访问同一资源，但是需要限制在同一时刻访问此资源的最大线程数目。
		
		4.事件：通过通知操作的方式来保持线程的同步，还可以方便实现对多个线程的优先级比较的操作。
		
		
	
