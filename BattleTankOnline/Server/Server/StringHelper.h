#define STRING_HELPER
#ifdef STRING_HELPER
#pragma once
#include <string>
#include <vector>

class StringHelper
{
public:
	StringHelper();
	~StringHelper();
	StringHelper(const StringHelper &copy) = delete;
	StringHelper operator=(const StringHelper &copy) = delete;

public:
	// return copy string. so, do not change member variable

	// if split "a,b,,d" by ",", result is "a", "b", "", "d".
	static std::vector<std::string> split(const std::string &strTarget, const std::string &strDelimiter);
	// if split "a,b,,d" by ",", result is "a"
	static std::string getBefore(const std::string &strTarget, const std::string &strKey);
	// if split "a,b,,d" by ",", result is "b,,d"
	static std::string getAfter(const std::string &strTarget, const std::string &strKey);
	
	static std::string trimWhiteSpace(const std::string &strTarget);
	static std::string getBetween(const std::string &strTarget, const std::string &strStartKey, const std::string &strEndKey);
	static std::string getUpperCase(const std::string &strTarget);
	static std::string getLowerCase(const std::string &strTarget);
	static std::vector<std::string::size_type> getIndexList(const std::string &strTarget, const std::string &strKey);
	// if iCount <= 0, return string is empty
	static std::string repeat(const std::string &strTarget, const int &iCount);
private:
	class impl;
	impl *pImpl;
};


#endif // STRING_HELPER