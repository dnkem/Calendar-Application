#include "Event.h"

// fix
// create constructor
// make starttime between 0-23
// make duration at least 1
Event::Event(string title, string description, int startTime, int duration = 1){
    this->title = title;
    this->description = description;
    this->startTime = startTime;
    this->duration = duration;
}

bool Event::equals(Event& e) {
    if (e.title == title){ return true;}
    return false;
}

string Event::getTitle(){
    return title;
}

bool Event::lessThan(Event& e){
    if (startTime < e.startTime){ return true;}
    return false;
}

bool Event::conflictsWith(Event& e){
    // both start at the same time
    if (e.startTime == startTime) {return true;}
    // one overlapping another's end
    if (e.startTime<startTime && ((startTime - e.startTime) < e.duration)) {return true;}  // difference/time inbetween < duration
    if (e.startTime>startTime && ((e.startTime - startTime) > duration)) {return true;} 
    // one within the other
    if (e.startTime<startTime && (((startTime + duration) - (e.startTime + e.duration)) >= 0)) {return true;}  
    if (e.startTime>startTime && (((e.startTime + e.duration) - (startTime + duration)) >= 0)) {return true;}  

    return false;
}

// fix
// improve alignment
void Event::print(){
    cout<<"Title: " << title <<endl;
    cout<<"Description: " << description <<endl;
    cout<<"Start time: " << startTime <<endl;
    cout<<"Duration: " << duration <<endl;
}