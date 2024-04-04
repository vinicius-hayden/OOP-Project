// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 16/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

namespace seneca {
    class Station {
            int m_id{};
            std::string m_itemName{};
            std::string m_description{};
            int m_nextSerialNumber{};
            int m_qtyItems{};

            static size_t m_widthField;
            static size_t id_generator;

        public: 
            Station(const std::string& record);
            
            const std::string& getItemName() const;
            size_t getNextSerialNumber();
            size_t getQuantity() const;
            void updateQuantity();
            void display(std::ostream& os, bool full) const
        ;
    };
}

#endif // SENECA_STATION_H