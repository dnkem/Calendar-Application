#include <iostream>
#include <random>
#include <sstream>
#include <unordered_set>
#include "Tester.h"
#include "PlannerDate.h"
#include "Planner.h"
#include "Date.h"
#include "Event.h"

#define NUM_EVENTS 4

using namespace std;

// tutorial tests - for convenience, no marks on assignment
int basicEventTest();
int testPlannerDateEvents();
int testPlannerDateEventsOrder();

// assignment tests
int testPlannerEvents();   
int testPlannerEventsOrder(); 
int testAddDaily();
int testAddWeekly();
int testPrintDate(); 
int testPrintDatesConflict();
int testPrintDatesRange();
int testPrintDatesEvent();

int main(){
    int choice = -1;
    while(choice != 0 && cin.good()){
        std::cout<<endl;
        std::cout<<" 0. Exit"<<endl;
        /* These are PlannerDate tests from tutorial 3 */
        std::cout<<" 1. [marked in tutorial 3] basicEventTest (Event class)"<<endl;
        std::cout<<" 2. [marked in tutorial 3] testPlannerDateEvents (PlannerDate class)"<<endl;
        std::cout<<" 3. [marked in tutorial 3] testPlannerDateEvents (proper order, PlannerDate class)"<<endl;

        /* These are Planner tests that will be marked for your assignment */
        std::cout<<endl<<"All tests below are on the Planner class"<<endl<<endl;
        std::cout<<" 4. [2 marks] Test addEvent & printAllDates"<<endl;
        std::cout<<" 5. [2 marks] Test addEvent & printAllDates (proper order)"<<endl;

        std::cout<<" 6. [2 marks] Test addWeeklyEvent / addDailyEvent"<<endl;
        std::cout<<" 7. [2 marks] Test printDate"<<endl;
        std::cout<<" 8. [2 marks] Test printDatesWithConflict"<<endl; 
        std::cout<<" 9. [2 marks] Test printDatesInRange"<<endl;
        std::cout<<" 10. [2 marks] Test printDatesWithEvent"<<endl;


        std::cout<<" 11. [14 marks] Test all and get mark"<<endl<<endl;
        cin >> choice;
        std::cout<<endl;

        // clear the buffer since buffers are a pain in the butt
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice)
        {
            case 1: basicEventTest(); break;
            case 2: testPlannerDateEvents(); break;  
            case 3: testPlannerDateEventsOrder(); break;  

            case 4: testPlannerEvents(); break;  
            case 5: testPlannerEventsOrder(); break;  
            case 6: testAddDaily(); testAddWeekly(); break;
            case 7: testPrintDate(); break;  
            case 8: testPrintDatesConflict(); break;
            case 9: testPrintDatesRange(); break;   
            case 10: testPrintDatesEvent(); break;
            case 11: 
                int score = 0;
                score += testPlannerEvents();   
                score += testPlannerEventsOrder(); 
                score += testAddDaily();
                score += testAddWeekly();
                score += testPrintDate(); 
                score += testPrintDatesConflict();
                score += testPrintDatesRange();
                score += testPrintDatesEvent();
                std::cout << "Your score is "<<score<<" out of 14" << endl << endl;   
                break;
        }
    }
    std::cout<<"Bye!"<<endl;
    return 0;  
}

string titles[NUM_EVENTS] = {"Tutorial", "Lecture", "Lab", "Assignment"};
string descriptions[NUM_EVENTS] = {"Program C++", "Learn C++", "Ask questions", "Make assignment - no segfaults"};


Tester tester;

int basicEventTest(){
    cout << "Testing Event print" << endl << endl;

    Event e1(titles[0], descriptions[0], 10, 2);

    tester.initCapture();
    e1.print();
    tester.endCapture();

    vector<int> keys = {0};

    int error = 0;

    tester.find(keys,titles, error);

    if (error > 0){
        cout << "Event title: "<<titles[0]<<" not found" << endl;
        return 0;
    }

    tester.find(keys,descriptions, error);

    if (error > 0){
        cout << "Event description: "<<descriptions[0]<<" not found" << endl;
        return 0;
    }

    cout<<endl<<"Event::print test passed" << endl << endl;

    cout <<endl<< "Testing Event::lessThan" << endl << endl;

    Event e2(titles[1], descriptions[1], 8, 2);

    e2.print();
    cout<<endl<<"Should be less than"<<endl<<endl;
    e1.print();

    if (e1.lessThan(e2)||!e2.lessThan(e1)){
        cout << "Event::lessThan failed" << endl;
        return 1;
    }
    cout << "Event::lessThan tests passed" << endl;
    return 2;
}


