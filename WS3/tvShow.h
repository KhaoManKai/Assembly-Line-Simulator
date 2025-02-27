// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
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

namespace seneca {
class TvShow;

struct TvEpisode {
    const TvShow* m_show{};
    unsigned short m_numberOverall{};
    unsigned short m_season{};
    unsigned short m_numberInSeason{};
    std::string m_airDate{};
    unsigned int m_length{};
    std::string m_title{};
    std::string m_summary{};
};

class TvShow: public MediaItem {
    size_t m_id{0};
    std::vector<TvEpisode> m_episodes;
    
    TvShow(): MediaItem("", "", 0){}
    TvShow(size_t id, const std::string& title, unsigned short year, const std::string& summary) : MediaItem(title, summary, year), m_id(id){}
    friend class MediaItem;
public:
    void display(std::ostream& out) const override;
    static TvShow* createItem(const std::string& strShow);
    template<typename Collection_t>
    static void addEpisode(Collection_t& col, const std::string& strEpisode);
    double getEpisodeAverageLength() const;
    static std::string trim(const std::string& str);
    std::list<std::string> getLongEpisodes() const;
};

template<typename Collection_t>
void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode) {
    if (strEpisode.empty() || strEpisode[0] == '#') {
        throw "Not a valid episode.";
    }
    
    size_t pos1 = strEpisode.find(',');//id
    if (pos1 == std::string::npos) throw "Not a valid episode.";
    
    size_t pos2 = strEpisode.find(',', pos1 + 1);//epi num
    if (pos2 == std::string::npos) throw "Not a valid episode.";
    
    size_t pos3 = strEpisode.find(',', pos2 + 1); //season num
    if (pos3 == std::string::npos) throw "Not a valid episode.";
    
    size_t pos4 = strEpisode.find(',', pos3 + 1); //epi num in season
    if (pos4 == std::string::npos) throw "Not a valid episode.";
    
    size_t pos5 = strEpisode.find(',', pos4 + 1); //date
    if (pos5 == std::string::npos) throw "Not a valid episode.";
    
    size_t pos6 = strEpisode.find(',', pos5 + 1);//length
    if (pos6 == std::string::npos) throw "Not a valid episode.";
    
    size_t pos7 = strEpisode.find(',', pos6 + 1); //title
    if (pos7 == std::string::npos) throw "Not a valid episode.";
    
    std::string id = trim(strEpisode.substr(0, pos1));
    std::string epNumStr = trim(strEpisode.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string seasonStr = trim(strEpisode.substr(pos2 + 1, pos3 - pos2 - 1));
    std::string epInSeasonStr = trim(strEpisode.substr(pos3 + 1, pos4 - pos3 - 1));
    std::string airDate = trim(strEpisode.substr(pos4 + 1, pos5 - pos4 - 1));
    std::string lengthStr = trim(strEpisode.substr(pos5 + 1, pos6 - pos5 - 1));
    std::string title = trim(strEpisode.substr(pos6 + 1, pos7 - pos6 - 1));
    std::string summary = trim(strEpisode.substr(pos7 + 1));

    try {
            size_t showId = std::stoull(id, nullptr, 16);
            bool found = false;
                   
            unsigned int minutes = 0;
            size_t colonPos1 = lengthStr.find(':');
            if (colonPos1 != std::string::npos) {
                std::string hourStr = lengthStr.substr(0, colonPos1);
                unsigned int hours = std::stoi(hourStr);
                minutes = hours * 60;
                
                size_t colonPos2 = lengthStr.find(':', colonPos1 + 1);
                size_t periodPos = lengthStr.find('.', colonPos1 + 1);
                size_t secondSep = (colonPos2 != std::string::npos) ? colonPos2 : periodPos;
                
                if (secondSep != std::string::npos) {
                    std::string minStr = lengthStr.substr(colonPos1 + 1, secondSep - (colonPos1 + 1));
                    minutes += std::stoi(minStr);
                } else {
                    std::string minStr = lengthStr.substr(colonPos1 + 1);
                    minutes += std::stoi(minStr);
                }
            }

            for (size_t i = 0; i < col.size(); i++) {
                TvShow* show = dynamic_cast<TvShow*>(col[i]);
                if (show && show->m_id == showId) {
                    show->m_episodes.push_back(TvEpisode{
                        show,
                        static_cast<unsigned short>(std::stoi(epNumStr)),
                        static_cast<unsigned short>(seasonStr.empty() ? 1 : std::stoi(seasonStr)),
                        static_cast<unsigned short>(std::stoi(epInSeasonStr)),
                        airDate,
                        minutes,
                        title,
                        summary
                    });
                    found = true;
                    break;
                }
            }
            if(!found) {
                throw "Not a valid episode.";
            }
    } catch (...) {
        throw "Not a valid episode.";
    }
}
 
}
#endif /* tvShow_h */
