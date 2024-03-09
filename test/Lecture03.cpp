#include<iostream>


void pp(int &a)
{
	std::cout << &a << "	" << a << std::endl;
}


//custom array uing RAII
class IntArray
{
	size_t m_size;
	int* m_arr;
public:
	IntArray(size_t size)
		: m_size(size)
		, m_arr(new int[size])
	{
	}
	~IntArray()
	{
		delete m_arr;
	}

	int get(size_t index) const
	{
		return m_arr[index];
	}

	void set(size_t index, int value)
	{
		m_arr[index] = value;
	}

	void print()const
	{
		for (int i = 0; i < m_size; i++)
		{
			std::cout << m_arr[i] << std::endl;
		}
	}
};

//custom array using templates,overloading and RAII
template <typename T>
class DynamicArray
{
	size_t m_size;
	T* m_arr;
public:
	DynamicArray(size_t size)
		: m_size(size)
		, m_arr(new T[size])
	{
	}
	~DynamicArray()
	{
		delete[] m_arr;
	}

	T get(size_t index) const
	{
		return m_arr[index];
	}

	T &operator[](size_t index) 
	{
		return m_arr[index];
	}

	void set(size_t index, T value)
	{
		m_arr[index] = value;
	}

	const T& operator[](size_t index) const
	{
		return m_arr[index];
	}

	void print()const
	{
		for (int i = 0; i < m_size; i++)
		{
			std::cout << m_arr[i] << std::endl;
		}
	}
};
int A3main()
{

	//array defined on heap and stack
	/*int arr[10];
	int * harr = new int[10];

	for (size_t i = 0; i < 10; i++)
	{
		pp(arr[i]);
	}
	std::cout <<"===================================================="<<std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		pp(harr[i]);
	}*/

	//pointers
	/*int a = 10;
	int* pa = &a;
	int b = 25;
	int* pb = &b;
	*pa = 17;
	pp(a);
	pp(b);
	*/


	//RAII intialize and methods
	/*IntArray myarr(10);
	myarr.set(0, 1);
	myarr.set(1, 2);
	myarr.set(2, 3);
	myarr.set(3, 4);
	myarr.print();*/


	//Dynamic array using Templates
	DynamicArray<float> d(10);
	d.set(0, 1.23f);
	d.set(1, 2.23f);
	d.set(3, 3.313f);
	d[4] = 4.5345;
	d.print();
	
	std::cout << d[1];
	return 0;
}