int testPlannerDateEvents(){
    Date d(1,1,2023);
    PlannerDate pd(d);

    cout<<"Testing PlannerDate::equals(Date& d)"<<endl<<endl;

    Date d2(1,1,2023);

    if (!pd.equals(d2)){
        cout << "PlannerDate::equals(Date& d) failed" << endl;
        return 0;
    }

    cout<<"PlannerDate::equals(Date& d) passed"<<endl<<endl;

    cout<<"Testing PlannerDate::lessThan(Date& d)"<<endl<<endl;

    Date d3(1,2,2023);

    if (!pd.lessThan(d3)){
        cout << "PlannerDate::lessThan(Date& d) failed" << endl;
        return 0;
    }

    cout<<"PlannerDate::lessThan(Date& d) passed"<<endl<<endl;

    int startTimes[NUM_EVENTS] = {10, 8, 6, 9};

    cout<<"Testing PlannerDate::addEvent and print"<<endl<<endl;

    for (int i = 0; i < NUM_EVENTS; ++i){
        pd.addEvent(titles[i], descriptions[i], startTimes[i], 2);
    }

    int error = 0;
    tester.initCapture();
    pd.print();
    tester.endCapture();

    cout<<endl<<"Searching output..."<<endl<<endl;

    vector<int> keys = {0, 1, 2, 3};
    tester.find(keys, titles, error);
    if (error>0){
        cout<<"PlannerDate::addEvent failed"<<endl;
        return 1;
    }
    tester.find(keys, descriptions, error);
    if (error>0){
        cout<<"PlannerDate::addEvent failed"<<endl;
        return 1;
    }

    cout<<"PlannerDate::addEvent and print passed"<<endl<<endl;
    return 2;
}

int testPlannerDateEventsOrder(){
    int startTimes[NUM_EVENTS] = {10, 8, 6, 9};
    vector<int> order = {2, 1, 3, 0};

    Date d(1,1,2023);
    PlannerDate pd(d);

    cout<<"Testing PlannerDate::addEvent and print in order"<<endl<<endl;

    for (int i = 0; i < NUM_EVENTS; ++i){
        pd.addEvent(titles[i], descriptions[i], startTimes[i], 2);
    }

    int error = 0;
    tester.initCapture();
    pd.print();
    tester.endCapture();

    
    tester.findInOrder(order, titles, error);
    if (error>0){
        cout<<"PlannerDate::addEvent failed"<<endl;
        return 0;
    }
    tester.findInOrder(order, descriptions, error);
    if (error>0){
        cout<<"PlannerDate::addEvent failed"<<endl;
        return 1;
    }

    cout<<"PlannerDate::addEvent and print in order passed"<<endl<<endl;
    return 2;
}   

int testPlannerEvents(){
    Date d1(2023,1,1);
    Date d2(2023,9,2);

    Planner p;

    cout<<"Testing Planner::addEvent and printAllDates"<<endl<<endl;

    int startTimes[NUM_EVENTS] = {12, 10, 6, 9};

    for (int i = 0; i < NUM_EVENTS; ++i){
        if (i%2==0){
            p.addEvent(titles[i], descriptions[i], d2, startTimes[i], 2);
        } else {
            p.addEvent(titles[i], descriptions[i], d1, startTimes[i], 2);
        }
    }

    tester.initCapture();
    d1.print();
    tester.endCapture();

    cout<<endl<<endl;
    string dates[2] = {tester.getOutput(), ""};

    tester.initCapture();
    d2.print();
    tester.endCapture();

    cout<<endl<<endl;
    dates[1] = tester.getOutput();

    int error = 0;
    tester.initCapture();
    p.printAllDates();
    tester.endCapture();

    cout<<endl<<"Searching output..."<<endl<<endl;

    vector<int> keys = {0, 1};
    tester.find(keys, dates, error);
    if (error>0){
        cout<<"Date not found"<<endl;
        return 0;
    }

    keys = {3,1,2,0};
    tester.find(keys, titles, error);
    if (error>0){
        cout<<"Planner title not found"<<endl;
        return 1;
    }

    tester.find(keys, descriptions, error);
    if (error>0){
        cout<<"Planner description not found"<<endl;
        return 1;
    }

    // cout<<"***MANUAL CHECK***"<<endl;
    // cout<<"Printing Dates: "<<endl;
    // d1.print(); cout<<endl;
    // d2.print(); cout<<endl;
    // cout<<"Make sure no other dates were printed above. If so, 1/2 marks (deduct 1 mark for this test)"<<endl;

    // tester.pressEnterToContinue();

    cout<<"PlannerDate::addEvent and print passed"<<endl<<endl;
    return 2;
}

