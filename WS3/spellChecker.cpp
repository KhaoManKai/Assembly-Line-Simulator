// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "spellChecker.h"
namespace seneca{
SpellChecker::SpellChecker(const char* filename){
    std::ifstream file(filename);
    if (!file) {
        throw "Bad file name!";
    }
    std::string line;
    size_t index = 0;
    while (getline(file, line) && index < size) {
        std::istringstream ss(line);
        ss >> m_badWords[index];
        ss >> m_goodWords[index];
        index++;
    }
    file.close();
}

void SpellChecker::operator()(std::string& text){
    size_t pos = 0;
    for (size_t i = 0; i < size; i++) {
        while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
            text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
            pos += m_goodWords[i].length();
            m_replacement[i]++;
        }
        pos =0;
    }
}

void SpellChecker::showStatistics(std::ostream& out) const{
    std::cout << "Spellchecker Statistics" << std::endl;
    for (size_t i = 0; i < size; i++) {
        out << std::left << std::setw(15) <<m_badWords[i] << ": " << m_replacement[i] << " replacements" << std::endl;
    }
}
}
