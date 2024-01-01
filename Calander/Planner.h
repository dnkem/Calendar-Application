#ifndef PLANNER_H
#define PLANNER_H

#include "PlannerDate.h"

class Planner{
    public:

        // constructor & destructo
        Planner();
        ~Planner();


        // other
        void addEvent(string title, string description, Date& date, int startTime, int duration);
        void addDailyEvent(string title, string description, Date& startDate, Date& endDate, int startTime, int duration);
        void addWeeklyEvent(string title, string description, Date& startDate, Date& endDate, int startTime, int duration);       

        // printing
        void printAllDates();
        void printDate(Date&);
        void printDatesInRange(Date& startDate, Date& endDate);
        void printDatesWithEvent(string title);
        void printDatesWithConflict();


    private:
        // getters
        PlannerDate* getDate(Date&);

        PlannerDate* plannedDates[MAX_ARRAY];
        int numDates;
};

#endif