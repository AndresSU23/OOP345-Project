#include "Utilities.h"
#include <algorithm>
#include <stdexcept>

namespace seneca {
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        if (next_pos >= str.size()) {
            more = false;
            return "";
        }

        size_t delimiter_pos = str.find(m_delimeter, next_pos);

        if (delimiter_pos == std::string::npos) {
            std::string token = str.substr(next_pos);
            token = trim(token);
            next_pos = str.size();
            more = false;
            if (token.size() > m_widthField)
                m_widthField = token.size();
            return token;
        }

        else {
            if (delimiter_pos == next_pos) {
                more = false;
                throw std::runtime_error("Delimiter found at next_pos");
            }
            std::string token = str.substr(next_pos, delimiter_pos - next_pos);
            token = trim(token);
            next_pos = delimiter_pos + 1;
            more = true;
            if (token.size() > m_widthField)
                m_widthField = token.size();
            return token;
        }
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimeter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimeter;
    }

    std::string seneca::Utilities::trim(std::string str) const{
        str.erase(str.begin(), std::find_if_not(str.begin(), str.end(), ::isspace));
        str.erase(std::find_if_not(str.rbegin(), str.rend(), ::isspace).base(), str.end());
        return str;
    }

    char Utilities::m_delimeter = '|';

}
