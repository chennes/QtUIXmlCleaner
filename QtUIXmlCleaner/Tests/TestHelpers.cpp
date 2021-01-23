#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporters_all.hpp>

#include "../Helpers.h"

#include <string>
#include <sstream>

/*
std::string getlineWithEnding(std::istream& s);
void RemoveFromString(std::string& line, const std::string& toRemove);
*/

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