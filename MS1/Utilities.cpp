// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 13/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include 'Utilities.h'

using namespace std;
namespace seneca {

    string& Utilities::trim(string& str) { 
		size_t start = 0;
		while (start < str.length() && isspace(str[start])) {
			start++;
		}

		size_t end = str.length();
		while (end > start && isspace(str[end - 1])) {
			end--;
		}

		str = str.substr(start, end - start);
		return str; 
	}

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    static void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    static char Utilities::getDelimiter() const {
        return m_delimiter;
    }

    // * Uses the delimiter to extract the next token from str starting at position next_pos.
    // * If successful, return a copy of the extracted token found (without spaces at the beginning/end), 
    //      . update next_pos with the position of the next token, and set more to true (false otherwise).
    // * reports an exception if a delimiter is found at next_pos.
    // * updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
    // * Note: in this application, str represents a single line that has been read from an input file.

    string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
        string token;
        size_t position = str.find(getDelimiter(), next_pos);
        bool found = (position != std::string::npos);
        
        if (found) {
            token = str.substr(next_pos, position - next_pos);
            next_pos = position + 1;
            more = true
            if (token.length() > m_widthField)
                m_widthField = token.length();
        } else {
            token = str.substr(next_pos);
            more = false;
        }

        if (next_pos < str.length() && str[next_pos] == m_delimiter)
            throw "Delimiter found at next position";

        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        return token;
    }
}