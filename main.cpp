#include "FlightRoute.h"

int main()
{
    FlightRoute flight = FlightRoute("airports.csv", "routes.csv");
    flight.findOptimalFlightPath("accra_winnipeg"); 
    return 1;
}
