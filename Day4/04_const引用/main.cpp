int main()
{


    int value{ 10 };
	int& ref{ value }; // ref是value的引用
	const int& const_ref{ value }; // const_ref是value的常量引用
	ref = 20;
	value = 30;
	//const_ref = 10; 无法通过const 引用修改引用对象的值 const引用提供了一种保护机制 但不影响对象本身

	const int limit{ 10 };
	const int& const_ref2{ limit }; // const_ref2是limit的常量引用
	//limit = 10;
	//const_ref2 = 10; 通过常量对象本身和const引用都无法修改对象的值
    return 0;
}