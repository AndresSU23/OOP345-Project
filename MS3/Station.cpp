// Name: David Andres Sanchez Umbarila
// Seneca Student ID: 140273228
// Seneca email: dasanchez-umbarila@myseneca.ca
// Date of completion: 31/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"

namespace seneca {
    Station::Station(const std::string& record) {
        seneca::Utilities util;
        seneca::Utilities util2;
        bool more = true;
        size_t next_pos = 0;

        m_itemName = util.extractToken(record, next_pos, more);
        m_serialNumber = std::stoi(util2.extractToken(record, next_pos, more));
        m_quantity = std::stoi(util2.extractToken(record, next_pos, more));
        m_description = util2.extractToken(record, next_pos, more);

        m_widthField = std::max(util.getFieldWidth(), m_widthField);
        m_id = id_generator++;
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0)
            m_quantity--;
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::setfill('0') << (m_id) << " | "
            << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " | "
            << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | ";
        if (full) {
            os << std::setw(4) << std::setfill(' ') << m_quantity << " | " << m_description;
        }
        os << std::endl;
    }
    size_t Station::m_widthField = 0;
    int Station::id_generator = 1;
}