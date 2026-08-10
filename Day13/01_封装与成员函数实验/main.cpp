#include <iostream>

class LimitedCounter
{
public:
	bool increment()
	{
		if (value_ < 10)
		{
			value_++;
			return true;
		}
		return false;
	}
	void reset()
	{
		value_ = 0;
	}
	int value() const {
		return value_;
	}


private:
	int value_{ 0 };
};

int main()
{
	class LimitedCounter limitedCounter;
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";
	std::cout << limitedCounter.increment() << limitedCounter.value() << "\n";


	return 0;
}
