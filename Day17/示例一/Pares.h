#pragma once
#include<string>

enum class ParesError {
	none,
	emptyInput,
	invalidNumber,
	outOfRange,
	unsupportedValue
};
struct ParesResult {
	ParesError error{ParesError::none};
	int value{};
	std::string mode;
	std::string field;
	std::string reason;

	bool succeeded() const {
		return error == ParesError::none;

	}
};
ParesResult paresRate(std::string_view text);
ParesResult paresMode(std::string_view text);

