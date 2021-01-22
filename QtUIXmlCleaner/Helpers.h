#ifndef _QTUIXMLCLEANER_HELPERS_H_
#define _QTUIXMLCLEANER_HELPERS_H_

#include <string>
#include <istream>

std::string getlineWithEnding(std::istream& s);
void RemoveFromString(std::string& line, const std::string& toRemove);

#endif //_QTUIXMLCLEANER_HELPERS_H_