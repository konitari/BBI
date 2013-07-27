#ifndef __PE_ENGINE_H__
#define __PE_ENGINE_H__

#include <new>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <tr1/unordered_map>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "pedata.h"
#include "ehm.h"

#define MAX_LINE_BUFFER 256
#define EARNINGS_FLUCTUATION_PERC 0.8
#define PRICES_FLUCTUATION_PERC 0.2

#define _countof(arr) (sizeof(arr)/sizeof(arr[0])

using namespace std;

namespace PeFlow {

	class PeEngine
	{

	public:
		
		void PrintDataToScreen();
		
		bool PublishRandomPrice();
		
		bool PublishRandomEarnings();
		
		static bool CreatePeEngine(string const &peDataFile, PeEngine** engine);
		
		virtual ~PeEngine(void);
		
	private:
		
		PeEngine(void);
		
		PeData* GetSecurityData(string const &security);

		bool PublishPrice(string const &security, double price);

		bool PublishEarnings(string const &security, double earnings);
		
		bool InitializeEngine(string const &peDataFile);
		
		PeData* GetRandomSecurity();

		std::tr1::unordered_map<string, PeData*> m_pPeMap;
		
	};

}

#endif
