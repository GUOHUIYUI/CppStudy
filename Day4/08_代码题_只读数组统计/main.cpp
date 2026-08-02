#include <iostream>

bool calculateStatistics(const int* values, int& maximum, int& minimum, double& average, int count)
{
	if (values == nullptr || count <= 0)
	{
		return false;
	}
	minimum = values[0];
	maximum = values[0];
	for (int i = 0;i < count;i++)
	{
		if (values[i] < minimum)
		{
			minimum = values[i];
		}
		if (values[i] > maximum)
		{
			maximum = values[i];
		}
		average += values[i];
	}

	average /= count;
	return true;

}



int main()
{
	int arr[5]{ 1,2,3,4,5 };
	int max{}, min{};
	double avg{};
	calculateStatistics(arr, max, min, avg, 5);
	std::cout << max <<std::endl;
	std::cout << min << std::endl;

	std::cout << avg << std::endl;

	return 0;
}