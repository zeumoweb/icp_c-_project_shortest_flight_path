#pragma once

#include "Airport.h"
#include "utility.h"
#include "Node.h"
#include <map>
#include <deque>
#include <set>

using std::deque;
using std::make_shared;
using std::map;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

/**
 * Model flights accross different cities and countries. Allow the computation of
 * the shortest number of flights between two cities.
 *
 * @author Styve Lekane.
 */
class FlightRoute{
    
private:
    static const int AIRLINE_INDEX = 0;
    static const int SOURCE_AIRPORT_INDEX = 2;
    static const int DESTINATION_AIRPORT_INDEX = 4;
    static const int NUMBER_OF_STOPS_INDEX = 7;

    // Maps aiport code to list of connected airports.
    map<string, shared_ptr<vector<shared_ptr<AirPort> > > > routes;
    // Maps aiport code to airport info (AirPort Object).
    map<string, shared_ptr<AirPort> > airports;
    // Maps city to all airport within that city.
    map<string, shared_ptr<vector<string> > > cities;

public:

    FlightRoute(string airportDataPath, string routeDataPath){
        cout << "\nStarted Loading Flight Data... May take a few seconds\n" << endl;
        loadAirportData(airportDataPath);
        loadRoutesData(routeDataPath);
        cout << "Completed Flight Data Loading!!!'\n" << endl;
    }

    void loadAirportData(string airportDataFilePath);

    void loadRoutesData(string routesDataFilePath);

    bool hasValidIataCode(vector<string> line);

    shared_ptr<AirPort> buildAirPortAndCityMap(vector<string> airport);

    vector<shared_ptr<AirPort> > getConnectedAirPorts(string cityCode); 

    void findOptimalFlightPath(string locationFilePath);
    
    void addPathToRoutes(vector<string> route);
};
