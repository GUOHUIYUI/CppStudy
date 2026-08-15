#include <string>


//两种方式实质是不同的，第一种直接使用构造成员，第二种先默认构造再赋值

class Label {
public:
	Label(std::string text)
		:text_{ text }
	{
	}
private:
	std::string text_;
};

class Label1 {
public:
	Label1(std::string text)

	{
		text_ = text;
	}
private:
	std::string text_;
};
//const成员因为创建后无法修改其值，因此只能在初始化列表中赋值

class Reading {
public:
	Reading(int id, int value)
		:id_{ id },
		value_{ value }
	{
	}
private:
	const int  id_;
	int value_;
};

//成员初始化顺序是和声明顺序有关，不和初始化列表顺序有关

//仍然是初始化id_再初始化value_
class Reading1 {
public:
    Reading1(int id, int value)
        :value_{ value },
        id_{ id }
    {
    }
private:
    const int  id_;
    int value_;
};