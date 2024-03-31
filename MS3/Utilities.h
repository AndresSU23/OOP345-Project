// Name: David Andres Sanchez Umbarila
// Seneca Student ID: 140273228
// Seneca email: dasanchez-umbarila@myseneca.ca
// Date of completion: 31/03/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {
	class Utilities {
		size_t m_widthField{ 1 };
		static char m_delimeter;

		std::string trim(std::string str) const;

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}

#endif // !SENECA_UTILITIES_H

