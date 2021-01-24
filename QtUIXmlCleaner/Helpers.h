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

#ifndef _QTUIXMLCLEANER_HELPERS_H_
#define _QTUIXMLCLEANER_HELPERS_H_

#include <string>
#include <istream>

/**
 * \file Helpers.h
 * \brief Contains two general-purpose helper functions: `getlineWithEnding()` and `RemoveFromString()`
 */

/**
 * \brief Similar to std::getline, but includes the line ending character (if there is one).
 * 
 * This retains `\n`, `\r`, and `\r\n` as end of line characters, and includes them in the string.
 * The string cannot be guaranteed to end with one of those combinations, however, as it may
 * represent the end of the file, in which case no line ending character is present.
 * \param s The stream to read from.
 * \returns A string containing the contents of the line, up to and including the line ending character(s).
 * \post \a s is advanced past the line ending characters, and may be in an end-of-file condition.
 */
std::string getlineWithEnding(std::istream& s);

/**
 * \brief Remove the first occurrence of \a toRemove from \a line.
 *
 * \param line The line to be modified.
 * \param toRemove The string to remove from \a line.
 * \post The first occurrence of \a toRemove has been removed from \a line. If \a toRemove is not in \a line,
 * \a line is unchanged
 */
void RemoveFromString(std::string& line, const std::string& toRemove);

#endif //_QTUIXMLCLEANER_HELPERS_H_