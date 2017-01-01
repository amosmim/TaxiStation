/**
 * Amos Maimon And Or Zipori.
 *
 * StringParser Implementation.
 */


#include "StringParser.h"
/**
 * Constructor.
 *
 * @param string
 * @return
 */
StringParser::StringParser(std::string string) {
    str = string;
}

/**
 * This function is in charge of taking a string and spliting it by a delimeter.
 *
 * @param delim
 * @return vector of sting tokens
 */
std::vector<std::string> StringParser::split(char delim) {
    std::vector<std::string> parsedStrings;
    std::stringstream stream(str);
    std::string temp;

    while(getline(stream, temp, delim)) {
        parsedStrings.push_back(temp);
    }

    return parsedStrings;
}

/**
 * Make the class reusable. Set a new string.
 * @param string
 */
void StringParser::setStr(std::string string) {
    str = string;
}


/**
 * Assign Char to Status.
 * @param status
 * @return Status
 */
Status StringParser::getStatusFromChar(char status) {

    switch (status) {
        case 'S':
            return Status::SINGLE;

        case 'D':
            return  Status::DIVORCED;

        case 'W':
            return  Status::WIDOWED;

        case 'M':
            return  Status::MARRIED;
        default:
            perror("wrong Status Key! in : " + status );
    }
}