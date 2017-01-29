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

    // Because white space from the left is allowed
    str = ltrim(str);

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

/**
 * Check whether a string is an int.
 * @param st
 * @return true is yes, otherwise false.
 */
bool StringParser::isInt(std::string st) {
    for (int i = 0; i < st.size(); i++) {
        if (st.at(i) < 48 || st.at(i) > 57) {
            return false;
        }
    }
    return true;
}

/**
 * Check whether the point is a legit point.
 * @param p
 * @return True if yes, otherwise false.
 */
bool StringParser::isLegitPoint(int px, int py, int gridX, int gridY) {
    if ((px >= 0 && px <= gridX) && (py >= 0 && py <= gridY)) {
        return true;
    }
    return false;
}

/**
 * Check the input for a specific mission.
 *
 * @param input
 * @param mID
 * @return True if yes, otherwise false.
 */
bool StringParser::missionInputVerification(std::vector<std::string> input, int mID, int gridX, int gridY,
                                            std::vector<Point> obstacles) {
    switch(mID) {
        case 2: { // Get trip task
            // We need an input of 8
            if (input.size() != 8) {
                cout << "-1\n";
                return false;
            }

            // Check whether all inputs are integers
            for (int i = 0; i < input.size(); i++) {
                if (!isInt(input[i])) {
                    cout << "-1\n";
                    return false;
                }
            }

            // Specific check for each input :
            int rid = atoi(input[0].c_str());
            int x_start = atoi(input[1].c_str());
            int y_start = atoi(input[2].c_str());
            int x_end = atoi(input[3].c_str());
            int y_end = atoi(input[4].c_str());
            int numPassengers = atoi(input[5].c_str());
            double tariff = atoi(input[6].c_str());
            int onTime = atoi(input[7].c_str());
            // Ride ID
            if (rid < 0) {
                cout << "-1\n";
                return false;
            }
            // Start and End points
            if (!isLegitPoint(x_start, x_end, gridX, gridY) || !isLegitPoint(y_start, y_end, gridX, gridY)) {
                cout << "-1\n";
                return false;
            }
            // Illegal trip
            if (x_start == x_end && y_start == y_end) {
                return false;
            }

            // Illegal trip
            for (int i = 0; i < obstacles.size(); i++) {
                Point p = obstacles[i];

                if ((x_start == p.getX() && y_start == p.getY()) ||
                    (x_end == p.getX() && y_end == p.getY())) {
                    return false;
                }
            }

            // Number of passengers
            if (numPassengers < 0) {
                cout << "-1\n";
                return false;
            }
            // Tariff
            if (tariff < 0) {
                cout << "-1\n";
                return false;
            }
            // Time
            if (onTime <= 0) {
                cout << "-1\n";
                return  false;
            }

        } break;
        case 3: { // Get cab
            // We need an input of 4
            if (input.size() != 4) {
                cout << "-1\n";
                return false;
            }

            // Check whether the first two inputs are integers
            for (int i = 0; i < 2; i++) {
                if (!isInt(input[i])) {
                    cout << "-1\n";
                    return false;
                }
            }

            // Specific check for each input :
            int cid = atoi(input[0].c_str());
            int cabType = atoi(input[1].c_str());

            // Cab ID
            if (cid < 0) {
                cout << "-1\n";
                return false;
            }
            // Cab type
            if (cabType <= 0 || cabType > 2) {
                cout << "-1\n";
                return false;
            }
            // Only one char allowed in choosing car type and car color
            if (input[2].size() != 1 || input[3].size() != 1) {
                cout << "-1\n";
                return false;
            }
            // Validate the correct char for car type
            switch (input[2].at(0)) {
                case 'H':
                case 'T':
                case 'F':
                case 'S':break;
                default: {
                    cout << "-1\n";
                    return false;}
            }
            // Validate the correct char for car color
            switch (input[3].at(0)) {
                case 'R':
                case 'G':
                case 'B':
                case 'W':
                case 'P': break;
                default: {
                    cout << "-1\n";
                    return false;}
            }
        } break;
        case 4: { // Validate driver input
            if (input.size() != 5) {
                return false;
            }

            // Check whether selected inputs are integers
            for (int i = 0; i < input.size(); i++) {
                if (i == 2) { // input[2] supposed to be char
                    continue;
                }
                if (!isInt(input[i])) {
                    return false;
                }
            }

            // Validate the correct char
            switch (input[2].at(0)) {
                case 'M':
                case 'W':
                case 'D':
                case 'S':break;
                default: {
                    return false;}
            }

            int id = atoi(input[0].c_str());
            int age = atoi(input[1].c_str());
            int exp = atoi(input[3].c_str());
            int v_id = atoi(input[4].c_str());
            // id is non negetive
            if (id < 0) {
                return false;
            }
            // age is non negetive
            if (age < 0) {
                return false;
            }
            // expirience is non negetive
            if (exp < 0) {
                return false;
            }
            // vehicle id is non negetive
            if (v_id < 0) {
                return false;
            }
        }

    }

    // All good
    return true;
}

/**
 * Left trim.
 * @param s
 * @param t
 * @return trimmed string.
 */
std::string& StringParser::ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}