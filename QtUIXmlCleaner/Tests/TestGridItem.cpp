#include <catch2/catch_test_macros.hpp>

#include "../GridItem.h"

#include <string>
#include <sstream>

using namespace QtXMLCleaner;

TEST_CASE("Test GridItem stops at </item>", "[griditem]") {
	std::string openTag("<item row=\"0\" column=\"0\">\n");
	std::string closeTag("</item>\nFoobar\n");
	std::istringstream closeStream(closeTag);
	GridItem g(openTag, closeStream);
	REQUIRE(g.data().find("Foobar") == std::string::npos);
}

TEST_CASE("Test GridItem retains inner item", "[griditem]") {
	std::string openTag("<item row=\"0\" column=\"0\">\n");
	std::string closeTag("<item>\nFoo\n</item>\nBar\n</item>\nBaz\n");
	std::istringstream closeStream(closeTag);
	GridItem g(openTag, closeStream);
	std::string data = g.data();
	REQUIRE(data.find("Foo") != std::string::npos);
	REQUIRE(data.find("Bar") != std::string::npos);
	REQUIRE(data.find("Baz") == std::string::npos);
}

TEST_CASE("Test GridItem row ordering", "[griditem]") {
	std::string rowOneStart("<item row=\"1\" column=\"1\">\n");
	std::string rowOneStop("</item>\n");
	std::istringstream rowOneStream(rowOneStop);
	GridItem rowOne(rowOneStart, rowOneStream);

	std::string rowTwoStart("<item row=\"2\" column=\"0\">\n");
	std::string rowTwoStop("</item>\n");
	std::istringstream rowTwoStream(rowTwoStop);
	GridItem rowTwo(rowTwoStart, rowTwoStream);

	REQUIRE(rowOne < rowTwo);
}

TEST_CASE("Test GridItem column ordering", "[griditem]") {
	std::string columnOneStart("<item row=\"1\" column=\"1\">\n");
	std::string columnOneStop("</item>\n");
	std::istringstream columnOneStream(columnOneStop);
	GridItem columnOne(columnOneStart, columnOneStream);

	std::string columnTwoStart("<item row=\"1\" column=\"2\">\n");
	std::string columnTwoStop("</item>\n");
	std::istringstream columnTwoStream(columnTwoStop);
	GridItem columnTwo(columnTwoStart, columnTwoStream);

	REQUIRE(columnOne < columnTwo);
}