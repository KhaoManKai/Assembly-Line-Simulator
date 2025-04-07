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