int testPlannerEventsOrder(){
    Date d1(2023,1,1);
    Date d2(2023,9,2);

    Planner p;

    cout<<"Testing Planner::addEvent and printAllDates for proper Date and Event order"<<endl<<endl;

    int startTimes[NUM_EVENTS] = {12, 10, 6, 9};

    for (int i = 0; i < NUM_EVENTS; ++i){
        if (i%2==0){
            p.addEvent(titles[i], descriptions[i], d2, startTimes[i], 2);
        } else {
            p.addEvent(titles[i], descriptions[i], d1, startTimes[i], 2);
        }
    }

    tester.initCapture();
    d1.print();
    tester.endCapture();

    cout<<endl<<endl;
    string dates[2] = {tester.getOutput(), ""};

    tester.initCapture();
    d2.print();
    tester.endCapture();

    cout<<endl<<endl;
    dates[1] = tester.getOutput();

    int error = 0;
    tester.initCapture();
    p.printAllDates();
    tester.endCapture();

    cout<<endl<<"Searching output..."<<endl<<endl;

    vector<int> keys = {0, 1};
    tester.findInOrder(keys, dates, error);
    if (error>0){
        cout<<"Planner dates are not in order"<<endl;
        return 0;
    }

    cout<<"Dates found in order"<<endl<<endl;

    keys = {3,1,2,0};
    tester.findInOrder(keys, titles, error);
    if (error>0){
        cout<<"Planner titles not in order"<<endl;
        return 1;
    }

    tester.findInOrder(keys, descriptions, error);
    if (error>0){
        cout<<"Planner descriptions not in order"<<endl;
        return 1;
    }

    cout<<"Events found in order"<<endl<<endl;

    cout<<"PlannerDate::addEvent and print (in order) passed"<<endl<<endl;
    return 2;
}

int testAddDaily(){

    const int numDates = 7;
    Date dates[numDates];
    Date start(2023,1,28);
    for (int i = 0; i < numDates; ++i){
        dates[i] = start;
        start.addDays(1);
    }


    string datesOutput[numDates];

    // read in the dates

    cout<<"Reading dates into string array"<<endl<<endl;


    for (int i = 0; i < numDates; ++i){
        tester.initCapture();
        dates[i].print();
        tester.endCapture();
        cout<<endl;
        datesOutput[i] = tester.getOutput();
    }

    Planner p;

    cout<<"Testing Planner::addDailyEvent"<<endl<<endl;

    p.addDailyEvent(titles[0], descriptions[0], dates[0], dates[6], 10, 2);
    // dates[2] = Date(2024,2,1);

    // for (int i = 0; i < numDates; ++i){
    //     p.addEvent(titles[0], dates[i], 10, 2, descriptions[0]);
    // }

    cout<<"Printing all dates"<<endl<<endl;
    tester.initCapture();
    p.printAllDates();
    tester.endCapture();

    cout<<endl<<endl;

    string title[numDates] = {"Tutorial", "Tutorial", "Tutorial", "Tutorial", "Tutorial", "Tutorial", "Tutorial"};
    
    int error = 0;

    cout<<endl<<"Searching output for dates..."<<endl<<endl;

    vector<int> keys = {0, 1, 2, 3, 4, 5, 6};
    tester.find(keys, datesOutput, error);
    if (error>0){
        cout<<"At least one Date not found"<<endl;
        return 0;
    }

    cout<<"All dates found, checking for Event titles"<<endl<<endl;

    tester.findInOrder(keys, title, error);
    if (error>0){
        cout<<"Did not find "<<numDates<<" events with title: "<<title[0]<<endl;
        return 0;
    }


    cout<<"Planner::addDailyEvent passed"<<endl<<endl;
    return 1;
}

