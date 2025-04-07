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
