// Name: David Andres Sanchez Umbarila
// Seneca Student ID: 140273228
// Seneca email: dasanchez-umbarila@myseneca.ca
// Date of completion: 31/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"
#include <deque>

namespace seneca {
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        if (m_orders.empty()) return false;

        if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
            if (m_pNextStation) {
                *m_pNextStation += std::move(m_orders.front());
            }
            else {
                if (!m_orders.front().isOrderFilled())
                    g_incomplete.push_back(std::move(m_orders.front()));
                else
                    g_completed.push_back(std::move(m_orders.front()));
            }
            m_orders.pop_front();
            return true;
        }
        return false;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> "
            << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line") << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

} 