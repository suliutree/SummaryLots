## 设计模式
    
    设计模式（Design Pattern）是一套被反复使用、多数人知晓的、经过分类编目的、代码设计经验的总结。
    
    目的：使用设计模式是为了可重用代码、让代码更容易被他人理解、保证代码可靠性。
    
### 单例模式
    
    有些对象我们只需要一个
    	比如：配置文件、工具类、线程池、缓存、日志对象等
    
    1）如果不想让客户创建新的实例，可以声明私有构造函数，从而阻止编译器将其自动声明为公有。
    2）如果想让单例不可复制，以确保不能创建第二个实例，也可以声明私有复制构造函数和私有赋值操作符。
    3）如果要禁止客户删除单例实例，可以声明私有构造函数。
    4）GetInstance() 方法即可以返回单例类的指针，也可以返回引用。当返回指针时，客户可以删除该对象。因此最好返回引用。

    优点：
    1）确保一个类只创建一个实例；
    2）为对象分配和销毁提供控制；
    3）支持线程安全地访问对象的全局状态；
    4）避免污染全局命名空间。

    单例设计模式可用于对固定的唯一对象进行建模。例如，访问系统时钟、全局剪贴板或键盘的类。也可以用于创建管理器类，提供
    对多种资源的唯一访问点，诸如线程管理器或事件管理器。

    class Singleton
    {
    public:
        static Singleton &GetInstance();
        
        /// Return some class-specific single-instance state
        int GetState();

    private:
        Singleton();
        ~Singleton();
        Singleton(const Singleton&);
        const Singleton& operator = (const Singleton&);
    }

    static Mutex mutex;
    Singleton &Singleton::GetInstance()
    {
        ScopedLock lock(&mutex); // 函数退出时释放互斥锁
        static Singleton instance;
        return instance;
    }

    Singleton::Singleton()
    {
        cout << "Singleton created" << endl;
    }

    Singleton::~Singleton()
    {
        cout << "Singleton destroyed" << endl;
    }

    int Singleton::GetState()
    {
        // this is where you could return the singleton's state.
        // I'm keeping it simple for this example though
        return 42;
    }

    int main(int, char**)
    {
        Singleton &foo = Singleton::GetInstance();
        foo.GetState();

        Singleton &foo2 = Singleton::GetInstance();
        foo2.GetState();
    }


<br>

#### 工厂模式

    工厂模式是一个创建型的设计模式，它允许创建对象时不指定要创建的对象的具体类型。
    从基本层面来看，工厂方法仅是一个普通方法的调用，该调用返回类的实例。但是，它们经常和继承一起使用，即派生类能够重写工厂
    方法并返回派生类的实例。常见的做法是使用抽象基类实现工厂模式。

    renderfactory.h

    class RendererFactory
    {
    public:
        typedef IRenderer *(*CreateCallback)();
        
        static void RegisterRenderer(const std::string &type, CreateCallback cb);

        static void UnregisterRenderer(const std::string &type);

        static IRenderer *CreateRenderer(const std::string &type);

    private:
        typedef std::map<std::string, CreateCallback> CallbackMap;
        static CallbackMap mRenderers;
    };

    renderfactory.cpp

    RenderFactory::CallbackMap RendererFactory::mRenderers;

    void RendererFactory::RegisterRenderer(const std::string &type, CreateCallback cb)
    {
        mRenderers[type] = cb;
    }

    void UnregisterFactory::UnregisterRenderer(const std::string type)
    {
        mRenderers.erase(type);
    }

    IRender *RendererFactory::CreateRenderer(const std::string &type)
    {
        CallbackMap::iterator it = mRenderers.find(type);
        if (it != mRenderers.end())
        {
            return (it->second)();
        }

        return NULL;
    }

    renderer.h

    class IRenderer
    {
    public:
        virtual ~IRenderer() {}
        virtual bool LoadScene(const std::string &filename) = 0;
        virtual void SetViewportSize(int w, int h) = 0;
        virtual void SetCameraPos(double x, double y, double z) = 0;
        virtual void SetLookAt(double x, double y, double z) = 0;
        virtual void Render() = 0;
    };

    main.cpp

    /// An OpenGL-based 3D renderer
    class OpenGLRenderer : public IRenderer
    {
    public:
        ~OpenGLRenderer() {}
        bool LoadScene(const std::string &filename) { return true; }
        void SetViewportSize(int w, int h) {}
        void SetCameraPos(double x, double y, double z) {}
        void SetLookAt(double x, double y, double z) {}
        void Render() { cout << "OpenGL Render" << endl; }
        static IRenderer *Create() { return new OpenGLRenderer; }
    };

    /// A DirectX-based 3D renderer
    class DirectXRenderer : public IRenderer
    {
    public:
        bool LoadScene(const std::string &filename) { return true; }
        void SetViewportSize(int w, int h) {}
        void SetCameraPos(double x, double y, double z) {}
        void SetLookAt(double x, double y, double z) {}
        void Render() { cout << "DirectX Render" << endl; }
        static IRenderer *Create() { return new DirectXRenderer; }
    };

    /// A Mesa-based software 3D renderer
    class MesaRenderer : public IRenderer
    {
    public:
        bool LoadScene(const std::string &filename) { return true; }
        void SetViewportSize(int w, int h) {}
        void SetCameraPos(double x, double y, double z) {}
        void SetLookAt(double x, double y, double z) {}
        void Render() { cout << "Mesa Render" << endl; }
        static IRenderer *Create() { return new MesaRenderer; }
    };

    int main(int, char **)
    {
        RendererFactory::RegisterRenderer("opengl", OpenGLRenderer::Create);
        RendererFactory::RegisterRenderer("directX", DirectXRenderer::Create);
        RendererFactory::RegisterRenderer("mesa", MesaRenderer::Create);

        IRenderer *ogl = RendererFactory::CreateRenderer("opengl");
        ogl->Render();
        delete ogl;

        // create a Mesa software renderer
        IRenderer *mesa = RendererFactory::CreateRenderer("mesa");
        mesa->Render();
        delete mesa;

        // unregister the Mesa renderer
        RendererFactory::UnregisterRenderer("mesa");
        mesa = RendererFactory::CreateRenderer("mesa");
        if (! mesa)
        {
            cout << "Mesa renderer unregistered" << endl;
        }

        return 0; 
    }


