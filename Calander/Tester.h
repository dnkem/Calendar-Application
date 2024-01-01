#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <random>
#include <unordered_set>

using namespace std;

class Tester{
    public:
        void initCapture();
        void endCapture();	
        void pressEnterToContinue();
        void find(vector<int>& keys, const string* search, int& error);
		void findInOrder(vector<int>& keys, const string* search, int& error);
        string getOutput(){return output;}
		// generate a set (no duplicates) of "count" random integers
		// from 0 to "range"
		void ran(vector<int>& list, int count, int range);
		// generate a random integer in the given range
		int ran(int range_from, int range_to);
    private:
        streambuf* oldCoutStreamBuf;
    	ostringstream strCout;
		string output;
};

// strangely difficult to get this to work correctly
void Tester::pressEnterToContinue(){
    std::cout << "Press enter to continue..."<<endl;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char c = cin.get();
    while ( c != '\n') { 
        c = cin.get();
    }
}

void Tester::find(vector<int>& keys, const string* search, int& error){
    int found = -1;
    error = 0;
    vector<int>::iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid]);
        if (found == string::npos){
            std::cout<<search[*ivid]<<" not found"<<endl;
            ++error;
        } 
    }
}

void Tester::findInOrder(vector<int>& keys, const string* search, int& error){
    int found = -1;
    error = 0;
    vector<int>::iterator ivid;
    for (ivid = keys.begin(); ivid != keys.end(); ++ivid){
        found = output.find(search[*ivid], found+1);
        if (found == string::npos){
            std::cout<<search[*ivid]<<" not found in order"<<endl;
            ++error;
        } 
    }
}

void Tester::initCapture(){
    oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream temp;
    strCout.swap(temp);
    std::cout.rdbuf( strCout.rdbuf() );
}

void Tester::endCapture(){
    std::cout.rdbuf( oldCoutStreamBuf );
    output = strCout.str();
    std::cout << output;
}

void Tester::ran(vector<int>& list, int count, int range){
    unordered_set<int> s;
    const int range_from  = 0;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range-1);

    while (s.size() < count){
        s.insert(distr(generator));
    }
    unordered_set<int>::iterator it;
    for (it = s.begin(); it!=s.end();++it){
        list.push_back(*it);
    }
}

// generate and return a single random number in the range range_from to range_to - 1
int Tester::ran(int range_from, int range_to){
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to-1);
    return distr(generator);
}

#endif