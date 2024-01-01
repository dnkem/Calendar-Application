
#ifndef DATE_H
#define DATE_H

#include "defs.h"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Date {
		
	public:
		//constructor
		Date();
		Date(int year, int month, int day);
		Date(const Date&);
		
		//setters
		void setDay( int);
		void setMonth(int);
		void setYear(int);
		void setDate(int, int, int);
		void setDate(Date&);
		
		//getters
		int getDay();
		int getMonth();
		int getYear();
		string getMonthName();
		
		//other
		void incDate();
		void addDays(int);

		// implement these functions
		bool lessThan(Date& d);
		bool equals(Date& d);

		
		void print();
	
	private:
		//functions
		int getMaxDay();	
	
		//variables
		int day;
		int month;
		int year;
	
};
#endif