<br>

#### 观察者模式

     实现观察者模式的典型做法是引入两个概念：主题（Subject）和观察者（Observer），也称作发布者和订阅者。一个或多个
     观察者注册主题中感兴趣的事件，之后主题会在自身状态发生变化时通知所有注册的观察者。

     observer.h

    class IObserver
    {
    public:
        virtual ~IObserver() {}
        virtual void Update(int message) = 0;
    };

    class ISubject
    {
    public:
        ISubject();
        virtual ~ISubject();

        virtual void Subscribe(int message, IObserver *observer);
        virtual void Unsubscribe(int message, IObserver *observer);
        virtual void Notify(int message);

    private:
        typedef std::vector<IObserver *> ObserverList;
        typedef std::map<int, ObserverList> ObserverMap;
        ObserverMap mObservers;
    };

    observer.cpp

    ISubject::ISubject() {}
    ISubject::~ISubject() {}

    void ISubject::Subscribe(int message, IObserver *observer)
    {
        if (observer)
        {
            ObserverMap::iterator it = mObservers.find(message);
            if (it == mObservers.end())
            {
                mObservers[message] = ObserverList();
            }
            mObservers[message].push_back(observer);
        }
    }

    void ISubject::Unsubscribe(int message, IObserver *observer)
    {
        ObserverMap::iterator it = mObservers.find(message);
        if (it != mObservers.end())
        {
            ObserverList &list = mObservers[message];
            ObserverList::iterator li;
            for (li = list.begin(); li != list.end();)
            {
                if ((*li) == observer)
                {
                        list.erase(li);
                }
                else
                {
                        ++li;
                }
            }
        }
    }

    void ISubject::Notify(int message)
    {
        ObserverMap::iterator it = mObserver.find(message);
        if (it != mObservers.end())
        {
            ObserverList &list = mObservers[message];
            ObserverList::iterator li;
            for (li = list.begin(); li != list.end(); ++li)
            {
                (*li)->Update(message);
            }
        }
    }

    subject.h

    class MySubject : public ISubject
    {
    public:
        enum Messages { ADD, REMOVE, UPDATE };
    };

    main.cpp

    class MyObserver : public IObserver
    {
    public:
        MyObserver(const std::string &str) : mName(str) {}

        void Update(int message)
        {
            cout << mName << " Received message " << message << endl;
        }

    private:
        std::string mName;
    };

    int main()
    {
        MyObserver observer1("observer1");
        MyObserver observer2("observer2");
        MyObserver observer3("observer3");

        MySubject subject;

        subject.Subscribe(MySubject::ADD, &observer1);
        subject.Subscribe(MySubject::ADD, &observer2);
        subject.Subscribe(MySubject::REMOVE, &observer2);
        subject.Subscribe(MySubject::UPDATE, &observer1);
        subject.Subscribe(MySubject::UPDATE, &observer3);

        subject.Notify(MySubject::ADD);
        subject.Notify(MySubject::UPDATE);
    }
