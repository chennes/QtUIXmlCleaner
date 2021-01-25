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
	Cleaner c("XmlWithGrid.ui", "NewFile.ui");
	c.run(); // Synchronous call
	QFile testResult("NewFile.ui");
	REQUIRE(testResult.exists());
	testResult.remove();
}

TEST_CASE("Test Cleaner sorts grid when sort=true", "[cleaner]") {
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
	testResult.remove();
}

TEST_CASE("Test Cleaner skips grid when sort=false", "[cleaner]") {
	Cleaner c("XmlWithGrid.ui", "XmlWithGridTest2.ui");
	c.SetSortQGridLayoutChildren(false);
	c.run(); // Synchronous call
	QFile testResult("XmlWithGridTest2.ui");
	QFile expectedResult("XmlWithGrid.ui");
	REQUIRE(testResult.exists());
	testResult.open(QIODevice::ReadOnly | QIODevice::Text);
	REQUIRE(testResult.isOpen());
	expectedResult.open(QIODevice::ReadOnly | QIODevice::Text);

	auto testContents = testResult.readAll();
	auto expectedContents = expectedResult.readAll();

	REQUIRE(testContents.compare(expectedContents) == 0);
	testResult.remove();
}

TEST_CASE("Test Cleaner removes stdset=0 when remove=true", "cleaner") {
	Cleaner c("XmlWithStdset.ui", "XmlWithStdsetTest.ui");
	c.SetRemoveStdsetZero(true);
	c.run(); // Synchronous call
	QFile testResult("XmlWithStdsetTest.ui");
	QFile expectedResult("XmlWithStdsetClean.ui");
	REQUIRE(testResult.exists());
	testResult.open(QIODevice::ReadOnly | QIODevice::Text);
	REQUIRE(testResult.isOpen());
	expectedResult.open(QIODevice::ReadOnly | QIODevice::Text);

	auto testContents = testResult.readAll();
	auto expectedContents = expectedResult.readAll();

	REQUIRE(testContents.compare(expectedContents) == 0);
	testResult.remove();
}

TEST_CASE("Test Cleaner removes stdset=0 when remove=false", "cleaner") {
	Cleaner c("XmlWithStdset.ui", "XmlWithStdsetTest2.ui");
	c.SetRemoveStdsetZero(false);
	c.run(); // Synchronous call
	QFile testResult("XmlWithStdsetTest2.ui");
	QFile expectedResult("XmlWithStdset.ui");
	REQUIRE(testResult.exists());
	testResult.open(QIODevice::ReadOnly | QIODevice::Text);
	REQUIRE(testResult.isOpen());
	expectedResult.open(QIODevice::ReadOnly | QIODevice::Text);

	auto testContents = testResult.readAll();
	auto expectedContents = expectedResult.readAll();

	REQUIRE(testContents.compare(expectedContents) == 0);
	testResult.remove();
}

TEST_CASE("Test Cleaner removes native=true when remove=true", "cleaner") {
	Cleaner c("XmlWithNative.ui", "XmlWithNativeTest.ui");
	c.SetRemoveNativeTrue(true);
	c.run(); // Synchronous call
	QFile testResult("XmlWithNativeTest.ui");
	QFile expectedResult("XmlWithNativeClean.ui");
	REQUIRE(testResult.exists());
	testResult.open(QIODevice::ReadOnly | QIODevice::Text);
	REQUIRE(testResult.isOpen());
	expectedResult.open(QIODevice::ReadOnly | QIODevice::Text);

	auto testContents = testResult.readAll();
	auto expectedContents = expectedResult.readAll();

	REQUIRE(testContents.compare(expectedContents) == 0);
	testResult.remove();
}

TEST_CASE("Test Cleaner removes native=true when remove=false", "cleaner") {
	Cleaner c("XmlWithNative.ui", "XmlWithNativeTest2.ui");
	c.SetRemoveNativeTrue(false);
	c.run(); // Synchronous call
	QFile testResult("XmlWithNativeTest2.ui");
	QFile expectedResult("XmlWithNative.ui");
	REQUIRE(testResult.exists());
	testResult.open(QIODevice::ReadOnly | QIODevice::Text);
	REQUIRE(testResult.isOpen());
	expectedResult.open(QIODevice::ReadOnly | QIODevice::Text);

	auto testContents = testResult.readAll();
	auto expectedContents = expectedResult.readAll();

	REQUIRE(testContents.compare(expectedContents) == 0);
	testResult.remove();
}