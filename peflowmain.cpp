#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "commandlineparser.h"
#include "peengine.h"

#define UPDATE_TIME_EARNINIGS 	60
#define UPDATE_TIME_PRICES  	1

using namespace PeFlow;
using namespace std;

volatile bool g_StopSimulation = false;

/**
 * This thread runs every second and checks if it is asked to exit
 * If not, it will ping the P/E engine to publish random prices for
 * random securities
 *      
 * @param obj The P/E enginge
 *
 * @return NULL
 */
void *prices_thread_proc(void* obj)
{
	bool success = false;
	
	// cast in the given engine
	PeEngine* engine = static_cast<PeEngine*>(obj);
			
	// loop till simulation asked to stop
	while (!g_StopSimulation) {
								
		success = engine->PublishRandomPrice();
		CHECK_BOOL_EX(success, "Failed to publish random price");
				
		// print the data to screen for user to see
		engine->PrintDataToScreen();
		
		// sleep for some time
		sleep(UPDATE_TIME_PRICES);	
	}
	
	success = true;
	
Error:		
	
	// if thread is going away, simply ensure that the
	// other thread also exits	
	g_StopSimulation = true;
		
	return NULL;	
}

/**
 * This thread runs every 60s and checks if it is asked to exit
 * If not, it will ping the P/E engine to publish random earnings
 * for random securities.
 *      
 * @param obj The P/E enginge
 *
 * @return NULL
 */
void *earnings_thread_proc(void *obj)
{
	bool success = false;
	
	// cast in the given engine
	PeEngine* engine = static_cast<PeEngine*>(obj);
			
	// loop till simulation done
	while (!g_StopSimulation) {
						
		success = engine->PublishRandomEarnings();
		CHECK_BOOL_EX(success, "Failed to publish random earnings");
		
		// print the data to screen for user to see
		engine->PrintDataToScreen();
		
		// sleep for some time in 1s intervals (poor man's event-driven threading)
		// typically we will wait for some event.
		for (int i = 0; i < (UPDATE_TIME_EARNINIGS/UPDATE_TIME_PRICES) && !g_StopSimulation; i++) {
			sleep(UPDATE_TIME_PRICES);	
		}
	}
	
Error:

	// if thread is going away, simply ensure that the
	// other thread also exits	
	g_StopSimulation = true;
	
	return NULL;
}

/**
 * Main for the P/E Flow Simulation
 *     
 * @note Caller is responsible to call delete on the returned parser.
 *
 * @param argc command line arg count
 * @param argv command line args
 *
 * @return 0 if successful, 1 otherwise
 */	
int main(int argc, char** argv)
{	
	bool success = false;	
	PeEngine* engine = NULL;
	int retVal = 0;
	pthread_t earnings_thread;
	pthread_t prices_thread;
	CommandLineParser* parser = NULL;
	
	// create a parser and have it parse args	
	success = CommandLineParser::CreateParser(argc, argv, &parser);
	CHECK_BOOL_EX(success, "Failed to create command line parser");
	
	// create the pe simulation engine	
	success = PeEngine::CreatePeEngine(parser->GetPeDataFile(), &engine);
	CHECK_BOOL_EX(success , "Failed to create PE Engine");
	
	// create the thread that will update the prices every 1s to simulate
	// external price-modification-events coming into the engine
	retVal = pthread_create(&prices_thread, 0, &prices_thread_proc, (void*)engine);
	CHECK_BOOL_EX((retVal == 0) , "Failed to create quit thread");
	
	// create the thread that updates earnings every 60s to simulate
	// external earnings-modification-events coming into the engine
	retVal = pthread_create(&earnings_thread, 0, &earnings_thread_proc, (void*)engine);
	CHECK_BOOL_EX((retVal == 0) , "Failed to create simulation thread");
				
	// wait for prices' thread to exit	
	pthread_join(prices_thread, 0);
		
	// wait for earnings' thread to exit	
	pthread_join(earnings_thread, 0);
	
	success = true;
	
Error:
	
	delete engine;
	delete parser;
		
	return (success ? EXIT_SUCCESS : EXIT_FAILURE);
}
