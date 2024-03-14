#include <iostream>
#include <iomanip>

#include "Utilities.h"
#include "Station.h"

using namespace std;
namespace seneca {

    Station::Station(const std::string& src) {
        try {
            Utilities utilities;
            bool check = false;
            size_t position = 0;
            
            m_itemName = utilities.extractToken(src, position, check);
            m_widthField = std::max(m_widthField, m_itemName.size());
            utilities.setFieldWidth(m_widthField);

            if (check) {
                m_nextSerialNumber = std::stoi(utilities.extractToken(src, position, check));
                m_qtyItems = std::stoi(utilities.extractToken(src, position, check));
                
                m_description = utilities.extractToken(src, position, check);
                
                m_id = id_generator++;
            }
        } 
        catch (const char* msg) {
            std::cerr << "Error: " << msg << std::endl;
        }
    }


    const string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        m_nextSerialNumber++;
        return m_nextSerialNumber - 1;
    }

    size_t Station::getQuantity() const {
        return m_qtyItems;
    }

    void Station::updateQuantity() {
        if (getQuantity() >= 1) {
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