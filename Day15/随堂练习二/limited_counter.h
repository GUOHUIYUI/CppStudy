#ifndef LIMITED_COUNTER_H
#define	LIMITED_COUNTER_H

class LimitCounter {
public:
	bool increament();
	int value()const;
private:
	int value_;
};

#endif