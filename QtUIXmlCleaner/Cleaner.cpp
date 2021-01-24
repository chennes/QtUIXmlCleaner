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

#include "Cleaner.h"

#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QTemporaryFile>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>

#include "Helpers.h"
#include "GridItem.h"

using namespace QtXMLCleaner;

Cleaner::Cleaner(const QString& infile, const QString& outfile)
{
	_infile = infile;
	_outfile = outfile;
}

void Cleaner::SetSortQGridLayoutChildren(bool newValue)
{
	_sortQGridLayoutChildren = newValue;
}

void Cleaner::SetRemoveStdsetZero(bool newValue)
{
	_removeStdsetZero = newValue;
}

void Cleaner::SetRemoveNativeTrue(bool newValue)
{
	_removeNativeTrue = newValue;
}

void Cleaner::run()
{

	if (_infile == _outfile) {
		// Let's make a backup, just in case...
		bool copyMade = QFile::copy(_infile, _infile+".original");
		if (!copyMade) {
			emit errorOccurred(QString::fromLatin1("Could not make backup of ") + _infile);
			exit(-1);
			return;
		}
	}

	std::ifstream is(_infile.toStdString());
	if (!is.good()) {
		emit errorOccurred(QString::fromLatin1("Could not open file ") + _infile + " for reading.");
		exit(-1);
		return;
	}

	QString fileToWrite;
	QTemporaryFile temp;
	temp.open();
	if (!temp.isOpen()) {
		emit errorOccurred(QString::fromLatin1("Failed to open a temporary file."));
		exit(-1);
		return;
	}
	while (is.good()) {
		std::string line = getlineWithEnding(is);
		if (_removeNativeTrue)
			RemoveNativeTrue(line);
		if (_removeStdsetZero)
			RemoveStdsetZero(line);
		temp.write(line.c_str());
	}
	is.close();
	fileToWrite = temp.fileName();
	temp.setAutoRemove(false);
	temp.close();
	if (_sortQGridLayoutChildren) {
		is.open(temp.fileName().toStdString());
		QTemporaryFile temp2;

		temp2.open();
		if (!temp2.isOpen()) {
			emit errorOccurred(QString::fromLatin1("Failed to open second a temporary file."));
			exit(-1);
			return;
		}

		while (is.good()) {
			std::string line = getlineWithEnding(is);
			temp2.write(line.c_str());
			if (line.find("class=\"QGridLayout\"") != std::string::npos) {
				std::set<GridItem> gridItems;
				while (is.good()) {
					std::string nextLine = getlineWithEnding(is);
					if (nextLine.find("</layout>") != std::string::npos) {
						temp2.write(nextLine.c_str());
						break;
					}
					else if (nextLine.find("<item") != std::string::npos) {
						gridItems.emplace(nextLine, is);
					}
					else {
						temp2.write(nextLine.c_str());
					}
				}
				for (const auto& item : gridItems) {
					temp2.write(item.data().c_str());
				}
			}
		}
		temp.setAutoRemove(true);
		temp2.setAutoRemove(false);
		fileToWrite = temp2.fileName();
		temp2.close();
	}


	// Write the file out
	QFile out(fileToWrite);
	QFile::remove(_outfile);
	bool renameWorked = out.rename(_outfile);
	if (!renameWorked) {
		out.remove();
		emit errorOccurred(QString::fromLatin1("Could not open output file ") + _outfile + " for writing.");
		exit(-1);
		return;
	}

	emit processComplete();
}

void Cleaner::RemoveNativeTrue(std::string& line) const
{
	RemoveFromString(line, " native=\"true\"");
}

void Cleaner::RemoveStdsetZero(std::string& line) const
{
	RemoveFromString(line, " stdset=\"0\"");
}