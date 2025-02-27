// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "movie.h"
namespace seneca{

std::string Movie::trim(const std::string& str){
    auto start = str.find_first_not_of(" \f\n\r");
    if (start == std::string::npos) {return "";}
    auto end = str.find_last_not_of(" \f\n\r");
    return str.substr(start, end -start +1);
}
Movie* Movie::createItem(const std::string& strMovie) {
    if (strMovie.empty() || strMovie[0] == '#') {
        throw "Not a valid movie.";
    }
    
    size_t pos1 = strMovie.find(',');
    if (pos1 == std::string::npos) throw "Not a valid movie.";
    
    size_t pos2 = strMovie.find(',', pos1 + 1);
    if (pos2 == std::string::npos) throw "Not a valid movie.";

    std::string title = trim(strMovie.substr(0, pos1));
    std::string yearStr = trim(strMovie.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string summary = trim(strMovie.substr(pos2 + 1));
    
    try {
        unsigned short year = static_cast<unsigned short>(std::stoi(yearStr));
        return new Movie(title, year, summary);
    } catch (...) {
        throw "Not a valid movie.";
    }
}

void Movie::display(std::ostream& out) const
{
  if (g_settings.m_tableView)
  {
    out << "M | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(9) << this->getYear() << " | ";
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
    out << this->getTitle() << " [" << this->getYear() << "]\n";
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
