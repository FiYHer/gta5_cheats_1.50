#include "util.h"

void error_handle(bool state, const char* str)
{
	if (state == false)
	{
		std::cout << "·¢Éú´íÎó : " << str << std::endl;
		system("pause");
		exit(-1);
	}
}

void cmd_color(bool state, const char* str)
{
	if (state)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		std::cout << str << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else std::cout << str << std::endl;
}

unsigned int string_to_hash(std::string input, std::string pre)
{
	unsigned int num1 = 0U;
	input = pre + input;
	for (char c : input)
	{
		unsigned int num2 = num1 + (unsigned int)tolower(c);
		unsigned int num3 = num2 + (num2 << 10);
		num1 = num3 ^ num3 >> 6;
	}
	unsigned int num4 = num1 + (num1 << 3);
	unsigned int num5 = num4 ^ num4 >> 11;
	return num5 + (num5 << 15);
}

unsigned int joaat(std::string input)
{
	unsigned int num1 = 0U;
	for (char c : input)
	{
		unsigned int num2 = num1 + (unsigned int)tolower(c);
		unsigned int num3 = num2 + (num2 << 10);
		num1 = num3 ^ num3 >> 6;
	}
	unsigned int num4 = num1 + (num1 << 3);
	unsigned int num5 = num4 ^ num4 >> 11;
	return num5 + (num5 << 15);
}

bool single_check(int key)
{
	bool state = GetAsyncKeyState(key) & 0x8000;
	if (state) Beep(500, 500);
	return state;
}

bool two_check(int _left, int _right)
{
	bool state = GetAsyncKeyState(_left) & 0x8000 && GetAsyncKeyState(_right) & 0x8000;
	if (state) Beep(500, 500);
	return state;
}