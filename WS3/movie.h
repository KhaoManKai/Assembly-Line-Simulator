// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"
#include "settings.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

namespace seneca{
class Movie : public MediaItem{
    friend class MediaItem;
    Movie() : MediaItem("", "", 0){}
    Movie(const std::string& title, unsigned short year, const std::string& summary) : MediaItem(title, summary, year){}
public:
    static std::string trim(const std::string& str);
    void display(std::ostream& out) const override;
    static Movie* createItem(const std::string& strMovie);
    
};

}
#endif /* movie_h */
