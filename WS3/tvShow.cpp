// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "tvShow.h"
#include <cstdint>
#include <iostream>
namespace seneca{
std::list<std::string> TvShow::getLongEpisodes() const {
    std::list<std::string> longtvEp;
    std::vector<TvEpisode> tempEpisodes;
    std::copy_if(m_episodes.begin(), m_episodes.end(), std::back_inserter(tempEpisodes), [](const TvEpisode& episode){
        return episode.m_length >= 60;
    });
    std::transform(tempEpisodes.begin(), tempEpisodes.end(), std::back_inserter(longtvEp), [](const TvEpisode& episode){
        return episode.m_title;
    });
    return longtvEp;
}
double TvShow::getEpisodeAverageLength() const {
    if (m_episodes.empty()) return 0.0;

    double total = std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0, [](double sum, const TvEpisode& episode){
        return sum + (episode.m_length * 60);
    });
    return total / m_episodes.size();
}


std::string TvShow::trim(const std::string& str){
    auto start = str.find_first_not_of(" \f\n\r");
    if (start == std::string::npos) {return "";}
    auto end = str.find_last_not_of(" \f\n\r");
    return str.substr(start, end -start +1);
}

TvShow* TvShow::createItem(const std::string& strShow) {
    if (strShow.empty() || strShow[0] == '#') {
        throw "Not a valid show.";
    }

    size_t pos1 = strShow.find(',');
    if (pos1 == std::string::npos){
        throw "Not a valid show.";
    }
    size_t pos2 = strShow.find(',', pos1 + 1);
    if (pos2 == std::string::npos){
        throw "Not a valid show.";
    }
    size_t pos3 = strShow.find(',', pos2 + 1);
    if (pos3 == std::string::npos){
        throw "Not a valid show.";
    }
    std::string id = trim(strShow.substr(0, pos1));
    std::string title = trim(strShow.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string yearStr = trim(strShow.substr(pos2 + 1, pos3 - pos2 - 1));
    std::string summary = trim(strShow.substr(pos3 + 1));
    
    try {
        size_t showId = std::stoull(id, nullptr, 16);
        unsigned short year = static_cast<unsigned short>(std::stoi(yearStr));
        return new TvShow(showId, title, year, summary);
    } catch (...) {
        throw "Not a valid show.";
    }
}

void TvShow::display(std::ostream& out) const
{
  if (g_settings.m_tableView)
  {
    out << "S | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(2) << this->m_episodes.size() << " | ";
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
    out << this->getTitle() << " [" << this->getYear() << "]\n";
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
    while (pos < this->getSummary().size())
    {
      out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
      pos += g_settings.m_maxSummaryWidth;
    }
    for (auto& item : m_episodes)
    {
      out << std::setfill('0') << std::right;
      out << "    " << 'S' << std::setw(2) << item.m_season
        << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
      if (item.m_title != "")
        out << item.m_title << '\n';
      else
        out << "Episode " << item.m_numberOverall << '\n';

      pos = 0;
      while (pos < item.m_summary.size())
      {
        out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
        pos += g_settings.m_maxSummaryWidth - 8;
      }
    }
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
      << std::setfill(' ') << '\n';
  }
}
}
