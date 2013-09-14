#include "String.h"

std::string replace(std::string string, char a, char b) {
	std::string replaced = string;
	for (unsigned i = 0; i < replaced.size(); ++i) {
		if (replaced[i] == a) replaced[i] = b;
	}
	return replaced;
}

std::string replace(std::string string, char a, std::string b) {
	std::string replaced;
	for (unsigned i = 0; i < string.size(); ++i) {
		if (string[i] == a) replaced += b;
		else replaced += string[i];
	}
	return replaced;
}

std::string replace(std::string string, std::string a, std::string b) {
	std::string replaced;
	for (unsigned i = 0; i < string.size();) {
		if (string.substr(i, a.size()) == a) {
			replaced += b;
			i += a.size();
		}
		else {
			replaced += string[i];
			i += 1;
		}
	}
	return replaced;
}

bool endsWith(std::string string, std::string end) {
	if (end.size() > string.size()) return false;
	return string.substr(string.size() - end.size(), end.size()) == end;
}

std::string toUpperCase(std::string string) {
	std::string value = string;
	for (unsigned i = 0; i < string.size(); ++i) {
		if (string[i] >= 'a' && string[i] <= 'z') value[i] = (int)'A' + (int)string[i] - (int)'a';
	}
	return value;
}

bool contains(std::string a, char b) {
	for (unsigned i = 0; i < a.size(); ++i) {
		if (a[i] == b) return true;
	}
	return false;
}

bool contains(std::string a, std::string b) {
	for (unsigned i = 0; i < a.size(); ++i) {
		if (a.substr(i, b.size()) == b) return true;
	}
	return false;
}

int lastIndexOf(std::string a, char b) {
	for (int i = static_cast<int>(a.size() - 1); i >= 0; --i) {
		if (a[i] == b) return i;
	}
	return -1;
}

bool contains(const std::vector<std::string> strings, std::string string) {
	for (std::string s : strings) if (s == string) return true;
	return false;
}

std::vector<std::string> split(std::string string, char c) {
	std::vector<std::string> values;
	unsigned start = 0;
	for (unsigned i = 0; i < string.size(); ++i) {
		if (string[i] == c) {
			values.push_back(string.substr(start, i - start));
			start = i + 1;
		}
	}
	if (start < string.size()) values.push_back(string.substr(start));
	return values;
}

bool startsWith(std::string a, std::string b) {
	return a.substr(0, b.size()) == b;
}
