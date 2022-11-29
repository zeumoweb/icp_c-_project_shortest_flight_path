#pragma once
#include <string>
#include <vector>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <map>

using std::vector;
using std::string;
using std::ifstream;
using std::endl;
using std::cout;
using std::regex;
using std::sregex_token_iterator;
using std::map;


vector<string> split(string s, string delimiter);
vector<string> split(string s, regex re);
vector< vector<string> > readFile(string filepath);
double convertToRadian(double degree);
double calculateHaversineDistance(double latSource, double lonSource, 
    double latDestination, double lonDestination);