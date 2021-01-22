#include "Helpers.h"

/// To ensure we preserve line endings, keep them around as part of the data.
std::string getlineWithEnding(std::istream& s)
{
	std::string result;
	while (s.good()) {
		char c = s.get();
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