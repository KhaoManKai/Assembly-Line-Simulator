// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include "mediaItem.h"
#include "settings.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
#include <sstream>
#include <iomanip>
namespace seneca{
class SpellChecker{
    static const int size = 6;
    std::string m_badWords[size];
    std::string m_goodWords[size];
    size_t m_replacement[size]{};
    SpellChecker() = default;
public:
    SpellChecker(const char* filename);
    void operator()(std::string& text);
    void showStatistics(std::ostream& out) const;
};

}
#endif /* spellChecker_h */
