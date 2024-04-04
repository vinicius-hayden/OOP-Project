// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 23/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <sstream>

#include <iomanip>
#include <algorithm>
#include <vector>

#include "CustomerOrder.h"


using namespace std;
namespace seneca {
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const string& str) {
        bool isEmpty = str.empty(); 
        Utilities utils;
        size_t position = 0u;
        bool more;

        m_name = isEmpty ? "" : utils.extractToken(str, position, more);
        m_product = isEmpty ? "" : utils.extractToken(str, position, more);

        vector<string> extractedItems;

        while (!isEmpty && position < str.length()) {
            extractedItems.push_back(utils.extractToken(str, position, more));
        }
        m_cntItem = extractedItems.size();

        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0u; i < m_cntItem; ++i) {
            m_lstItem[i] = new Item(extractedItems[i]);
        }

        m_widthField = max(m_widthField, isEmpty ? 0 : utils.getFieldWidth());
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            for (size_t i = 0u; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete [] m_lstItem;
            m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			
			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
        }
        return *this;
    }
    
    CustomerOrder::CustomerOrder(CustomerOrder& src) {
		throw "Error";
	}
    
    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0u; i < m_cntItem; i++) {
            delete m_lstItem[i];
            m_lstItem[i] = nullptr;
        }
        delete [] m_lstItem;
        m_lstItem = nullptr;
    }

    bool CustomerOrder::isOrderFilled() const {
        bool ok = true;
        for (size_t i = 0u; i  < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                ok = false;
            }
        }
        return ok;
    }

    bool CustomerOrder::isItemFilled(const string& itemName) const {
        bool ok = true;
        for (size_t i = 0u; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName) {
                return m_lstItem[i]->m_isFilled;
            }
        }
        return ok;
    }

    void CustomerOrder::fillItem(Station& station, ostream& os) {
        bool ok = false;
        for (size_t i = 0u; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_isFilled == ok && m_lstItem[i]->m_itemName == station.getItemName()) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    ok = true;
                    os << "    Filled ";
                    
                }
                else {
                    os << "    Unable to fill ";
                }
                os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
        }
    }


    void CustomerOrder::display(ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0u; i < m_cntItem; i++) {
			os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - ";
			
            if (m_lstItem[i]->m_isFilled) {
                os << "FILLED";
            } else {
                os << "TO BE FILLED";
            }
            os << endl;
		}
	}


}