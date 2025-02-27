// Workshop 4
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 10 Dec 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include "Workstation.h"
#include "CustomerOrder.h"
#include <vector>
#include <fstream>
#include <exception>
#include <algorithm>
namespace seneca {
class LineManager{
    std::vector<Workstation*> m_activeLine{};
    size_t m_cntCustomerOrder{};
    Workstation* m_firstStation{nullptr};
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};
}

#endif
