


int main()
{
	int first{ 10 };
	int second{ 20 };
	//根据const修饰的位置不同 const 修饰*ptr 所以*ptr不可以修改 ptr本身可以修改
	const int* ptr = &first; //指针指向的内容不能被修改 但是指针本身可以修改
	//*ptr = 100; 是错误的 因为const修饰了*ptr 所以*ptr不可以修改
	ptr = &second; //是正确的 因为ptr本身可以修改

	return 0;
}