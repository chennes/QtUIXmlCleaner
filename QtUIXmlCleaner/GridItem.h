#ifndef _QTUIXMLCLEANER_GRIDITEM_H_
#define _QTUIXMLCLEANER_GRIDITEM_H_

#include <istream>
#include <vector>
#include <string>

namespace QtXMLCleaner {

	class GridItem
	{
	public:
		explicit GridItem(const std::string &openTagLine, std::istream& is);
		~GridItem() = default;

		std::string data() const;

		bool operator< (const GridItem& rhs) const;

	private:
		int _row;
		int _column;
		std::vector<std::string> _lines;
	};

}

#endif // _QTUIXMLCLEANER_GRIDITEM_H_
