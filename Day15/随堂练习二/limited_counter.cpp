#include"limited_counter.h"

bool LimitCounter:: increament()
{
	if (value_ >= 20)return false;
	value_++;
	return true;
}

int LimitCounter::value() const
{
    return value_;
}