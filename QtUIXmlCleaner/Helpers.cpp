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

#include "Helpers.h"

/// To ensure we preserve line endings, keep them around as part of the data.
std::string getlineWithEnding(std::istream& s)
{
	std::string result;
	while (s.good()) {
		char c = s.get();
		if (!s.good())
			break; // Do NOT add this character, it's not real, we hit the end of the file
		result += c;
		if (c == '\r' && s.peek() == '\n')
			result += s.get();
		if (c == '\r' || c == '\n')
			break;
	}
	return result;
}

void RemoveFromString(std::string& line, const std::string& toRemove)
{
	if (auto loc = line.find(toRemove); loc != std::string::npos) {
		line.erase(loc, toRemove.size());
	}
}