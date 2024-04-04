// Name: Vinicius Souza da Silva
// Seneca Student ID: 135067221
// Seneca email: vhsouza-da-silva@myseneca.ca
// Date of completion: 16/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <string>

#include "Utilities.h"

using namespace std;
namespace seneca {

    char seneca::Utilities::m_delimiter = '\0';

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

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()  {
        return m_delimiter;
    }

    // * Uses the delimiter to extract the next token from str starting at position next_pos.
    // * If successful, return a copy of the extracted token found (without spaces at the beginning/end), 
    //      . update next_pos with the position of the next token, and set more to true (false otherwise).
    // * reports an exception if a delimiter is found at next_pos.
    // * updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
    // * Note: in this application, str represents a single line that has been read from an input file.

    string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        more = false;

        size_t delimiter_pos = str.find(m_delimiter, next_pos);

        if (delimiter_pos == next_pos) {
            throw "   ERROR: No token.";
        }

        string token;

        if (delimiter_pos == std::string::npos) {
            token = str.substr(next_pos);
            next_pos = str.length();
        } else {
            token = str.substr(next_pos, delimiter_pos - next_pos);
            next_pos = delimiter_pos + 1; 
            more = true;
        }

        trim(token);

        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }

        return token;
    }
}