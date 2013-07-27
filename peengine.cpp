#include "peengine.h"

using namespace PeFlow;

PeEngine::PeEngine(void)
{}


PeEngine::~PeEngine(void)
{}

/**
 * Initializes the P/E engine and reads the data from the initial
 * P/E file into a hashmap in memory.
 *     
 * @param peDataFile full path to the P/E file
 *
 * @return true on success, false otherwise
 */	
bool PeEngine::InitializeEngine(string const &peDataFile)
{					
	bool retVal = false;
	char lineBuffer[MAX_LINE_BUFFER] = {'\0'};
	FILE *pPeDataFile = NULL;
	PeData *data = NULL;
	char security[4] = {'\0'};		
	double price = 0;
	double earnings = 0;
	
	// seed random number generator
	srand (time(NULL));
	
	// open the initial file			
	pPeDataFile = fopen(peDataFile.c_str(), "r");
	CHECK_NULL_EX(pPeDataFile, "Failed to open intial data file");
		
	// read in the initial data into an unordered map	
	while (fgets(lineBuffer, sizeof(lineBuffer), pPeDataFile) != NULL)
	{	
		// check if any "blank" line encountered--if so skip it
		// blank like will typically have "\r\n", so 2.
		if (strlen(lineBuffer) <= 2)
		{
			continue;
		}
		
		// attempt to parse line
		retVal = (5 == sscanf(lineBuffer, "%c%c%c,%lf,%lf", &security[0], &security[1], &security[2], &price, &earnings));
		CHECK_BOOL_EX(retVal, "Failed to parse intial data file");
		
		// create piece of data corresponding to the file		
		retVal= PeData::CreatePeData(price, earnings, &data);
		CHECK_BOOL_EX(retVal, "Failed to create PeData object");
		
		// hand-off
		m_pPeMap[security] = data;
		data = NULL;
		
		// announce as we parse
		cout << fixed << setprecision(2);
		cout << "Inserting: " << security;
		cout << "\tPrice: " << price;
		cout << "\tPrice: " << earnings;
		cout << endl;									
	}
	
	if (m_pPeMap.size() == 0)
	{
		cerr << "Could not load any initial data." << endl;
	}
						
Error:
	
	delete data;
	
	if (!retVal) 
	{
		m_pPeMap.clear();	
	}

	if (pPeDataFile != NULL)
	{
		fclose(pPeDataFile);
		pPeDataFile = NULL;
	}

	return retVal;
}

/**
 * This function creates a P/E engine.
 *     
 * @param peDataFile full path to the P/E file
 * @param engine The create P/E Engine
 * @return true on success, false otherwise
 */		
bool PeEngine::CreatePeEngine(string const &peDataFile, PeEngine** engine)
{		
	bool retVal = false;
	PeEngine* eng = NULL;

	eng = new (std::nothrow) PeEngine();
	CHECK_NULL(eng);
		
	retVal = eng->InitializeEngine(peDataFile);
	CHECK_BOOL(retVal);
	
	// hand-off	
	*engine = eng;
	eng = NULL;
	
	retVal = true;
	
Error:		

	delete eng;
	return retVal;
}

/**
 * This is a utility function that helps get the data corresponding
 * to a security from the map.
 *     
 * @param security The name of the security
 
 * @return PeData on success, NULL otherwise
 */		
PeData* PeEngine::GetSecurityData(string const &security)
{
	PeData* data = NULL;
	std::tr1::unordered_map<string, PeData*>::const_iterator findResult;
	
	findResult = m_pPeMap.find(security);
	if (findResult == m_pPeMap.end())
	{
		cerr << "Failed to find given security in database" << endl;
	}
	else
	{
		data = static_cast<PeData*>(findResult->second);
	}
	
	return data;
}

/**
 * This is a utility function helps set the price of a given security.
 *     
 * @param security The name of the security
 * @param price The price of the security
 
 * @return true on success, false otherwise
 */	
bool PeEngine::PublishPrice(string const &security, double price)
{
	bool retVal = false;
	PeData* data = NULL;
					
	data = GetSecurityData(security);			
	CHECK_NULL_EX(data, "Failed to find security in database");
				
	data->SetPrice(price);
	retVal = true;
					
Error:

	return retVal;
}

/**
 * This is a utility function helps set the earnings of a given security.
 *     
 * @param security The name of the security
 * @param earnings The earnings of the security
 
 * @return true on success, false otherwise
 */	
bool PeEngine::PublishEarnings(string const &security, double earnings)
{
	bool retVal = false;
	PeData* data = NULL;
	
	data = GetSecurityData(security);			
	CHECK_NULL_EX(data, "Failed to find security in database");
		
	data->SetEarnings(earnings);
	retVal = true;
				
Error:

	return retVal;
}

