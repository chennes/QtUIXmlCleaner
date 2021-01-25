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

#include "../Cleaner.h"
#include <QFile>
#include <QTemporaryFile>

using namespace QtXMLCleaner;

TEST_CASE("Test Cleaner creates outfile", "[cleaner]") {
	Cleaner c("XmlWithGrid.ui", "XmlWithGridResult.ui.");
	c.run(); // Synchronous call
	QFile testResult("XmlWithGridResult.ui");
	REQUIRE(testResult.exists());
	testResult.remove();
}

TEST_CASE("Test Cleaner sorts grid", "[cleaner]") {
	Cleaner c("XmlWithGrid.ui","XmlWithGridTest.ui");
	c.SetSortQGridLayoutChildren(true);
	c.run(); // Synchronous call
	QFile testResult("XmlWithGridTest.ui");
	QFile expectedResult("XmlWithGridClean.ui");
	REQUIRE(testResult.exists());
	testResult.open(QIODevice::ReadOnly | QIODevice::Text);
	REQUIRE(testResult.isOpen());
	expectedResult.open(QIODevice::ReadOnly | QIODevice::Text);

	auto testContents = testResult.readAll();
	auto expectedContents = expectedResult.readAll();

	REQUIRE(testContents.compare(expectedContents) == 0);
}