int main()
{


	int first{ 10 };
	int second{ 20 };
	//根据const修饰的位置不同 const 修饰ptr 所以ptr不可以修改 *ptr本身可以修改
	int* const ptr = &first; //ptr本身不能修改 但是*ptr可以修改
	//ptr = &second; //是错误的 因为ptr本身不能修改
	*ptr = 100; //是正确的 因为*ptr可以修改

	//两者都不可修改 const int* const ptr=&first
	return 0;
}