/**
 * This is a utility function helps get a random security
 * from the db-map.
 *
 * @return Randomly chosen PeData from the map.
 */	
PeData* PeEngine::GetRandomSecurity()
{
	int size = 0;
	int randIndex = 0;
	std::tr1::unordered_map<string, PeData*>::iterator iter;
	PeData *data = NULL;
	
	// ensure the DB has a non-zero size, otherwise there's no point
	// in publishing a random security
	size = m_pPeMap.size();	
	if (size > 0)
	{
		// point to the beginning of the map
		iter= m_pPeMap.begin();
			
		// get a random index in range (0, size -1)
		randIndex = rand() % size;	
		
		// increment iterator 'randIndex' number of times
		while (randIndex-- > 0)
		{			
			iter++;
		}
		
		data = static_cast<PeData*>(iter->second);	
	}
	else
	{
		CHECK_BOOL_EX(false, "There are no securities in the DB. "
		                     "Cannot publish data for random security,");
	}
	
Error:	

	return data;
}

/**
 * This is a function gets Random security from the DB
 * and then modifies it's price to be +/-80% of it's 
 * current price.
 *
 * @return true on success, false otherwise
 */	
bool PeEngine::PublishRandomPrice()
{	
	PeData* data = NULL;
	bool retVal = false;
	double price = 0;
	
	// get random security
	data = GetRandomSecurity();
	CHECK_NULL(data);
	
	// grab its price
	price = data->GetPrice();
	
	// randomly shift it's price +-80%
	price *= (((rand() % 2) == 0) ? (1 + EARNINGS_FLUCTUATION_PERC) : (1 - EARNINGS_FLUCTUATION_PERC));
	
	// set it back into the data
	data->SetPrice(price);
		
	retVal = true;
	
Error:

	return retVal;
}
	
/**
 * This is a function gets Random security from the DB
 * and then modifies it's earnings to be +/-20% of it's 
 * current price.
 *
 * @return true on success, false otherwise
 */		
bool PeEngine::PublishRandomEarnings()
{	
	PeData* data = NULL;
	bool retVal = false;
	double earnings = 0;
	
	// get random security
	data = GetRandomSecurity();
	CHECK_NULL(data);
	
	// grab its price
	earnings = data->GetEarnings();
	
	// randomly shift it's price +-20%
	earnings *= (((rand() % 2) == 0) ? (1 + PRICES_FLUCTUATION_PERC) : (1 - PRICES_FLUCTUATION_PERC));
	
	// set it back into the data
	data->SetEarnings(earnings);		

	retVal = true;
	
Error:

	return retVal;	
}

/**
 * This is a function prints the current "state of the nation,"
 * in the sense that it dumps out the current database of P/E
 * data onto the screen. Note that this is meant to run on a 
 * VT100 type terminal, so that you can see nice screen-refreshes.
 *
 * @return true on success, false otherwise
 */	
void PeEngine::PrintDataToScreen()
{
	static int updateIteration = 0;	
	std::tr1::unordered_map<string, PeData*>::iterator iter;
	
	// clear screen and set cursor to first slot
	cout << "\033[2J\033[1;1H";
	
	// display counter/1s tick
	cout << "\r\nUpdate #" << updateIteration++ << "\r\n" << endl; 
	
	// spew header
	cout << setw(10) << fixed << setprecision(2) << "Security" << " |";
	cout << setw(10) << fixed << setprecision(2) << "Price"    << " |";
	cout << setw(10) << fixed << setprecision(2) << "Earnings" << " |";
	cout << setw(10) << fixed << setprecision(2) << "P/E"      << endl;
	
	// spew lines below header
	cout << setw(10) << fixed << setprecision(2) << "________" << " |";
	cout << setw(10) << fixed << setprecision(2) << "________" << " |";
	cout << setw(10) << fixed << setprecision(2) << "________" << " |";
	cout << setw(10) << fixed << setprecision(2) << "________" << endl;
	
	// spew data
	for (iter = m_pPeMap.begin(); iter != m_pPeMap.end(); ++iter)
	{
		PeData *data = static_cast<PeData*>(iter->second);
		cout << setw(10) << fixed << setprecision(2) << iter->first         << " |";
		cout << setw(10) << fixed << setprecision(2) << data->GetPrice()    << " |";
		cout << setw(10) << fixed << setprecision(2) << data->GetEarnings() << " |";
		cout << setw(10) << fixed << setprecision(2) << data->GetPeRatio()  << endl;
	}
	
	// instructions to quit
	cout << "\r\nPress 'Ctrl + C' to exit\r\n";
}
