#include "PlannerDate.h"

PlannerDate::PlannerDate(Date& d){
    numEvents = 0;
    date = d;
}

bool PlannerDate::equals(Date& d){
    if (d.equals(date)){return true;}
    return false;
}
bool PlannerDate::equals(PlannerDate& d){
    if (d.date.equals(date)){ return true;}
    return false;
}
bool PlannerDate::lessThan(Date& d){
    return  date.lessThan(d);
    
}
bool PlannerDate::lessThan(PlannerDate& d){
    return (d.lessThan(d.date));
}

bool PlannerDate::addEvent(string title, string description, int startTime, int duration){
    if (numEvents >= MAX_ARRAY) { return false;}
    int index = 0;

    Event* event = new Event(title, description, startTime, duration);

    while (index < numEvents){
        if (event->lessThan(*arr[index])){
            // this is the place - make some room
            for (int i = numEvents; i > index; --i){
                arr[i] = arr[i-1];
            }
            break;
        }
        ++index;
    }

    cout<<"Adding event "<<title<<" at index "<<index<<endl;
    arr[index] = event;
    ++ numEvents;
    return true;
}

bool PlannerDate::hasEvent(string title){
    int index = 0;
    while (index < numEvents){
        if (title == arr[index]->getTitle()){
            return true;
        }
        ++index;
    }
    cout<<"No event exists with the title: "<<title<<endl;
    return false;
}

bool PlannerDate::hasConflict(){
    int index = 0;
    int oneLess = numEvents - 1;
    while (index < oneLess){
        if (arr[index]->conflictsWith(*arr[index+1])){
            // string t = (*arr[index+1]).getTitle();
            // cout<<"Conflicting event "<< t <<" at index "<<index<<endl;
            return true;
        }
        ++index;
    }
    return false;
}

void PlannerDate::print(){
    cout<<endl;
    cout<<"PRINTING ALL EVENTS FROM: ";
    date.print();
    for (int i=0; i<numEvents; i++){
        arr[i]->print();
    }
}