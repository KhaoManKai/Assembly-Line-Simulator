// Workshop 4
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 10 Dec 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
#include "Station.h"
#include <iomanip>
namespace seneca{
size_t Station::m_widthField = 0;
int Station::id_generator = 0;

Station::Station(const std::string& record) {
    Utilities util;
    size_t next_pos = 0;
    bool more = true;
    try {
        m_name = util.extractToken(record, next_pos, more);
        if (more) {
            m_serialNumber = std::stoi(util.extractToken(record, next_pos, more));
        }
        if (more) {
            m_quantity = std::stoi(util.extractToken(record, next_pos, more));
        }
        m_widthField = std::max(m_widthField, util.getFieldWidth());
        if (more) {
            m_desc = util.extractToken(record, next_pos, more);
        }
        m_id = ++id_generator;
    }
    catch (...) {
        throw;
    }
}

const std::string& Station::getItemName() const {
    return m_name;
}

size_t Station::getNextSerialNumber() {
    return m_serialNumber++;
}

size_t Station::getQuantity() const {
    return m_quantity;
}

void Station::updateQuantity() {
    if (m_quantity > 0) {
        m_quantity--;
    }
}

void Station::display(std::ostream& os, bool full) const {
    os << std::right << std::setw(3) << std::setfill('0') << m_id << " | " << std::left << std::setfill(' ') << std::setw(m_widthField) << m_name << " | " << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";
    
    if (full){
        os << std::setfill(' ') << std::right << std::setw(4) << m_quantity << " | " << m_desc;
    }
    os << std::endl;
}
}
