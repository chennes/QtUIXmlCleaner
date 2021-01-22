#include "GridItem.h"

#include "Helpers.h"
#include <regex>

#include <iostream>

using namespace QtXMLCleaner;

GridItem::GridItem(const std::string &openTagLine, std::istream& is) :
	_column(-1),
	_row(-1)
{
	std::regex openTagRegex("^\\s*<item");
	std::regex columnRegex("column=\"(\\d+)\"");
	std::regex rowRegex("row=\"(\\d+)\"");
	std::regex closeTagRegex("^\\s*</item>");

	int openTagCounter = 0;
	int closeTagCounter = 0;
	while (is.good()) {
		if (openTagCounter == 0) {
			std::smatch columnMatch;
			if (std::regex_search(openTagLine, columnMatch, columnRegex) && columnMatch.size() == 2) {
				_column = atoi(columnMatch[1].str().c_str());
			}

			std::smatch rowMatch;
			if (std::regex_search(openTagLine, rowMatch, rowRegex) && rowMatch.size() == 2) {
				_row = atoi(rowMatch[1].str().c_str());
			}

			openTagCounter = 1;
			_lines.push_back(openTagLine);

			if (_column == -1 || _row == -1) {
				// An error has occurred here, this is not a grid item
				return;
			}
		}
		else {
			auto line = getlineWithEnding(is);
			if (std::regex_search(line, openTagRegex)) {
				openTagCounter++;
			}
			else if (std::regex_search(line, closeTagRegex)) {
				closeTagCounter++;
			}
			_lines.push_back(line);
			if (openTagCounter == closeTagCounter)
				break;
		}
	}
}

std::string QtXMLCleaner::GridItem::data() const
{
	std::string result;
	for (const auto& line : _lines) {
		result += line;
	}
	return result;
}

bool QtXMLCleaner::GridItem::operator<(const GridItem& rhs) const
{
	if (_row < rhs._row)
		return true;
	else if (_row > rhs._row)
		return false;
	else if (_column < rhs._column)
		return true;
	else if (_column > rhs._column)
		return false;
	else
		return false;
}
