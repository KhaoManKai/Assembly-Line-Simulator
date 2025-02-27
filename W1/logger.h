// Workshop 1
// Logger Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

// the logger module manages a dynamically allocated
// collection of events in the form of an array.
#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
#include <iostream>
#include <stdio.h>
#include <cstddef>
using namespace std;
namespace seneca {
class Logger {
private:
    Event* m_event; // pointer to the dynamically allocated array of `Even` object
    size_t m_capacity;
    size_t m_currentNum;
    void resize(); // resize array when it necessary
public:
    // This class will not support copy operations 
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    ~Logger();
    //constructor
    Logger();
    //move operations
    Logger(Logger&& other) noexcept;
    Logger& operator = (Logger&& other) noexcept;
    void addEvent(const Event& event);
    
    friend ostream& operator<<(ostream& ostr, const Logger& other);
};
}
#endif /* logger_h */
