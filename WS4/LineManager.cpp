
#include "LineManager.h"
namespace seneca{

LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stationList) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        throw std::string("Unable to open file: ") + filename;
    }

    std::vector<std::pair<std::string, std::string>> stationPairs;
    std::string lineBuffer;
    while (std::getline(inputFile, lineBuffer)) {
        size_t delimiterPos = lineBuffer.find('|');
        if (delimiterPos != std::string::npos) {
            stationPairs.emplace_back(
                lineBuffer.substr(0, delimiterPos),
                lineBuffer.substr(delimiterPos + 1)
            );
        } else {
            stationPairs.emplace_back(lineBuffer, "");
        }
    }

    m_activeLine.clear();
    std::for_each(stationPairs.begin(), stationPairs.end(), [&](const auto& pair) {
        auto station = std::find_if(stationList.begin(), stationList.end(), [&](const Workstation* ws) { return ws->getItemName() == pair.first;
        });
        if (station != stationList.end()) {
            m_activeLine.push_back(*station);
        }
    });


    std::for_each(stationPairs.begin(), stationPairs.end(), [&](const auto& pair) {
        if (!pair.second.empty()) {
            auto current = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* ws){
                return ws->getItemName() == pair.first;
            });
            auto next = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* ws) { return ws->getItemName() == pair.second;
            });
            if (current != m_activeLine.end() && next != m_activeLine.end()) {
                (*current)->setNextStation(*next);
            }
        }
    });


    m_firstStation = *std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
        return std::none_of(stationPairs.begin(), stationPairs.end(), [&](const auto& pair) { return pair.second == station->getItemName();
        });
    });

    m_cntCustomerOrder = g_pending.size();
}

void LineManager::reorderStations() {
    std::vector<Workstation*> reordered;
    Workstation* current = m_firstStation;
    
    while (current != nullptr) {
        reordered.push_back(current);
        current = current->getNextStation();
    }
    m_activeLine = std::move(reordered);
}

bool LineManager::run(std::ostream& os) {
    static size_t currentItr{1};
    os << "Line Manager Iteration: " << currentItr << std::endl;
    
    if (!g_pending.empty()) {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }
    
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
        station->fill(os);
    });
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station){
        station->attemptToMoveOrder();
    });
    ++currentItr;
    
    return g_pending.empty() && std::all_of(m_activeLine.begin(), m_activeLine.end(),
        [](const Workstation* station) { return station->empty(); });
}
void LineManager::display(std::ostream& os) const{
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
        station->display(os);
    });
}
}
