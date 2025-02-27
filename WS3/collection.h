// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
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

class Collection{
    std::string m_name{""};
    std::vector<MediaItem*>m_items;
    using ObserverFunction = void (*)(const Collection&, const MediaItem&);
    ObserverFunction m_observer;
    
public:
    Collection(const std::string& name);
    Collection(const Collection&) = delete;
    Collection& operator = (const Collection&) = delete;
    Collection(Collection&&) = delete;
    Collection& operator = (Collection&&) = delete;
    virtual ~Collection();
    const std::string& name() const;
    size_t size() const;
    void setObserver(void (*observer)(const Collection&, const MediaItem&));
    Collection& operator+=(MediaItem* item);
    MediaItem* operator[](size_t idx) const;
    MediaItem* operator[](const std::string& title) const;
    void removeQuotes();
    void sort(const std::string& field);
        
};
std::ostream& operator << (std::ostream& ostr, const Collection& collection);

}

#endif /* collection_hpp */
