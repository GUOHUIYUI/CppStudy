#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>

//原生数组：原生数组在声明时必须给定长度，operator[]在访问时不会自动判断下标，数组越界访问属于未定义行为
//std::size(arr)在数组声明所在的作用域使用，获取数组长度
//原生数组作为参数传递时会退化为指针，所以传递时需要额外传递数组长度

//原生数组的尺寸与遍历
void example1();
void test1();


//使用std::array保存固定数量数据  std::array在array头文件中
/*
	std::array<int ,5 > values{1,2,3,4,5};
	int 为数据类型
	5 为数组长度
	与原生数组相同，std::array也是保存固定长度的连续数据，但是提供了一些常见容器接口
	values.size(),values.front(),values.back(),values.at(2)
	它也支持普通数组的访问方式 values[2];

	operator[]和at()的区别
	operator[]不会进行越界检查，at()会进行越界检查，如果越界会抛出异常

*/

void example2();

//std::array是一个对象，可以把尺寸一起带入函数类型
//void printSamples(const std::array<int, 5>& samples); const表示只读取这个数组，引用可以避免复制数组的副本


//三、范围for中的值与引用
void example3()
{
	std::array<int, 4> arrays{ 1,2,3,4 };
	for (int value : arrays)
	{
		value = 0; //这操作不会修改arrays中的元素，value为数组中元素的副本
	}
	for (int &value : arrays)
	{
		value = 0;//这操作会修改arrays中的元素，value为数组中元素的引用
	}
}

//原地修改负数
void example4()
{
	std::array<int, 6>values{ 4, -2, 7, -1, 0, 5 };
	int replace{};
	for (int &value : values)
	{
		if (value < 0)
		{
			value = 0;
			replace++;
		}
	}
	std::cout << "replace   " << replace << std::endl;
	for (int value : values)
	{
		std::cout << value << "  " << std::endl;
	}
}

/*
	* 解释为什么没有修改原数组；
		因为修改的value只是数组元素的副本
	* 做最小修改使程序正确；
	* 再增加一个只读循环，输出修改后的全部元素。
*/
void test2()
{
	std::array<int, 6>values{ 4, -2, 7, -1, 0, 5 };

	/*
		for (int value : values) {
			if (value % 2 != 0) {
			++value;
			}
		}
	*/
	for (int &value : values) {
		if (value % 2 != 0) {
			++value;
		}
	}
	for (int value : values) {
		std::cout << "value:  " << value << std::endl;
	}

}
/*
1. 把元素数量当成最后一个下标
2. 循环条件写成<= size()
3. 范围for按值遍历却期待修改原元素
4. 认为原生数组参数仍知道元素数量：原生数组传递时会退化为指针
*/


int main()
{
	test2();
	return 0;
}

void test1()
{
	int values[6]{ 2, 4, 6, 8, 10, 12 };
	int sum{}, even{}, max{ values[0] };
	for (std::size_t index{};index < std::size(values);index++)
	{
		if (max < values[index])
		{
			max = values[index];
		}
		if (values[index] % 2 == 0)
		{
			even++;
		}
		sum += values[index];
	}
	std::cout << "max  " << max << std::endl;//12
	std::cout << "even  " << even << std::endl;//6
	std::cout << "sum  " << sum << std::endl;//42

}

void example1()
{
	int arr[4] = { 1,2,3,4 };//下标从0开始，所以范围为0-3
	int sum{};

	// std::cout << arr[4] << std::endl;//未定义行为，访问越界
	for (std::size_t i = 0;i < std::size(arr);i++)
	{
		sum += arr[i];
	}
	std::cout << "count  " << std::size(arr) << std::endl;
	std::cout << "sum:  " << sum << std::endl;
}


void example2()
{
	std::array<int, 6> arrays{ 1200,1231,2344,231,3123,321 };
	int maximum{ arrays[0] };
	int minimum{ arrays[0] };
	int sum{ 0 };
	//增强for   value为arrays中元素的副本，修改value不能修改arrays，要修改arrays要使用引用
	//这里的范围for会依次把每个元素的值复制到局部变量`sample`。对于`int`这样的小型类型，按值读取清楚且足够。
	for (int value : arrays)
	{
		if (maximum < value)
		{
			maximum = value;
		}
		if (minimum > value)
		{
			minimum = value;
		}
		sum += value;
	}
	double vaerage = static_cast<double>(sum) / static_cast<double>(arrays.size());
	std::cout << "maximum:  " << maximum << std::endl;
	std::cout << "minimum:  " << minimum << std::endl;
	std::cout << "average:  " << vaerage << std::endl;
}
