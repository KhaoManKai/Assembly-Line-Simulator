// Workshop 4
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 10 Dec 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"
#include <iostream>
#include <string>

namespace seneca {
struct Item {
    std::string m_itemName{};
    size_t m_serialNumber{0};
    bool m_isFilled{false};
    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder{
    std::string m_name{};
    std::string m_product{};
    size_t m_cntItem{};
    Item** m_lstItem{nullptr};
    static size_t m_widthField;
    
public:
    CustomerOrder() = default;
    CustomerOrder(const std::string& input);
    CustomerOrder(const CustomerOrder&);
    CustomerOrder& operator=(const CustomerOrder&) = delete;
    CustomerOrder(CustomerOrder&& src) noexcept;
    CustomerOrder& operator=(CustomerOrder&& src) noexcept;
    ~CustomerOrder();
    bool isOrderFilled() const;
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
};
}
#endif
