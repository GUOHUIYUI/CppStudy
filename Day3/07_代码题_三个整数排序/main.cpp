#include <iostream>

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}



void sortThree(int& a, int& b, int& c)
{
	if (a > b)
	{
		swap(a, b);
	}
	if (a > c)
	{
		swap(a, c);
	}
	if (b > c)
	{
		swap(b, c);
	}
	std::cout << "Sorted numbers: " << a << ", " << b << ", " << c << std::endl;
}




int main()
{
	int a{ 1 }, b{ 3 }, c{ 2 };
	sortThree(a, b, c);

	int d{ 3 }, e{ 2 }, f{ 1 };
	sortThree(d, e, f);

	int g{ 2 }, h{ 2 }, i{ 1 };
	sortThree(g, h, i);

	int j{ -1 }, k{ -5 }, l{ 3 };
	sortThree(j, k, l);

	int m{ 0 }, n{ 0 }, o{ 0 };
	sortThree(m, n, o);

	return 0;
}