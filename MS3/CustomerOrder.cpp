// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 16/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include <vector>
#include <iomanip>

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

    CustomerOrder::CustomerOrder(CustomerOrder& src) {
		throw "Error";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
			src.m_cntItem = 0;
			src.m_name = "";
			src.m_product = "";
		}
		return *this;
	}


	CustomerOrder::~CustomerOrder() {
		if (m_lstItem != 0) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}
	}

	bool CustomerOrder::isOrderFilled() const {
		bool result = true;
		for (size_t i = 0; i < m_cntItem ; i++) {
			if (!m_lstItem[i]->m_isFilled ) {
				result = false;
			}
		}
		return result;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool result = true;
		for (size_t i = 0; i < m_cntItem ; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled ) {
				result = false;
			}
		}
		return result;
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

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;

		for (size_t i = 0; i < m_cntItem; i++) {
			os << std::right;
			os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << setfill(' ') << left;
			os << setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
			os << endl;
		}
	}

}