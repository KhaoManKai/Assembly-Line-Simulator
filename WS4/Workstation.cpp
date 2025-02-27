// Workshop 4
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 10 Dec 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#include "Workstation.h"
namespace seneca{
std::deque<CustomerOrder> g_pending;
std::deque<CustomerOrder> g_completed;
std::deque<CustomerOrder> g_incomplete;

void Workstation::fill(std::ostream& os){
    if (!m_orders.empty()) {
        m_orders.front().fillItem(*this, os);
    }
}

bool Workstation::attemptToMoveOrder() {
    if (m_orders.empty()) {
        return false;
    }

    CustomerOrder& currentOrder = m_orders.front();
    
    if (currentOrder.isItemFilled(getItemName()) || getQuantity() <= 0) {
        
        if (!m_pNextStation) {
            if (currentOrder.isOrderFilled())
                g_completed.push_back(std::move(currentOrder));
            else
                g_incomplete.push_back(std::move(currentOrder));
        }
        else {
            *m_pNextStation += std::move(currentOrder);
        }
        m_orders.pop_front();
        return true;
    }
    
    return false;
}
void Workstation::setNextStation(Workstation* station){
    m_pNextStation = station;
}

Workstation* Workstation::getNextStation() const{
    return m_pNextStation;
}

void Workstation::display(std::ostream& os) const{
    os << getItemName() << " --> ";
    if (m_pNextStation) {
        os << m_pNextStation->getItemName();
    } else {
        os << "End of Line";
    }
    os << std::endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
    m_orders.push_back(std::move(newOrder));
    return *this;
}

bool Workstation::empty()const{
    return m_orders.empty();
}
}
