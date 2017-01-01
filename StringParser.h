/**
 * Amos Maimon And Or Zipori.
 *
 * StringParser Header.
 */

#ifndef EX1_STRINGPARSER_H
#define EX1_STRINGPARSER_H


#include <string>
#include <vector>
#include <sstream>
#include "Status.h"

/**
 * String Parser.
 *
 * This class is incharge of parsing strings into string tokens, for easy input handle.
 */

class StringParser {
private:
    std::string str;
public:
    StringParser() {}
    StringParser(std::string string);
    std::vector<std::string> split(char delim);
    void setStr(std::string string);
    Status getStatusFromChar(char status);
};


#endif //EX1_STRINGPARSER_H
