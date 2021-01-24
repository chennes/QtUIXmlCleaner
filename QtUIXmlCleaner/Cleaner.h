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


#ifndef _QTUIXMLCLEANER_CLEANER_H_
#define _QTUIXMLCLEANER_CLEANER_H_

#include <QThread>
#include <QException>

class QString;

namespace QtXMLCleaner {

	/**
	 * \brief A worker class to sort the children of a QGridLayout in Row-Column order and to
	 * remove some XML attributes.
	 *
	 * Before running, it should be configured using the `Set*()` family of functions, otherwise
	 * it won't do anything.
	 * 
	 * This is a QThread, so once configured it will run in its own thread. Connect to the
	 * `processComplete()` and `errorOcurred()` signals to be alerted when it has finished.
	 */
	class Cleaner : public QThread {

		Q_OBJECT

	public:

		/**
		 * \brief Construct a Cleaner that reads from \a infile and writes to \a outfile. 
		 * 
		 * \param infile Must be a readable file, and is expected to be a Qt UI XML-formatted file.
		 * \param outfile Must be writable, and can be the same as \a infile. If it is the same, a
		 * backup file is automatically created. \a outfile will only be created in the event of complete
		 * success. Any failures in processing prevent it from being created, or from overwriting
		 * \a infile if that was what was requested.
		 */
		Cleaner(const QString& infile, const QString& outfile);
		
		~Cleaner() = default;
		
		/**
		 * \brief Activate or deactivate sorting the children of a QGridLayout.
		 * 
		 * This is *not* a true XML parser, and does not understand the structure of
		 * an XML file. It searches for the string `class="QGridLayout"` on a line and
		 * assumes that it has found the correct XML element. It then processes each
		 * line below that begins with `(optional whitespace)<item row="X" column="Y"`,
		 * extracts the row and column numbers, and sorts them. It does not recurse,
		 * so a `QGridLayout` that is within a `QGridLayout` is simply treated as any other
		 * widget. It stops when it finds the closing tag of the outermost `QGridLayout`.
		 * It requires that the opening and closing <item> tags are on their own lines, and
		 * treats anything between those tags as a monolithic chunk of data to be included.
		 * 
		 * \param newValue Set to \a true to turn on sorting, or \a false to turn it off.
		 */
		void SetSortQGridLayoutChildren(bool newValue);

		/**
		 * \brief  Activate or deactivate the removal of `stdset="0"`
		 * 
		 * If \a newValue is `true`, removes the first occurrence of the text `stdset="0"` 
		 * from every line in the file. It is not an XML parser, it just does pure text
		 * replacement.
		 * 
		 * \param newValue Set to \a true to turn on removal, or \a false to turn it off.
		 */
		void SetRemoveStdsetZero(bool newValue);

		/**
		 * \brief  Activate or deactivate the removal of `native="true"`
		 *
		 * If \a newValue is `true`, removes the first occurrence of the text `native="true"`
		 * from every line in the file. It is not an XML parser, it just does pure text
		 * replacement.
		 *
		 * \param newValue Set to \a true to turn on removal, or \a false to turn it off.
		 */
		void SetRemoveNativeTrue(bool newValue);

		/**
		 * \brief This function is generally not called directly, but is run on its own thread by calling
		 * the `start()` function on the Cleaner object.
		 */
		void run() override;

	signals:

		/** 
		 * \brief Signals successful completion of the run. 
		 */
		void processComplete();

		/**
		 * \brief Signals failure of the run.
		 * \param message A text message describing the failure.
		 */
		void errorOccurred(QString message);

	private:

		void RemoveNativeTrue(std::string &line) const;
		void RemoveStdsetZero(std::string &line) const;

		bool _sortQGridLayoutChildren = false;
		bool _removeStdsetZero = false;
		bool _removeNativeTrue = false;

		QString _infile;
		QString _outfile;
	};

}

#endif // _QTUIXMLCLEANER_CLEANER_H_