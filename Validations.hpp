#pragma once
#include <string>
#include <exception>
#include "Date.hpp"

class Validations
{
public:

	Validations() = delete;

	static void ValidateDateFormat(const std::string& dateStr);
	static void ValidateDate(const std::string& yearStr, const std::string& monthStr, const std::string& dayStr);
	static void ValidateFileName(std::string& fileName);
};

