#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>

//#include "concol.h"

//TODO MessageBox
#ifndef out
#define out std::cout
#endif

namespace RenderFish
{
	class Debug
	{
	public:
		//Debug();
		~Debug();

		static void init()
		{
			//HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
			hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(hstdout, &csbi);
		}

		static void LogError(std::string strInfo)
		{
			SetConsoleTextAttribute(hstdout, 0x0C);
			out << "[Error] " << strInfo << std::endl;
		}

		static void LogWarning(std::string strInfo)
		{
			SetConsoleTextAttribute(hstdout, 0x0E);
			out << "[Warning] " << strInfo << std::endl;
		}

		static void LogInfo(std::string strInfo)
		{
			SetConsoleTextAttribute(hstdout, 0x0F);
			out << "[Info] " << strInfo << std::endl;
		}

		static void LogInfo(int intValue)
		{
			SetConsoleTextAttribute(hstdout, 0x0F);
			out << "[Info] " << intValue << std::endl;
		}

	private:
		Debug() {}
		static HANDLE hstdout;
	};

}

#undef out


#endif // !DEBUG_H