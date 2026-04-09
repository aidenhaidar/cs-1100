#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

// Remove leading and trailing whitespace from a string
string trim(const string& s);

// Convert a string to all lowercase letters
string toLower(const string& s);

// Check if the player's answer matches the expected answer
// (case-insensitive, ignores leading/trailing whitespace)
bool answersMatch(const string& input, const string& expected);

// Get a timestamp string like "2026-04-09 14:32"
string getCurrentTimestamp();

// Remove commas from a string (protects CSV format)
string sanitizeName(const string& name);

// URL-decode a string (e.g. "hello+world" or "hello%20world" -> "hello world")
string urlDecode(const string& str);

// Parse a form body like "name=John&answer=hello" into key-value pairs
string getFormValue(const string& body, const string& key);

#endif
