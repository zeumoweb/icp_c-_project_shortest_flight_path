#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using std::make_shared;
using std::reverse;
using std::shared_ptr;
using std::string;
using std::vector;
using std::ofstream;

/**
 * Models the state of an traveller at any given point along the path between the source city and the destination city.
 * @author Styve Lekane
 */
class Node
{

    public:
        string cityCode;
        string airline;
        string airport;
        shared_ptr<Node> parent;
        int totalFlights = 0;
        int stops = 0;
        double totalDistance;

        Node(string cityCode, shared_ptr<Node> parent, string airport, string airline, int totalFlights, int stops,
            double totalDistance)
        {
            this->cityCode = cityCode;
            this->parent = parent;
            this->totalFlights = totalFlights;
            this->stops = stops;
            this->airline = airline;
            this->airport = airport;
            this->totalDistance = totalDistance;
        }

        Node(const Node& node){
            this->cityCode = node.cityCode;
            this->parent = node.parent;
            this->totalFlights = node.totalFlights;
            this->stops = node.stops;
            this->airline = node.airline;
            this->airport = node.airport;
            this->totalDistance = node.totalDistance;
        }

        bool operator==(const Node& node){
            return node.cityCode == this->cityCode && node.airline == this->airline;
        }

        void writeFlightPathToFile(string outputPath);
        
        bool operator==(Node &node);

    private:
        void writeToFile(string outputPath, vector<string> airlinePath, vector<string> airportPath, vector<int> stops, int totalStops, int totalFlights, double totalDistance);
};
