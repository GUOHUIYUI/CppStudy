#include <charconv>
#include <iostream>
#include <string>
#include <string_view>
enum class ParesError {
	none,
	emptyInput,
	invalidNumber,
	outOfRange,
	unsupportedValue
};
struct ParesResult {
	ParesError error{ ParesError::none };
	int value{};
	std::string field;
	std::string reason;

	bool succeeded() const {
		return error == ParesError::none;

	}
};


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
	if (result.ec != std::errc{} || result.ptr != last)
	{
		return { ParesError::invalidNumber,0,"rate","use devimal digits only" };
	}
	if (value < 1 || value > 1000)
	{
		return { ParesError::outOfRange,0,"rate","value out	Of Range" };
	}
	return { ParesError::none,value,"","" };
}

void check(std::string_view test)
{
	const ParesResult result = paresRate(test);

	if (!result.succeeded()) {
		std::cout << result.field << ": " << result.reason << '\n';
	}
	else {
		std::cout << "value: " << result.value << '\n';
	}
}

int main()
{
	check("1001");
	check("0");
	check("100");
	check("");

    return 0;
}
