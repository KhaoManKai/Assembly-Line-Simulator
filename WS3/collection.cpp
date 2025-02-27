// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "collection.h"
namespace seneca{
Collection::Collection(const std::string& name): m_name(name), m_observer(nullptr){}
Collection::~Collection(){
    for(MediaItem* item : m_items){
        delete item;
    }
}
const std::string& Collection::name()const {
    return m_name;
}
size_t Collection::size() const{
    return m_items.size();
}
void Collection::setObserver(ObserverFunction observer){
    m_observer = observer;
}
Collection& Collection::operator+=(MediaItem* item){
    if (item) {
        auto it = std::find_if(m_items.begin(), m_items.end(), [&](const MediaItem* existingItem){
            return existingItem && existingItem->getTitle() == item->getTitle();
        });
        if (it == m_items.end()){
            m_items.push_back(item);
            if (m_observer) {
                m_observer(*this, *item);
            }
        } else{
            delete item;
        }
    }
    return *this;
}
MediaItem* Collection::operator[](size_t idx) const{
    if (idx >= m_items.size()) {
        throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
    }
    return m_items[idx];
}
MediaItem* Collection::operator[](const std::string& title) const {
    if (title.empty()) {
        return nullptr;
    }
    
    std::string searchTitle = title;
    if (searchTitle.front() == '"' && searchTitle.back() == '"') {
        searchTitle = searchTitle.substr(1, searchTitle.length() - 2);
    }
    
    for (auto item : m_items) {
        if (!item) continue;
        
        std::string itemTitle = item->getTitle();
        if (itemTitle.front() == '"' && itemTitle.back() == '"') {
            itemTitle = itemTitle.substr(1, itemTitle.length() - 2);
        }
        
        if (itemTitle == searchTitle) {
            return item;
        }
    }
    
    return nullptr;
}
void Collection::removeQuotes(){
    std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item){
        std::string title= item->getTitle();
        std::string summary = item->getSummary();
        title.erase(std::remove(title.begin(), title.end(), '"'), title.end());
        summary.erase(std::remove(summary.begin(), summary.end(), '"'), summary.end());
        item->setTitle(title);
        item->setSummary(summary);
    });
}
void Collection::sort(const std::string& field){
    std::sort(m_items.begin(), m_items.end(), [field](const MediaItem* a, const MediaItem* b){
           if (field == "title")
               return a->getTitle() < b->getTitle();
           else if (field == "year")
               return a->getYear() < b->getYear();
        return false;
    });
}
std::ostream& operator << (std::ostream& ostr, const Collection& collection){
    for (size_t i = 0; i < collection.size(); i++) {
        ostr << *collection[i];
    }
    return ostr;
}
}
