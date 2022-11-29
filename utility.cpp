#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <map>
#include <cmath>
#include "Airport.h"
#include "utility.h"


// Allows us to split csv files on comma while ignoring strings that contains
// comma as part of it.
const string REGEX = ",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)";

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

vector<string> split(string s, regex re)
{
    vector<string> line;

    sregex_token_iterator iter(s.begin(), s.end(), re, -1);
    sregex_token_iterator end;

    while (iter != end)
    {
        line.push_back(*iter);
        ++iter;
    }

    return line;
}

vector<vector<string> > readFile(string filepath)
{
    string line;
    vector<vector<string> > lines;
    vector<string> vec_line;

    // Use a while loop together with the getline() function to read the file line by line
    ifstream file(filepath);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(split(line, regex(REGEX)));
        }

        file.close();
    }
    return lines;
}

double convertToRadian(double degree)
{
    double pi = 3.14159265359;
    return (degree * (pi / 180));
}

// get the distance between source and destination latitudes and longitudes
double calculateHaversineDistance(double latSource, double lonSource,
                                  double latDestination, double lonDestination)
{
    
    double diffLat = convertToRadian(latDestination - latSource);
    double diffLon = convertToRadian(lonDestination - lonSource);

    latSource = convertToRadian(latSource);
    latDestination = convertToRadian(latDestination);

    // Compute Distance
    double dist = pow(sin(diffLat / 2), 2) +
                  pow(sin(diffLon / 2), 2) *
                      cos(latSource) *
                      cos(latSource);
    double rad = 6371;
    double c = 2 * asin(sqrt(dist));
    return rad * c;
}

