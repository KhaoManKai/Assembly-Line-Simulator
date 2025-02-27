// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "mediaItem.h"
#include "settings.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
namespace seneca{
class Book : public MediaItem{
 
    std::string m_author{""};
    std::string m_country{""};
    double m_price{0.0};
    
    Book(): MediaItem("","",0){}
    Book(const std::string& author,const std::string& title,const std::string& country,double price,unsigned short year,const std::string& summary)
        : MediaItem(title, summary, year),m_author(author),m_country(country),m_price(price) {}
    friend class MediaItem;
public:
    static std::string trim(const std::string& str);
    void display(std::ostream& out) const override;
    static Book* createItem(const std::string& strBook);
    

    
    
};

}



#endif /* book_h */
