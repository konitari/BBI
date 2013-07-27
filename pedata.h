#ifndef __PEDATA__H__
#define __PEDATA__H__

#include <new>
#include <iomanip>
#include "ehm.h"

namespace PeFlow {

	class PeData
	{

	public:	
		
		static bool CreatePeData(double price, double earnings, PeData **ppPeData);

		double GetPeRatio();

		double GetPrice();

		double GetEarnings();

		void SetPrice(double newPrice);

		void SetEarnings(double newEarnings);

		virtual ~PeData(void);

	private:

		PeData(double price, double earnings);

		double m_Price;

		double m_Earnings;

	};

}
#endif
