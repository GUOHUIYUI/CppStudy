#include<iostream>


bool splitSeconds(int totalSeconds, int& hours, int& minutes, int& seconds)
{
    if (totalSeconds < 0)
    {
        return false;
    }
    else
    {
		hours = totalSeconds / 3600;
		minutes = (totalSeconds % 3600) / 60;
		seconds = totalSeconds % 60;
		return true;
    }

}

int main()
{
	int hours{};
	int minutes{};
	int seconds{};
	if (splitSeconds(3661, hours, minutes, seconds))
	{
		std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
	}
	if (splitSeconds(0, hours, minutes, seconds))
	{
		std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
	}
	if (splitSeconds(59, hours, minutes, seconds))
	{
		std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
	}
	if (splitSeconds(60, hours, minutes, seconds))
	{
		std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
	}
    return 0;
}