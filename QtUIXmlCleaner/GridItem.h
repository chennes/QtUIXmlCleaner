// MIT License
//
// Copyright(c) 2021 Chris Hennes <chennes@pioneerlibrarysystem.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _QTUIXMLCLEANER_GRIDITEM_H_
#define _QTUIXMLCLEANER_GRIDITEM_H_

#include <istream>
#include <vector>
#include <string>

namespace QtXMLCleaner {

	/**
	 * \brief A single section of the UI file representing a grid item.
	 * 
	 * This class is designed to read and re-deliver a single grid item,
	 * which \a must take the form `<item row="X" column="Y" ...` (the
	 * two attributes do not have to be in that order, but they have to be on
	 * that line). It extracts the row and column information and provides
	 * an `operator<` to allow sorting first on row, then on column. Anything
	 * that lies between the opening `<item>` tag and its matching `</item>`
	 * is blindly included, with no parsing. This includes any QGridLayout
	 * elements, which are not parsed, and not handled any differently than
	 * any other widget (i.e. it does not recurse). The XML must be properly
	 * formed in terms of the number of opening and closing `<item>` tags, but
	 * the contents of those tags is completely unparsed, and simply blindly
	 * stored.
	 */
	class GridItem
	{
	public:

		/**
		 * \brief Constructor
		 * 
		 * \param openTagLine A line of text that contains the opening `<item>` tag. That
		 * tag must contain row and column attributes, and the line must not contain the closing 
		 * `</item>` tag.
		 * \param is The stream from which to read the rest of the item. It must ultimately contain
		 * a closing `</item>` tag that matches the opening tag given by \a openTagLine.
		 * \post The stream \a is is advanced past the end of the line with the closing `</item>`
		 * tag on it. If there is an error this item will sort less than any other GridItem, and
		 * its data will contain only the contents of \a openTagLine.
		 */
		GridItem(const std::string &openTagLine, std::istream& is);
		
		~GridItem() = default;

		/**
		 * \brief Get a copy of the data for this item, suitable for direct writing to a file.
		 */
		std::string data() const;

		/**
		 * \brief Sorts first on row, then on column. So, e.g. Row 1 column 3 is less than 
		 * row 2 column 1.
		 */
		bool operator< (const GridItem& rhs) const;

	private:
		int _row;
		int _column;
		std::vector<std::string> _lines;
	};

}

#endif // _QTUIXMLCLEANER_GRIDITEM_H_
