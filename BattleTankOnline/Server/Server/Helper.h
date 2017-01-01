#define HELPER
#ifdef HELPER
#pragma once
#include "StringHelper.h"
#include <type_traits>
#include <list>
#include <map>

using namespace std;
typedef unsigned long ULONG;
class Helper
{
	static bool InitRandom;
public:
	static char* GetCharFromString(string string);
	static char* GetCharFromInt(int x);
	static int GetIntFromString(string x);
	static float GetFloatFromString(string x);
	static unsigned long GetDWORDFromString(string x);
	static int GetCharLength(char* string);
	static ULONG GetULONGFromInt(int x);
	static void Replace(string& source, string const& find, string const& replace);
	static bool Equals(string a, string b);
	static string GetString(vector<string> decode, int pos, string element = ":");
	static int GetInt(vector<string> decode, int pos, string element = ":");
	static unsigned long GetDWORD(vector<string> decode, int pos, string element = ":");
	static float GetFloat(vector<string> decode, int pos, string element = ":");
	static int Rand(int from, int to);

	static void OffServerGameLogic(int sid);
	static void PING_UpdateGameLogic(int sid, string command);

};


#endif // HELPER