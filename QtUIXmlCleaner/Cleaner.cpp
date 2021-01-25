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

#include <QFile>

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>
#include <filesystem>

#include "Helpers.h"
#include "GridItem.h"

using namespace QtXMLCleaner;

Cleaner::Cleaner(const std::string& infile, const std::string& outfile)
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
		// Make a backup:
		try {
			std::filesystem::copy(_infile, _infile + ".backup");
		}
		catch (...) {
			emit errorOccurred(std::string("Could not make a backup of ") + _infile);
			exit(-1);
			return;
		}
	}

	std::ifstream is(_infile);
	if (!is.good()) {
		emit errorOccurred(std::string("Could not open file ") + _infile + " for reading.");
		exit(-1);
		return;
	}

	std::ostringstream firstPassOut;
	while (is.good() && firstPassOut.good()) {
		std::string line = getlineWithEnding(is);
		if (_removeNativeTrue)
			RemoveNativeTrue(line);
		if (_removeStdsetZero)
			RemoveStdsetZero(line);
		firstPassOut.write(line.data(),line.size());
	}
	is.close();

	std::istringstream firstPassIn(firstPassOut.str());
	std::ostringstream secondPassOut;

	while (firstPassIn.good() && secondPassOut.good()) {
		std::string line = getlineWithEnding(firstPassIn);
		secondPassOut.write(line.data(), line.size());
		if (_sortQGridLayoutChildren && line.find("class=\"QGridLayout\"") != std::string::npos) {
			std::set<GridItem> gridItems;
			while (firstPassIn.good()) {
				std::string nextLine = getlineWithEnding(firstPassIn);
				if (nextLine.find("</layout>") != std::string::npos) {
					for (const auto& item : gridItems) {
						std::string data = item.data();
						secondPassOut.write(data.data(), data.size());
					}
					secondPassOut.write(nextLine.data(), nextLine.size());
					break;
				}
				else if (nextLine.find("<item") != std::string::npos) {
					gridItems.emplace(nextLine, firstPassIn);
				}
				else {
					// Some kind of data before the next item? Just write it out now, but it really shouldn't be there
					secondPassOut.write(nextLine.data(), nextLine.size());
				}
			}
		}
	}

	std::ofstream os(_outfile);
	if (os.bad()) {
		emit errorOccurred(std::string("Could not open output file ") + _outfile + " for writing.");
		exit(-1);
		return;
	}
	os.write(secondPassOut.str().data(), secondPassOut.str().size());
	
	if (os.bad()) {
		emit errorOccurred(std::string("Error writing data to ") + _outfile);
		exit(-1);
		return;
	}
	os.close();

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