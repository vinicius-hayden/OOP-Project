// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 16/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>

#include "Utilities.h"
#include "Station.h"

using namespace std;
namespace seneca {

    size_t seneca::Station::m_widthField = 0;
    size_t seneca::Station::id_generator = 1;

    Station::Station(const std::string& src) {
        try {
            Utilities utilities;
            bool check = false; // 1
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

    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id
           << " | " << std::left << std::setw(m_widthField + 1) << std::setfill(' ')
           << m_itemName << "| " << std::right << std::setfill('0') << std::setw(6) 
           << m_nextSerialNumber << std::setfill(' ') << " | "
        ;
        
        if (!full) {
            os << std::endl;
        } else {
            os << std::setw(4) << m_qtyItems << " | " << m_description << std::endl;
        }
    }

}