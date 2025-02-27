// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "book.h"
namespace seneca{

std::string Book::trim(const std::string& str){
    auto start = str.find_first_not_of(" \n\f\r");
    if (start == std::string::npos) {return "";}
    auto end = str.find_last_not_of(" \n\f\r");
    return str.substr(start, end - start + 1);
}



Book* Book::createItem(const std::string& strBook) {
    if (strBook.empty() || strBook[0] == '#') {
        throw "Not a valid book.";
    }

    size_t pos1 = strBook.find(',');
    if (pos1 == std::string::npos) throw "Not a valid book.";
    size_t pos2 = strBook.find(',', pos1 + 1);
    if (pos2 == std::string::npos) throw "Not a valid book.";
    size_t pos3 = strBook.find(',', pos2 + 1);
    if (pos3 == std::string::npos) throw "Not a valid book.";
    size_t pos4 = strBook.find(',', pos3 + 1);
    if (pos4 == std::string::npos) throw "Not a valid book.";
    size_t pos5 = strBook.find(',', pos4 + 1);
    if (pos5 == std::string::npos) throw "Not a valid book.";
    
    std::string author = trim(strBook.substr(0, pos1));
    std::string title = trim(strBook.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string country = trim(strBook.substr(pos2 + 1, pos3 - pos2 - 1));
    std::string priceStr = trim(strBook.substr(pos3 + 1, pos4 - pos3 - 1));
    std::string yearStr = trim(strBook.substr(pos4 + 1, pos5 - pos4 - 1));
    std::string summary = trim(strBook.substr(pos5 + 1));
    
    try {
        double price = std::stod(priceStr);
        unsigned short year = static_cast<unsigned short>(std::stoi(yearStr));
        return new Book(author, title, country, price, year, summary);
    } catch (...) {
        throw "Not a valid book.";
    }
}


void Book::display(std::ostream& out) const
{
  if (g_settings.m_tableView)
  {
    out << "B | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(2) << this->m_country << " | ";
    out << std::setw(4) << this->getYear() << " | ";
    out << std::left;
    if (g_settings.m_maxSummaryWidth > -1)
    {
      if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
        out << this->getSummary();
      else
        out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
    }
    else
      out << this->getSummary();
    out << std::endl;
  }
  else
  {
    size_t pos = 0;
    out << this->getTitle() << " [" << this->getYear() << "] [";
    out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
    while (pos < this->getSummary().size())
    {
      out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
      pos += g_settings.m_maxSummaryWidth;
    }
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
      << std::setfill(' ') << '\n';
  }
}
}
