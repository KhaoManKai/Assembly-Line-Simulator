// Workshop 4
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 10 Dec 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include "Station.h"
#include "CustomerOrder.h"
#include <iostream>
#include <deque>
#include <string>
namespace seneca {
extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;

class Workstation : public Station{
    std::deque<CustomerOrder> m_orders{};
    Workstation* m_pNextStation{nullptr};
public:
    Workstation(const Workstation&) = delete;
    Workstation& operator = (const Workstation&) = delete;
    Workstation(Workstation&&) = delete;
    Workstation& operator = (Workstation&&) = delete;
    
    Workstation(const std::string& record) : Station(record){};
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station = nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
    bool empty() const;
};


}



#endif
