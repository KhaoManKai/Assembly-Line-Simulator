#include "CustomerOrder.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace seneca {
size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(const std::string& input) {
    Utilities util;
    size_t pos = 0;
    bool more = true;
    
    m_name = util.extractToken(input, pos, more);
    m_product = util.extractToken(input, pos, more);

    std::string temp = input.substr(pos);
    m_cntItem = std::count(temp.begin(), temp.end(), util.getDelimiter()) + 1;
    
    m_lstItem = new Item*[m_cntItem];
    for (size_t i = 0; i < m_cntItem && more; i++) {
        std::string item = util.extractToken(input, pos, more);
        m_lstItem[i] = new Item(item);
    }
    
    m_widthField = std::max(m_widthField, util.getFieldWidth());
}

CustomerOrder::CustomerOrder(const CustomerOrder&){
    throw std::string("Cannot make copies.");
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
    *this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
    if (this != &src) {
        if (m_lstItem) {
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
        }
     
        m_name = std::move(src.m_name);
        m_product = std::move(src.m_product);
        m_cntItem = src.m_cntItem;
        m_lstItem = src.m_lstItem;
        
        src.m_name.clear();
        src.m_product.clear();
        src.m_lstItem = nullptr;
        src.m_cntItem = 0;
    }
    return *this;
}

CustomerOrder::~CustomerOrder() {
    if (m_lstItem) {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
    m_lstItem = nullptr;
}

bool CustomerOrder::isOrderFilled() const {
    for (size_t i = 0; i < m_cntItem; i++) {
        if (!m_lstItem[i]->m_isFilled) {
            return false;
        }
    }
    return true;
}
bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    for (size_t i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
            return false;
        }
    }
    return true;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
    for (size_t i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
            if (station.getQuantity() > 0) {
                station.updateQuantity();
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                return;
            } else{
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
        }
    }
}

void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << std::endl;
    for (size_t i = 0; i < m_cntItem; i++) {
        os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
    }
}
}
