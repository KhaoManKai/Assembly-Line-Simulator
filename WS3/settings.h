// Workshop 3
//
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 22 NOV 2024   ID 132957234
// NBB  hllee13@myseneca.ca
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <iostream>
#include "tvShow.h"
namespace seneca{



struct Settings{
    int m_maxSummaryWidth = 80;
    bool m_tableView = false;
};
extern Settings g_settings;



}


#endif /* settings_h  */
