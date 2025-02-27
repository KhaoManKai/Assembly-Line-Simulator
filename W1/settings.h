// Workshop 1
// Settings Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

// The settings module will contain functionality regarding
// configuration of the application.
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <iostream>
#include <string>
#include <stdio.h>

namespace seneca {
struct Settings {
    //public members
    bool m_show_all = false;
    bool m_verbose = false;
    std::string m_time_units = "nanoseconds";
};
extern Settings g_settings; // declaration a global variable 
}
#endif /* settings_h*/
