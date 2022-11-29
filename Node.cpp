#pragma once
#include "Node.h"
#include "utility.h"

/**
 * Writes the output path to the output file.
 * @param outputPath Name of output file.
 */
void Node::writeFlightPathToFile(string outputPath)
{
    shared_ptr<Node> curr = make_shared<Node>(this->cityCode, this->parent,this->airport, this->airline, this->totalFlights, this->stops, this->totalDistance);
    int totalStops = 0;
    vector<string> path;
    vector<string> airlinePath;
    vector<string> airportPath;
    vector<int> stops;
    while (curr != NULL)
    {
        path.push_back(curr->cityCode);
        airlinePath.push_back(curr->airline);
        airportPath.push_back(curr->airport);
        stops.push_back(curr->stops);
        totalStops += curr->stops;
        curr = curr->parent;
    }
    std::reverse(path.begin(), path.end());
    std::reverse(airlinePath.begin(), airlinePath.end());
    std::reverse(airportPath.begin(), airportPath.end());
    std::reverse(stops.begin(), stops.end());

    writeToFile(outputPath, airlinePath, airportPath, stops, totalStops, totalFlights, totalDistance);
}



void Node::writeToFile(string outputPath, vector<string> airlinePath, vector<string> airportPath, vector<int> stops, int totalStops, int totalFlights, double totalDistance)
{

    ofstream file(outputPath);
    cout << "Output " << outputPath << endl;
    for (int i = 0; i < airportPath.size() - 1; i++)
    {
        file << airlinePath[i + 1] << " From "
             << airportPath[i] << " To " << airportPath[i + 1]
             << " "
             << stops[i + 1]
             << " "
             << " Stops."
             << endl;
    }
    file << "Total flights: " << totalFlights << "\n"
         << "Total additional stops: " << totalStops << "\n"
         << "Total distance: " << round(totalDistance) << " Km\n"
         << "Optimality criteria: flights" << endl;

    file.close();
}


bool Node::operator==(Node &node)
{
    return node.cityCode == this->cityCode && node.airline == this->airline;
}
