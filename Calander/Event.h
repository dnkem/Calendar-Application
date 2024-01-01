#ifndef EVENT_H
#define EVENT_H

#include "Date.h"

class Event{
    public:

        // constructor
        Event(string title, string description, int startTime, int duration);

        string getTitle();

        //other
        bool equals(Event&);
        bool lessThan(Event& e);
        bool conflictsWith(Event& e);
        void print();
        
    private:
        string title;
        string description;
        int startTime;  // 0 - 23
        int duration; // hours
};

#endif