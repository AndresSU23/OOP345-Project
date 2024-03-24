// Name: David Andres Sanchez Umbarila
// Seneca Student ID: 140273228
// Seneca email: dasanchez-umbarila@myseneca.ca
// Date of completion: 23/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <stdexcept>

#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {

    size_t CustomerOrder::m_widthField = 1; // initialize static member variable

    CustomerOrder::CustomerOrder(const std::string& record) : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {
        Utilities util;
        size_t next_pos = 0;
        size_t identifierPos = 0;
        bool more = true;

        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);
        identifierPos = next_pos;

        while (more) {
            util.extractToken(record, next_pos, more);
            m_cntItem++;
        }

        if (m_widthField < util.getFieldWidth())
            m_widthField = util.getFieldWidth();

        m_lstItem = new Item * [m_cntItem];
        next_pos = identifierPos;
        more = true;
        for (size_t i = 0; i < m_cntItem; ++i) {
            std::string itemName = util.extractToken(record, next_pos, more);
            m_lstItem[i] = new Item(itemName);
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw std::runtime_error("Ilegal Operatiorn: Copy Constructor");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
        for (size_t i = 0; i < other.m_cntItem; ++i)
            delete other.m_lstItem[i];
        delete[] other.m_lstItem;
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            m_name = other.m_name;
            m_product = other.m_product;
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_name = "";
            other.m_product = "";
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i)
            delete m_lstItem[i];
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";
            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }

}