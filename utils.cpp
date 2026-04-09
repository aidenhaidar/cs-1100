#include "utils.h"
#include <cctype>
#include <ctime>
#include <sstream>

string trim(const string& s) {
    int start = 0;
    int end = s.size() - 1;

    while (start <= end && isspace(s[start])) {
        start++;
    }
    while (end >= start && isspace(s[end])) {
        end--;
    }

    return s.substr(start, end - start + 1);
}

string toLower(const string& s) {
    string result = s;
    for (int i = 0; i < (int)result.size(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

bool answersMatch(const string& input, const string& expected) {
    return toLower(trim(input)) == toLower(trim(expected));
}

string getCurrentTimestamp() {
    time_t now = time(0);
    struct tm* t = localtime(&now);

    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", t);
    return string(buffer);
}

string sanitizeName(const string& name) {
    string result = "";
    for (int i = 0; i < (int)name.size(); i++) {
        if (name[i] != ',') {
            result += name[i];
        }
    }
    return result;
}

string urlDecode(const string& str) {
    string result = "";
    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] == '+') {
            result += ' ';
        } else if (str[i] == '%' && i + 2 < (int)str.size()) {
            // Convert two hex characters to a single character
            string hex = str.substr(i + 1, 2);
            char ch = (char)stoi(hex, nullptr, 16);
            result += ch;
            i += 2;
        } else {
            result += str[i];
        }
    }
    return result;
}

string getFormValue(const string& body, const string& key) {
    string searchKey = key + "=";
    int pos = body.find(searchKey);
    if (pos == (int)string::npos) {
        return "";
    }

    int start = pos + searchKey.size();
    int end = body.find("&", start);
    if (end == (int)string::npos) {
        end = body.size();
    }

    return urlDecode(body.substr(start, end - start));
}
