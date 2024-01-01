#include "Planner.h"

Planner::Planner(){
    numDates = 0;
}
Planner::~Planner(){
    for (int i=0; i< numDates; i++){
        delete plannedDates[i];
    }
}


PlannerDate* Planner::getDate(Date& d){
    // check if array is full
    if (MAX_ARRAY == numDates) return NULL;

    // checks if date exists in planner, returns it if so
    int index = 0;
    while (index < numDates){
        if (plannedDates[index]->equals(d)){
            cout<<"Date exists"<<endl;
            return plannedDates[index];
        }
        ++index;
    }

    // add to array (via lessThan) and return that new pointer
    PlannerDate* newDate = new PlannerDate(d);
    newDate->print();
    cout<<"Date DOESN'T exists, new one created: " <<endl;

    int index2 = numDates;
    while(index2 > 0){
        if (plannedDates[index2]->lessThan(*newDate)){
            break; // break and add to the current index
        }
        plannedDates[index2] = plannedDates[index2 - 1];
        --index2;
    }
    plannedDates[index2] = newDate;
    ++numDates;

    return plannedDates[index2];
}

void Planner::addEvent(string title, string description, Date& date, int startTime, int duration){
    if (numDates == MAX_ARRAY){
        cerr<<"ERROR - ARRAY IS FULL"<<endl;
        return;
    }

    Event* newEvent = new Event(title, description, startTime, duration);

    // check if date is in planner date, if not - getDates creates new one
    PlannerDate* pDate = getDate(date);
    pDate->addEvent(title, description, startTime, duration);
}

void Planner::addDailyEvent(string title, string description, Date& startDate, Date& endDate, int startTime, int duration){
    // cout<<endl;
    cout<<"DAILY EVENT FROM: "; startDate.print(); cout<<" TO: "; endDate.print();
    Date& index = startDate;
    // check if index is the same as end date

    while(!(index.equals(endDate))){
        addEvent(title, description, index, startTime, duration);
        index.incDate();
    }
    addEvent(title, description, index, startTime, duration);
}

void Planner::addWeeklyEvent(string title, string description, Date& startDate, Date& endDate, int startTime, int duration){
    cout<<"WEEKLY EVENT FROM: "; startDate.print(); 
    cout<<"     TO: "; endDate.print();

    // index to sift through, and endate + 1 for endpoint 
    Date& index = startDate;
    Date& lastDate = endDate;
    lastDate.incDate();

    while (index.lessThan(lastDate)){
        addEvent(title, description, index, startTime, duration);
        index.addDays(7);
    }
}       

void Planner::printAllDates(){
    cout<<endl;
    cout<<"ALL DATES IN PLANNER PRINTED: "<<endl;
    for (int i=0; i<numDates; i++){
        plannedDates[i]->print();
    }
}

void Planner::printDate(Date& d){
    cout<<endl;
    cout<<"Printing specific date: "; d.print(); cout<<endl;
    for (int i=0; i<numDates; i++){
        if (plannedDates[i]->equals(d)){
            plannedDates[i]->print();
        }
    }
    // d.print();
    // cerr<<" - THIS DATE DOES NOT EXIST"<<endl;
}

void Planner::printDatesInRange(Date& startDate, Date& endDate){
    cout<<endl;
    cout<<"Printing dates within range: "; startDate.print(); 
    cout<<"AND "; endDate.print(); cout<<endl;
    Date& index = startDate;

    // start at start date
    // incr start till reaches end
    while(!(index.equals(endDate))){
        printDate(index);
        index.incDate();
    }
    printDate(index);
}

void Planner::printDatesWithEvent(string title){
    cout<<endl;
    cout<<"Printing Dates with title: "<< title << endl;
    for (int i=0; i<numDates; ++i){
        if (plannedDates[i]->hasEvent(title)){   
            plannedDates[i]->print();
        }
    }
}

void Planner::printDatesWithConflict(){
    cout<<endl;
    cout<<"Printing CONFLICTING Dates with title: "<< endl;

    int index = 0;
    while(index < numDates){
        if (plannedDates[index]->hasConflict()){
            plannedDates[index]->print();
        }
        index++;
    }
    
}
