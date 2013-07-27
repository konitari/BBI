#include "pedata.h"

using namespace PeFlow;

/**
 * This function creates a P/E Data container object
 *     
 * @param price Price of this data security
 * @param earnings Earnings of this security
 * @param peData Created PeData object
 *
 * @note Caller is responsibe for calling delete on peData
 *
 * @return true on success, false otherwise
 */	
bool PeData::CreatePeData(double price, double earnings, PeData **peData)
{
	bool retVal = false;

	PeData* data = new (std::nothrow) PeData(price, earnings);
	CHECK_NULL(data);

	// hand-off
	*peData = data;
	data = NULL;

	retVal = true;

Error:

	delete data;
	return retVal;
}

/**
 * Custom constructor
 *     
 * @param price Price of this data security
 * @param earnings Earnings of this security
 * 
 */	
PeData::PeData(double price, double earnings) : 
	m_Price(price), 
	m_Earnings(earnings)			
{}

PeData::~PeData(void)
{}

/**
 * Returns a P/E ration. Note, earnings of 0 ==> P/E of 0
 *     
 * @return The P/E ratio 
 */	
double PeData::GetPeRatio()
{
	return ((m_Earnings == 0) ? 0.0 : (m_Price / m_Earnings));
}

/**
 * Returns the price of the security
 *     
 * @return The price of the security
 */	
double PeData::GetPrice()
{
	return m_Price;
}

/**
 * Returns the earnings of the security
 *     
 * @return The earnings of the security
 */	
double PeData::GetEarnings()
{
	return m_Earnings;
}

/**
 * Sets the price of the security
 *     
 * @param newPrice The new price of the security
 */	
void PeData::SetPrice(double newPrice)
{
	m_Price = newPrice;
}

/**
 * Sets the earnings of the security
 *     
 * @param newEarnings The new earnings of the security
 */	
void PeData::SetEarnings(double newEarnings)
{
	m_Earnings = newEarnings;
}
