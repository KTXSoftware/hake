#pragma once

#include <string>
#include <vector>

std::string replace(std::string string, char a, char b);
std::string replace(std::string string, char a, std::string b);
std::string replace(std::string string, std::string a, std::string b);
bool endsWith(std::string string, std::string end);
std::string toUpperCase(std::string string);
bool contains(std::string a, char b);
bool contains(std::string a, std::string b);
int lastIndexOf(std::string a, char b);
bool contains(const std::vector<std::string> strings, std::string string);
std::vector<std::string> split(std::string string, char c);
bool startsWith(std::string a, std::string b);
