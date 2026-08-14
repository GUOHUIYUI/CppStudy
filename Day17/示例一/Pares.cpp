#include"Pares.h"
#include<charconv>
#include<string_view>

ParesResult paresRate(std::string_view text)
{
	if (text.empty())
	{
		return { ParesError::emptyInput,0,"Rate","value is empty" };
	}
	int value{};
	const char *first = text.data();
	const char *last = text.data() + text.size();
	const auto result = std::from_chars(first, last, value);
	if (result.ec != std::errc{} || result.ptr  != last)
	{
		return { ParesError::invalidNumber,0,"","rate","use devimal digits only" };
	}
	if (value < 1 || value > 1000)
	{
		return { ParesError::outOfRange,0,"","rate","value out	Of Range"};
	}
	return { ParesError::none,value,"","",""};
}

ParesResult paresMode(std::string_view text)
{
	if (text.empty())
	{
		return { ParesError::emptyInput,0,"","Mode","mode is empty"};
	}
	if (text == "AUTO" || text == "MANUAL" || text == "SAFE") {
		return { ParesError::none,0,static_cast<std::string>(text),"",""};
	}
	else {
		return { ParesError::unsupportedValue,0,"","Mode","Mode unSupported"};
	}
}
