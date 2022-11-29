# Program Structure
The program contains three primary classes:

1.  The AirPort Class that models an airport.
2.  The Node Class that models a state at any given point in time along the path.
3.  The FlightRoute Class which load the data, and contains all the logic of the program.

The main method of the programm is found in the main.cpp file.

## How to run the program

To run the program, open an empty text file and write two lines in it, the lines should be in the form below: 

Accra, Ghana
London, United Kingdom

or 

city, country
city, country

The first line of the file represent the start city and country and the second line represents the destination city and country. Ensure that the city and country are seperated by a comma.

Move into the main file and call the findOptimalPath method defined in the FlightRoute class. This method accepts as argument the name of the file containing you start and destination location. **Do not include the file extension when possing the file name to this function"

## How to run the program

Move to the terminal and type the following command:

1.  g++ main.cpp utility.cpp Node.cpp FlightRoute.cpp -o main
2. ./main

The program will take a few second to load the various dataset in memory.

Once the program is done running, it will create an output file with the shortest flight path between the start and destination city. It will also show the distance between these two citys through the given path.