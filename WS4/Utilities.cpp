// Workshop 4
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 10 Dec 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
#include "Utilities.h"

namespace seneca{

char Utilities::m_delimiter{};

void Utilities::setFieldWidth(size_t newWidth){
    this->m_widthField = newWidth;
}
size_t Utilities::getFieldWidth() const{
    return m_widthField;
}
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
    if (next_pos < str.length() && str[next_pos] == m_delimiter) {
        more = false;
        throw std::string("Delimiter found at next_pos");
    }
    
    size_t delim_pos = str.find(m_delimiter, next_pos);
    
    std::string token;
    if (delim_pos != std::string::npos) {
        token = str.substr(next_pos, delim_pos - next_pos);
        next_pos = delim_pos + 1;
        more = true;
    } else {
        token = str.substr(next_pos);
        more = false;
    }
    while (!token.empty() && token.front() == ' ') {
        token.erase(0, 1);
    }
    while (!token.empty() && token.back() == ' ') {
        token.pop_back();
    }
    
    if (token.length() > m_widthField) {
        m_widthField = token.length();
    }
    return token;
}

void Utilities::setDelimiter(char newDelimiter){
    m_delimiter = newDelimiter;
}

char Utilities::getDelimiter(){
    return m_delimiter;
}
}
