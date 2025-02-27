// Workshop 4
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 10 Dec 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <iostream>
#include <string>
namespace seneca {

class Utilities {
    static char m_delimiter;
    size_t m_widthField {1};
public:
    void setFieldWidth(size_t newWidth);
    size_t getFieldWidth() const;
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    static void setDelimiter(char newDelimiter);
    static char getDelimiter();
};


}

#endif
