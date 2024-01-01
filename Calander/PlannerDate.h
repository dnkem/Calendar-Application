#ifndef PLANNERDATE_H
#define PLANNERDATE_H

#include "Event.h"

class PlannerDate{
    public:

        // fix: initialize arr?
        // constructor
        PlannerDate(Date&);

        //getter
        // Date getDate(){return date;}

        //other
        bool equals(Date&);
        bool equals(PlannerDate&);
        bool lessThan(Date&);
        bool lessThan(PlannerDate&);
        bool addEvent(string title, string description, int startTime, int duration);
        bool hasEvent(string title);
        bool hasConflict();
        void print();
        
    private:
        Date date;
        Event* arr[MAX_ARRAY];
        int numEvents;
};

#endif