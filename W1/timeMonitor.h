// Workshop 1
// TimeMonitor Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

// the timeMonitor module is measuring
// the duration of various operations/events.
#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <stdexcept>
#include "event.h"

using namespace std;
namespace seneca {
class TimeMonitor{
private:
    chrono::steady_clock::time_point m_start; 
    string m_eventName;
    bool m_checkrun;
public:
    TimeMonitor(): m_checkrun(false){};
    void startEvent(const char* name);
    Event stopEvent();
    
};
}
#endif /* timeMonitor_hpp */
