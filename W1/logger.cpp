// Workshop 1
// Logger Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "logger.h"
#include <iostream>
using namespace std;
namespace seneca {
Logger::Logger() : m_event(nullptr), m_capacity(5), m_currentNum(0) {
    m_event = new Event[m_capacity];
}
void Logger::addEvent(const Event& event){
    if (m_currentNum == m_capacity) {
        resize();
    }
        m_event[m_currentNum++] = event; // always adding event
}
void Logger::resize(){ // increament capacity of the array
    size_t newCapacity = m_capacity * 2;
    Event* newEvent = new Event[newCapacity];
    for (size_t i = 0; i < m_currentNum; ++i) {
        newEvent[i] = m_event[i];
    }
    delete[] m_event;
    m_event = newEvent;
    m_capacity = newCapacity;
}
Logger::Logger(Logger&& other) noexcept : m_event(other.m_event), m_capacity(other.m_capacity), m_currentNum(other.m_currentNum){
    other.m_capacity = 0;
    other.m_event = nullptr;
    other.m_currentNum = 0;
}
Logger& Logger::operator = (Logger&& other) noexcept{
    if (this != &other) {
        delete[] m_event;
        m_event = other.m_event;
        m_capacity = other.m_capacity;
        m_currentNum = other.m_currentNum;
        other.m_event = nullptr;
        other.m_capacity = 0;
        other.m_currentNum = 0;
    }
    return *this;
}
Logger::~Logger(){
    delete [] m_event;
}
ostream& operator<<(ostream& ostr, const Logger& other){
    for (size_t i = 0; i < other.m_currentNum; ++i) {
        ostr << other.m_event[i] << endl;
    }
    return ostr;
}
}
