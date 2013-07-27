#ifndef __COMMAND_LINE_PARSER__
#define __COMMAND_LINE_PARSER__

#include <iostream>
#include <stddef.h>
#include <new>
#include <string.h>
#include "ehm.h"

using namespace std;

namespace PeFlow {

	class CommandLineParser
	{

	public:	
		
		static bool CreateParser(int argc, char** argv, CommandLineParser** parser);

		string GetPeDataFile();
		
		virtual ~CommandLineParser();

	private:

		void PrintUsage();

		CommandLineParser(void);

		bool ParseData(int argc, char** argv);

		string m_PeDataFile;
		
	};

}

#endif

