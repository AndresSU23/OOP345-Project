// Name: David Andres Sanchez Umbarila
// Seneca Student ID: 140273228
// Seneca email: dasanchez-umbarila@myseneca.ca
// Date of completion: 31/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

namespace seneca {
    LineManager::LineManager(const std::string& file, std::vector<Workstation*>& stations) {
        std::ifstream in(file);
        if (!in) throw std::runtime_error("Cannot open file: " + file);

        std::string line;
        Utilities util;

        while (std::getline(in, line)) {
            size_t next_pos = 0;
            bool more = true;
            auto stationName = util.extractToken(line, next_pos, more);
            auto nextStationName = more ? util.extractToken(line, next_pos, more) : "";

            auto findStationByName = [&](const std::string& name) {
                return std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                    return ws->getItemName() == name;
                    });
                };

            auto currentStation = *findStationByName(stationName);
            Workstation* nextStation = nullptr;

            if (!nextStationName.empty()) {
                nextStation = *findStationByName(nextStationName);
            }

            currentStation->setNextStation(nextStation);
            m_activeLine.push_back(currentStation);
        }

        auto isNotAPredecessor = [&](Workstation* ws) {
            return std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* innerWs) {
                return innerWs->getNextStation() == ws;
                });
            };

        m_firstStation = *std::find_if(m_activeLine.begin(), m_activeLine.end(), isNotAPredecessor);
        m_cntCustomerOrder = g_pending.size();
    }



    void LineManager::reorderStations() {
        std::vector<Workstation*> sorted;
        auto current = m_firstStation;
        while (current != nullptr) {
            sorted.push_back(current);
            current = current->getNextStation();
        }
        m_activeLine = sorted;
    }


    bool LineManager::run(std::ostream& os) {
        static size_t count = 0u;
        os << "Line Manager Iteration: " << ++count << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto& station : m_activeLine) station->fill(os);
        for (auto& station : m_activeLine) station->attemptToMoveOrder();
        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const {
        for (auto& src : m_activeLine) {
            src->display(os);
        }
    }
}