int testAddWeekly(){

    const int numDates = 5;
    Date dates[numDates];

    Date start(2023, 9, 28);
    Date end(2023, 10, 28);

    int index = 0;
    
    for (Date i = start; i.lessThan(end); i.addDays(7)){
        dates[index++] = i;
     }


    
    string datesOutput[numDates];

    // read in the dates

    cout<<"Reading dates into string array"<<endl<<endl;


    for (int i = 0; i < numDates; ++i){
        tester.initCapture();
        dates[i].print();
        tester.endCapture();
        datesOutput[i] = tester.getOutput();
    }

    Planner p;

    cout<<"Testing Planner::addDailyEvent"<<endl<<endl;

    p.addWeeklyEvent(titles[1], descriptions[1], start, end, 10, 2);

    tester.initCapture();
    p.printAllDates();
    tester.endCapture();

    cout<<endl<<endl;

    string title[numDates] = {"Lecture", "Lecture", "Lecture", "Lecture", "Lecture"};
    
    int error = 0;

    cout<<endl<<"Searching output for dates..."<<endl<<endl;

    vector<int> keys = {0, 1, 2, 3, 4};
    tester.find(keys, datesOutput, error);
    if (error>0){
        cout<<"At least one Date not found"<<endl;
        return 0;
    }

    cout<<"All dates found"<<endl<<endl;

    tester.findInOrder(keys, title, error);
    if (error>0){
        cout<<"Did not find "<<numDates<<" events with title: "<<title[0]<<endl;
        return 0;
    }


    cout<<"Planner::addWeeklyEvent passed"<<endl<<endl;
    
    return 1;
}


int testPrintDate(){
    const int numDates = 4;
    Date dates[numDates];
    Date start(2023,1,28);
    for (int i = 0; i < numDates; ++i){
        dates[i] = start;
        start.addDays(1);
    }


    string datesOutput[numDates];

    // read in the dates

    cout<<"Reading dates into string array"<<endl<<endl;


    for (int i = 0; i < numDates; ++i){
        tester.initCapture();
        dates[i].print();
        tester.endCapture();
        cout<<endl;
        datesOutput[i] = tester.getOutput();
    }

    Planner p;

    cout<<"Testing Planner::printDate"<<endl<<endl;


    for (int i = 0; i < numDates-1; ++i){
        p.addEvent(titles[i], descriptions[i], dates[i], 10, 2);
    }

    p.addEvent(titles[3], descriptions[3], dates[1], 10, 2);

    cout<<"Printing Date: "<<endl;
    dates[1].print();
    tester.initCapture();
    p.printDate(dates[1]);
    tester.endCapture();

    cout<<endl<<endl;

    
    int error = 0;

    cout<<endl<<"Searching output for Events..."<<endl<<endl;

    vector<int> keys = {1, 3};
    tester.find(keys, titles, error);
    if (error>0){
        cout<<"At least one Event not found"<<endl;
        return 0;
    }

    cout<<"All Events found, searching for Events that should not be printed..."<<endl<<endl;

    keys = {0,2};
    tester.find(keys, titles, error);
    if (error==0){
        cout<<"Found titles that should not be there"<<endl;
        return 1;
    }


    cout<<endl<<"Planner::printDate passed"<<endl<<endl;
    return 2;
}

int testPrintDatesConflict(){
    const int numDates = 4;
    Date dates[numDates];
    Date start(2023,1,28);
    for (int i = 0; i < numDates; ++i){
        dates[i] = start;
        start.addDays(1);
    }


    string datesOutput[numDates];

    // read in the dates

    cout<<"Reading dates into string array"<<endl<<endl;


    for (int i = 0; i < numDates; ++i){
        tester.initCapture();
        dates[i].print();
        tester.endCapture();
        cout<<endl;
        datesOutput[i] = tester.getOutput();
    }

    Planner p;

    cout<<"Testing Planner::printDatesWithConflict"<<endl<<endl;

    p.addEvent(titles[0], descriptions[0], dates[0], 10, 2);
    p.addEvent(titles[1], descriptions[1], dates[0], 11, 2);
    p.addEvent(titles[1], descriptions[1], dates[1], 10, 2);
    p.addEvent(titles[1], descriptions[1], dates[1], 12, 2);
    p.addEvent(titles[2], descriptions[2], dates[2], 10, 2);
    p.addEvent(titles[3], descriptions[3], dates[2], 11, 2);
    p.addEvent(titles[2], descriptions[2], dates[2], 20, 2);
    p.addEvent(titles[3], descriptions[3], dates[3], 11, 2);


    cout<<"Printing Dates with Conflict: "<<endl;
    tester.initCapture();
    p.printDatesWithConflict();
    tester.endCapture();

    cout<<endl<<endl;

    
    int error = 0;

    cout<<endl<<"Searching output for Dates..."<<endl<<endl;

    vector<int> keys = {0,2};
    tester.find(keys, datesOutput, error);
    if (error>0){
        cout<<"At least one Date not found"<<endl;
        return 0;
    }

    cout<<"All Dates found, searching for Dates that should not be printed..."<<endl<<endl;

    keys = {0,1,3};
    tester.find(keys, datesOutput, error);
    if (error==0){
        cout<<"Found Dates that should not be there"<<endl;
        return 1;
    }


    cout<<endl<<"Planner::printDatesWithConflict passed"<<endl<<endl;
    return 2;
}

