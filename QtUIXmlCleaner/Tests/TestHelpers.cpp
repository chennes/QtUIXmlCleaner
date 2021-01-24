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

#include <catch2/catch_test_macros.hpp>

#include "../Helpers.h"

#include <string>
#include <sstream>

TEST_CASE("Test getlineWithEnding stops at LF", "[helpers]") {
	std::string stringWithLF("Foo\nBar");
	std::istringstream is(stringWithLF);
	auto line = getlineWithEnding(is);
	REQUIRE(line == "Foo\n");
}

TEST_CASE("Test getlineWithEnding stops at CR", "[helpers]") {
	std::string stringWithCR("Foo\rBar");
	std::istringstream is(stringWithCR);
	auto line = getlineWithEnding(is);
	REQUIRE(line == "Foo\r");
}

TEST_CASE("Test getlineWithEnding stops at CRLF", "[helpers]") {
	std::string stringWithCRLF("Foo\r\nBar");
	std::istringstream is(stringWithCRLF);
	auto line = getlineWithEnding(is);
	REQUIRE(line == "Foo\r\n");
}

TEST_CASE("Test getlineWithEnding stops at EOF", "[helpers]") {
	std::string stringWithEOF("FooBar");
	std::istringstream is(stringWithEOF);
	auto line = getlineWithEnding(is);
	REQUIRE(line == "FooBar");
}

TEST_CASE("Test removeFromString removes first instance", "[helpers]") {
	std::string stringToClean("FooBarBaz");
	RemoveFromString(stringToClean, "Bar");
	REQUIRE(stringToClean == "FooBaz");
}