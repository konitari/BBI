#include "commandlineparser.h"

namespace PeFlow {

	CommandLineParser::CommandLineParser(void)
	{}

	CommandLineParser::~CommandLineParser(void)
	{}

	/**
     * Creates a parser for the caller.
	 * the initial data is provided.
	 *     
     * @note Caller is responsible to call delete on the returned parser.
	 *
     * @param argc command line arg count
	 * @param argv command line args
	 * @param parser the created parser.
	 *
	 * @return non-NULL parser on success, failure otherwise
     */
	bool CommandLineParser::CreateParser(int argc, char** argv, CommandLineParser** parser)
	{
		bool retVal = false;
		
		CommandLineParser* p = new (std::nothrow) CommandLineParser();
		CHECK_NULL(p);
				
		retVal = p->ParseData(argc, argv);
		CHECK_BOOL(retVal);
					
		// hand-off
		*parser = p;
		p = NULL;
		
		retVal = true;
		
	Error:
	
		delete p;
		return retVal;		
	}

	/**
     * Prints usage instructions     
     */
	void CommandLineParser::PrintUsage() 
	{
		std::cout << endl << "PeFlow.exe -initpefile <Path to initial PE data-file>" << endl << endl;
	}
	
	/**
     * Parses the given command line args, and ensures that the file with
	 * the initial data is provided.
	 *     
     * @param argc number of arguments
     * @param argv the actual arguments
     */
	bool CommandLineParser::ParseData(int argc, char** argv)
	{
		bool retVal = false;
		
		// ensure 3 args given
		if (argc != 3) 
		{
			std::cerr << "Invalid number of arguments provided.";
			PrintUsage();
		}
		else
		{						
			// only arg allowes is the initial PE file
			if (strcmp(argv[1], "-initpefile") == 0 || strcmp(argv[1], "/initpefile") == 0) 
			{
				m_PeDataFile = argv[2];
				retVal = true;
			}				
			else
			{			
				std::cerr << "Incomplete data provided on the command line";
				PrintUsage();
			}			
		}

		return retVal;
	}

	string CommandLineParser::GetPeDataFile()
	{
		return m_PeDataFile;
	}
	
}


