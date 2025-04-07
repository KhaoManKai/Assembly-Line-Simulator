
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream>
#include <string>
#include "Utilities.h"
namespace seneca{
class Station {
    int m_id{};
    std::string m_name{};
    std::string m_desc{};
    unsigned int m_serialNumber{};
    unsigned int m_quantity{};
    static size_t m_widthField;
    static int id_generator;
    
public:
    Station(const std::string& record);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
};




}
#endif

