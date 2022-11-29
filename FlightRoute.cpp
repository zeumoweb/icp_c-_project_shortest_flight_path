#pragma once
#include "FlightRoute.h"


/**
 * Load data from airport csv file.
*/
void FlightRoute::loadAirportData(string airportDataFilePath)
    {
        vector<vector<string> > airport_data = readFile(airportDataFilePath);
        for (auto line : airport_data)
        {
            if (!hasValidIataCode(line))
            {
                continue;
            }
            this->airports[line[AirPort::CODE_INDEX]] = buildAirPortAndCityMap(line);
        }
    }


/**
 * Load data from routes csv file. 
*/
void FlightRoute::loadRoutesData(string routesDataFilePath)
    {
        vector<vector<string> > tempRoutes = readFile(routesDataFilePath);
        for (auto line : tempRoutes)
        {
            addPathToRoutes(line);
        }
    }


/**
 * Checks if an entry in the airports.csv dataset has a valid IATA code.
 *
 * @param line Row in the airport.csv dataset.
 * @return True if valid, and False otherwise.
 */
bool FlightRoute::hasValidIataCode(vector<string> line){
    return !(line[AirPort::CODE_INDEX] == "\\N") && !(line[AirPort::CODE_INDEX] == " ");
}


/**
 * Constructs the cities map by mapping all cities to its list of
 * corresponding connected airports.
 *
 * @param airport vector of string representing a row in the airport dataset.
 * @return A shared pointer to an AirPort Object build using each row of the airport dataset.
 */
shared_ptr<AirPort> FlightRoute::buildAirPortAndCityMap(vector<string> airport)
{
    string cityCode = airport[AirPort::CITY_INDEX] + ", " + airport[AirPort::COUNTRY_INDEX];
    shared_ptr<vector<string> > cityAirports = this->cities[cityCode];
    if (cityAirports == nullptr)
    {
        cityAirports = make_shared<vector<string> >();
        this->cities[cityCode] = cityAirports;
    }
    cityAirports->push_back(airport[AirPort::CODE_INDEX]);

    return make_shared<AirPort>(airport[AirPort::COUNTRY_INDEX], airport[AirPort::CITY_INDEX], airport[AirPort::CODE_INDEX],
                                airport[AirPort::ID_INDEX], std::stod(airport[AirPort::LATITUDE_INDEX]), std::stod(airport[AirPort::LONGITUDE_INDEX]),
                                std::stod(airport[AirPort::ALTITUDE_INDEX]), cityCode);
}


/**
 * Populate information about the different routes in the airport and cities map of the FlightRoute object.
 *
 * @param route A vector of string representing a row in the routes.csv dataset.
 */
void FlightRoute::addPathToRoutes(vector<string> route)
{
    shared_ptr<vector<shared_ptr<AirPort> > > destinationAirports = this->routes[route[FlightRoute::SOURCE_AIRPORT_INDEX]];
    if (destinationAirports == nullptr)
    {
        destinationAirports = make_shared<vector<shared_ptr<AirPort> > >();
        this->routes[route[FlightRoute::SOURCE_AIRPORT_INDEX]] = destinationAirports;
    }

    shared_ptr<AirPort> destinationAirport = this->airports[route[FlightRoute::DESTINATION_AIRPORT_INDEX]];
    if (destinationAirport != nullptr)
    {
        // make a copy of current destination airport
        const AirPort temp = *destinationAirport.get();
        destinationAirport = make_shared<AirPort>(temp);
        destinationAirport->setAirLineCode(route[FlightRoute::AIRLINE_INDEX]);
        destinationAirport->setStops(stoi(route[FlightRoute::NUMBER_OF_STOPS_INDEX]));
        destinationAirports->push_back(destinationAirport);
    }
}


/**
 * Returns all the list of connected Airports to a given city.
 *
 * @param cityCode The unique identifier city code.
 * @return A vector of AirPort objects pointers.
 */
vector<shared_ptr<AirPort> > FlightRoute::getConnectedAirPorts(string cityCode)
{
    vector<shared_ptr<AirPort> > connectedAirPorts;
    for (string airportCode : *this->cities[cityCode])
    {
        if (airportCode.empty())
            continue;

        // check if airport code exist in routes database.
        map<string, shared_ptr<vector<shared_ptr<AirPort> > > >::iterator itr;
        itr = this->routes.find(airportCode);
        if (itr == this->routes.end())
        {
            continue;
        }
        for (auto airport : *this->routes[airportCode])
        {
            // check if there is any routes with the current airport as source.
            map<string, shared_ptr<vector<shared_ptr<AirPort> > > >::iterator itr;
            itr = this->routes.find(airport->getCode());

            if (itr != this->routes.end())
            {
                connectedAirPorts.push_back(airport);
            }
        }
    }
    return connectedAirPorts;
}


/**
 * Find the optimal flight path between two cities and output the result into a
 * text file.
 * The optimal flight path is considered to be the path with the lowest number
 * of flights.
 *
 * @param locationFilePath
 */
void FlightRoute::findOptimalFlightPath(string locationFilePath)
    {
        cout << "\nStart Optimal Path Search...\n" << endl;
        ifstream path(locationFilePath + ".txt");
        if (path.fail()){
            cout << "You entered an invalid file name/path \n Try again \n";
            exit(-1);
        }
        string sourceCity;
        string destinationCity;
        getline(path, sourceCity);
        getline(path, destinationCity);
        deque<shared_ptr<Node> > frontier;
        set<string> explored;

        // find all airports in start city and add them to the frontier.
        for (string airport : *this->cities[sourceCity]) {
            // check if airport in routes.
            if (this->routes.find(airport) == this->routes.end()){
                continue;
            }

            frontier.push_front(make_shared<Node>(sourceCity, nullptr, airport, "", 0, 0, 0));
        }

        while (!frontier.empty())
        {
            shared_ptr<Node> currentCity = frontier.back();
            frontier.pop_back();

            if (currentCity == nullptr) continue;

            shared_ptr<AirPort> currentAirPort = this->airports[currentCity->airport];
            explored.insert(currentCity->cityCode);
            vector<shared_ptr<AirPort> > connectedAirPorts = getConnectedAirPorts(currentCity->cityCode);
            
            for (auto airport : connectedAirPorts)
            {
                double distance = calculateHaversineDistance(currentAirPort->getLatitude(), currentAirPort->getLongitude(), airport->getLatitude(), airport->getLongitude());
                shared_ptr<Node> nextCity = make_shared<Node>(airport->getCityCode(), currentCity, airport->getCode(), airport->getAirLine(),
                                                              currentCity->totalFlights + 1, airport->getStops(), currentCity->totalDistance + distance);
                if (airport->getCityCode() == destinationCity)
                {
                    cout << "Found a path and solution\n" << endl;
                    nextCity->writeFlightPathToFile(locationFilePath + "_output.txt");
                    return;
                }

                if (explored.find(airport->getCityCode()) == explored.end())
                {   
                    frontier.push_front(nextCity);
                }
            }
        }
        cout << "No solution found" << endl;
}
