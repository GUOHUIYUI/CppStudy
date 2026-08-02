#include <iostream>
#include <string>


class Solution {
public:
	bool isValid(std::string s) {
		std::string text{};
		for (char current : s)
		{
			if (current == '(' || current == '{' || current == '[')
			{
				text.push_back(current);
				continue;
			}
			else if (current == ')' || current == '}' || current == ']')
			{
				if (text.empty())
				{
					return false;
				}
				else if (text.back() == '(' && current == ')')
				{
					text.pop_back();
				}
				else if (text.back() == '{' && current == '}')
				{
					text.pop_back();
				}
				else if (text.back() == '[' && current == ']')
				{
					text.pop_back();
				}
				else
				{
					return false;
				}
			}
		}
		if (text.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};


int main()
{
	return 0;
}