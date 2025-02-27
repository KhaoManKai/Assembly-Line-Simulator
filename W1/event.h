// Workshop 1
// Event Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////


// the event module stores information about a single
// event that happened during the execution of the program.
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
namespace seneca{
class Event {
private:
    string m_name; // the name of event, type string
    chrono::nanoseconds m_duration; // duration, type chrono::nanoseconds
public:
    Event() : m_name(""), m_duration(chrono::nanoseconds::zero()) {}; // set to defult zero
    Event(const char* name, const chrono::nanoseconds& duration)
    : m_name(name), m_duration(duration) {}; // initializes the current instance with the values of the parameters.
    
    //friend helper function
    friend ostream& operator<<(ostream& ostr, const Event& event);
};
}
#endif /* event_h */

