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
#include "point.h"

using namespace std;
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
    std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");
    bool isInt(std::string st);
    bool isLegitPoint(int px, int py, int gridX, int gridY);
    bool missionInputVerification(std::vector<std::string> input, int mID, int gridX, int gridY,
                                  std::vector<Point> obstacles);

};


#endif //EX1_STRINGPARSER_H
