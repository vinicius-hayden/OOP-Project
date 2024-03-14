#include <iostream>

#include "Utilities.h"
#include "Station.h"

using namespace std;
namespace seneca {

    Station::Station(const string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        string itemName = util.extractToken(record, next_pos, more);
        size_t startingSerial = stoul(util.extractToken(record, next_pos, more));
        size_t quantity = stoul(util.extractToken(record, next_pos, more));
        string description = util.extractToken(record, next_pos, more);

        m_item = itemName;
        m_serialNumber = startingSerial;
        m_quantity = quantity;

        if (m_item.length() > m_widthField)
            m_widthField = m_item.length();
        if (m_item.length() > Utilities::m_widthField)
            Utilities::m_widthField = m_item.length();

        m_description = description;

        m_id = id_generator++;
    }

    const string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        m_nextSerialNumber++;
        return m_nextSerialNumber;
    }

    size_t Station::getQuantity() const {
        return m_qtyItems;
    }

    void Station::updateQuantity() {
        if (getQuantity >= 1) {
            m_qtyItems--;
        }
    }

    void Station::display(ostream& os, bool full) const {
        if (!full) {
            os << setw(3) << m_id << " | " << setw(m_widthField) << m_itemName << " | "  << setw(6) << m_nextSerialNumber << " | " << endl;
        } else {
            os << setw(3) << m_id << " | " << setw(m_widthField) << m_itemName << " | " << setw(6) << m_nextSerialNumber << " | " << setw(4) << m_qtyItems << " | " << m_description << endl;
        }
    }

}