int testPrintDatesRange(){
    const int numDates = 7;
    Date dates[numDates];
    Date start(2023,1,28);
    for (int i = 0; i < numDates; ++i){
        dates[i] = start;
        start.addDays(1);
    }


    string datesOutput[numDates];

    // read in the dates

    cout<<"Reading dates into string array"<<endl<<endl;


    for (int i = 0; i < numDates; ++i){
        tester.initCapture();
        dates[i].print();
        tester.endCapture();
        cout<<endl;
        datesOutput[i] = tester.getOutput();
    }

    Planner p;

    cout<<"Testing Planner::printDatesRange"<<endl<<endl;


    for (int i = 0; i < numDates-3; ++i){
        p.addEvent(titles[i], descriptions[i], dates[i], 10, 2);
    }

    p.addEvent(titles[3], descriptions[3], dates[4], 10, 2);
    p.addEvent(titles[3], descriptions[3], dates[5], 10, 2);
    p.addEvent(titles[0], descriptions[0], dates[6], 10, 2);


    cout<<"Printing Date range: "<<endl;
    dates[2].print();cout<<endl;
    dates[5].print();cout<<endl;
    tester.initCapture();
    p.printDatesInRange(dates[2], dates[5]);
    tester.endCapture();

    cout<<endl<<endl;

    
    int error = 0;

    cout<<endl<<"Searching output for Dates..."<<endl<<endl;

    vector<int> keys = {2, 3, 4, 5};
    tester.find(keys, datesOutput, error);
    if (error>0){
        cout<<"At least one Date not found"<<endl;
        return 0;
    }

    cout<<"All Dates found, searching for Dates that should not be printed..."<<endl<<endl;

    keys = {0,6};
    tester.find(keys, datesOutput, error);
    if (error==0){
        cout<<"Found Dates that should not be there"<<endl;
        return 1;
    }


    cout<<endl<<"Planner::printDatesInRange passed"<<endl<<endl;
    return 2;
}

int testPrintDatesEvent(){
    const int numDates = 7;
    Date dates[numDates];
    Date start(2023,1,28);
    for (int i = 0; i < numDates; ++i){
        dates[i] = start;
        start.addDays(1);
    }


    string datesOutput[numDates];

    // read in the dates

    cout<<"Reading dates into string array"<<endl<<endl;


    for (int i = 0; i < numDates; ++i){
        tester.initCapture();
        dates[i].print();
        tester.endCapture();
        cout<<endl;
        datesOutput[i] = tester.getOutput();
    }

    Planner p;

    cout<<"Testing Planner::printDatesRange"<<endl<<endl;


    for (int i = 0; i < numDates-3; ++i){
        p.addEvent(titles[i], descriptions[i], dates[i], 10, 2);
    }

    p.addEvent(titles[2], descriptions[2], dates[4], 10, 2);
    p.addEvent(titles[2], descriptions[2], dates[5], 10, 2);
    p.addEvent(titles[2], descriptions[2], dates[6], 10, 2);


    cout<<"Printing Dates with Event: "<<endl;
    cout<<titles[2]<<endl;
    tester.initCapture();
    p.printDatesWithEvent(titles[2]);
    tester.endCapture();

    cout<<endl<<endl;

    
    int error = 0;

    cout<<endl<<"Searching output for Dates..."<<endl<<endl;

    vector<int> keys = {2, 4, 5, 6};
    tester.find(keys, datesOutput, error);
    if (error>0){
        cout<<"At least one Date not found"<<endl;
        return 0;
    }

    cout<<"All Dates found, searching for Dates that should not be printed..."<<endl<<endl;

    keys = {0,1,3};
    tester.find(keys, datesOutput, error);
    if (error==0){
        cout<<"Found Dates that should not be there"<<endl;
        return 1;
    }


    cout<<endl<<"Planner::printDatesWithEvent passed"<<endl<<endl;
    return 2;
}


