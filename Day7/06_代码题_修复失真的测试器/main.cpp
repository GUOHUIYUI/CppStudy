#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


/*
    下面的测试器不能正确表示预期非法用例：
    void check(bool actual)
{
    std::cout << (actual ? "PASS" : "FAIL") << '\n';
}
*/

constexpr bool isCalibrationValid(double rawValue, double scale, double offset);
constexpr double applyCalibration(double rawValue, double scale, double offset);
bool calibrate(double rawValue, double scale, double offset, double& result);
bool calibrate(int rawValue, double scale, double offset, double& result);
void check(const std::string& name, bool actual, bool expect);
void check(const std::string& name, double actual, double expect);



int main()
{
	double expect{};
	// 1-4：正常用例（PASS 预期）
	check("valid calibration (bool)", calibrate(0, 1, 0, expect), true);
	check("applyCalibration (double)", applyCalibration(1, 1, 0), 1.0);
	check("calibrate with offset (bool)", calibrate(0, 1, 1, expect), true);
	check("expected result (double)", expect, 1.0);

	// 5-8：非法参数用例（预期 calibrate 返回 false，但仍应 PASS 测试）
	check("scale=0 invalid", calibrate(0, 0, 0, expect), false);
	check("scale>1000 invalid", calibrate(0, 1001, 0, expect), false);
	check("offset too small", calibrate(0, 1, -100001, expect), false);
	check("offset too large", calibrate(0, 1, 100001, expect), false);

	// 9：单独验证失败时输出参数保持调用前的值
	expect = 12345.0;
	calibrate(0, 0, 0, expect);   // 必定失败，不应修改 expect
	check("result preserved on fail", expect, 12345.0);
    return 0;
}

constexpr bool isCalibrationValid(double rawValue, double scale, double offset)
{
	if (rawValue < -100000 || rawValue>100000)
	{
		return false;
	}
	if (scale <= 0 || scale > 1000)
	{
		return false;
	}
	if (offset < -100000 || offset>100000)
	{
		return false;
	}
	return true;

}

constexpr double applyCalibration(double rawValue, double scale, double offset)
{
	return rawValue * scale + offset;
}

bool calibrate(double rawValue, double scale, double offset, double& result)
{
	if (!isCalibrationValid(rawValue, scale, offset))
	{
		std::cout << "parameter ERROR" << std::endl;
		return false;
	}
	result = applyCalibration(rawValue, scale, offset);
	return true;
}

bool calibrate(int rawValue, double scale, double offset, double& result)
{
	return calibrate(static_cast<double>(rawValue), scale, offset, result);
}

void check(const std::string& name, bool actual, bool expect)
{
	std::cout << name
		<< ":" << "actual:  " << actual
		<< "," << "expect:  " << expect
		<< (actual == expect ? "   PASS  " : "  FAIL  ") << std::endl;

}
void check(const std::string& name, double actual, double expect)
{
	std::cout << name
		<< ":" << "actual:  " << actual
		<< "," << "expect:  " << expect
		<< (actual == expect ? "  PASS  " : "  FAIL  ") << std::endl;

}

