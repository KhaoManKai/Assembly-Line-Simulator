// Workshop 1
// Event Module
// Revision History
// -----------------------------------------------------------
// // Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "event.h"
#include "settings.h"

using namespace std;
namespace seneca{
ostream& operator<<(ostream& ostr, const Event& event){
    // For counter, //use a local-to-function variable
    // that remains in memory for the lifetime of the program
    // which is static local counter
    static int counter = 0;
    const string& unit = g_settings.m_time_units;
    long long duration;
    int sizeOftheField;
    
    counter++;
    
    //condition before output
    //The size of 'Duration' depends on 'the Time Units' stored
    // in the global settings which is `g_settings.m_time_units`
    if (unit == "seconds") {
        sizeOftheField = 2;
        duration = chrono::duration_cast<chrono::seconds>(event.m_duration).count();
    }else if (unit == "milliseconds"){
        sizeOftheField = 5;
        duration = chrono::duration_cast<chrono::milliseconds>(event.m_duration).count();
    }else if (unit == "microseconds"){
        sizeOftheField = 8;
        duration = chrono::duration_cast<chrono::microseconds>(event.m_duration).count();
    }else{
        sizeOftheField = 11;
        duration = event.m_duration.count();
    }
    ostr << setw(2) << right << counter << ": " << setw(40) << right << event.m_name << " -> " << setw(sizeOftheField) << right << duration << " " << unit;
    
    return ostr;
}
}
