// Name: David Andres Sanchez Umbarila
// Seneca Student ID: 140273228
// Seneca email: dasanchez-umbarila@myseneca.ca
// Date of completion: 31/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#pragma once
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>
#include <string>
#include <iostream>
#include "CustomerOrder.h"

namespace seneca {
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{ nullptr };

    public:
        Workstation(const std::string& src) : Station(src) {};
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}

#endif // !SENECA_WORKSTATION_H
