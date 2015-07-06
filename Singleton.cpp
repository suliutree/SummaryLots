#include <iostream>

using namespace std;

class MySingleton
{
private:
	// 1.将构造方法私有化，不允许外部直接创建对象
	MySingleton(){}
	MySingleton(const MySingleton &copy);// 不允许拷贝（不实现）
	MySingleton &operator=(const MySingleton &copy);// 不允许赋值（不实现）
	// 2.声明类的唯一实例，使用private static修饰
	static MySingleton* m_pInstance;

public:
	// 3.提供一个用于获取实例的方法，使用public static修饰
	static MySingleton* getInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new MySingleton();

		return m_pInstance;
	}
};

// 必须对类中的静态变量 m_pInstance进行初始化，否则编译错误
MySingleton* MySingleton::m_pInstance = NULL;

int main()
{
	MySingleton* ms1 = MySingleton::getInstance();
	MySingleton* ms2 = MySingleton::getInstance();
	if (ms1 == ms2)
		cout << "ms1与ms2是同一个实例" << endl;
	else
		cout << "ms1与ms2不是同一个实例" << endl;

	system("pause");
	return 0;
}

/*
本例中的实现方式针对非多线程的情况。如果有多个线程想要同时调用getInstance函数，则需要mutex保护下列代码:

pthread_mutex_lock(&mutex);
if (m_pInstance == NULL)
	m_pInstance = new MySingleton;
pthread_mutex_unlock(&mutex);
*/
