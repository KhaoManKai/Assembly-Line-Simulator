// Workshop 1
// TimeMonitor Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "timeMonitor.h"
using namespace std;
namespace seneca {
void TimeMonitor::startEvent(const char* name){
    if (m_checkrun) {
        throw runtime_error("Started already");
    }else{
        m_eventName = name; // store the name of event
        m_start = chrono::steady_clock::now(); // record start time
        m_checkrun = true;
    }
}
Event TimeMonitor::stopEvent(){
    if (!m_checkrun) {
        throw runtime_error("Not start yet");
    }else{
        // calculating the duration, (current time - start time)
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - m_start);
        
        m_checkrun = false;
        
        return Event(m_eventName.c_str(), duration); // return event object with the event's name and duration 
    }
}
}
