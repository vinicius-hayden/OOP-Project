// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 23/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <string>

#include "Station.h"
#include "Utilities.h"

namespace seneca {
	
    struct Item {
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
            std::string m_name{};
            std::string m_product{};
            size_t m_cntItem{};
            Item** m_lstItem{};
            static size_t m_widthField;
	    public:
            CustomerOrder() = default;

            CustomerOrder(const std::string& str);
            CustomerOrder(CustomerOrder& src);
            CustomerOrder& operator=(CustomerOrder& src) = delete;
            CustomerOrder(CustomerOrder&& src) noexcept;
            CustomerOrder& operator=(CustomerOrder&& src) noexcept;
            
            ~CustomerOrder();
            bool isOrderFilled() const;
            bool isItemFilled(const std::string& itemName) const;
            void fillItem(Station& station, std::ostream& os);
            void display(std::ostream& os) const
        ;
	};
}
#endif // !SDDS_CUSTOMERORDER_H