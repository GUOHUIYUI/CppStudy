#include <iostream>
#include <string>
#include <string_view>


bool parseCommand(std::string_view line, std::string& name, std::string& argument);

int main()
{
	std::string name{}, argument{};
	
    std::cout << ((parseCommand("",name, argument) == false) ? "TRUE" : "FALSE") << "name: " << name << " argument: " << argument << std::endl;
	name.clear();
	argument.clear();
	std::cout << ((parseCommand("START", name, argument) == true) ? "TRUE" : "FALSE") << "name: " << name << " argument: " << argument << std::endl;
	name.clear();
	argument.clear();
	std::cout << ((parseCommand("SET RATE 100", name, argument) == true) ? "TRUE" : "FALSE") << "name: " << name << " argument: " << argument << std::endl;
	name.clear();
	argument.clear();
	std::cout << ((parseCommand("STOP", name, argument) == false) ? "TRUE" : "FALSE") << "name: " << name << " argument: " << argument << std::endl;
	name.clear();
	argument.clear();
	std::cout << ((parseCommand("dasguidghqiu wghdiugsaidugiauqwtdgiuag diuabiwghfdiuawyteiaugdiastgdgfuawigeiudaydghiauw", name, argument) == false) ? "TRUE" : "FALSE") << "name: " << name << " argument: " << argument << std::endl;



	return 0;
}

bool parseCommand(std::string_view line, std::string& name, std::string& argument)
{
	if (line.size() == 0 || line.size() > 64)
		return false;
	const std::size_t separator{ line.find(' ') };
	if (separator == std::string::npos)
	{
		if (line == "START" || line == "RUN" || line == "SET")
		{
			name = line;
			argument = "";
			return true;
		}
		else {
			return false;
		}
	}
	else {
		std::string tmp{ line.substr(0, separator) };
		if (tmp == "START" || tmp == "RUN" || tmp == "SET")
		{
			name = tmp;
			argument = line.substr(separator + 1);
			return true;
		}
		else {
			return false;
		}
	}


}
