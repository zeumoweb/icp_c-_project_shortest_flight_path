
#include <string>

using std::string;

/**
 * Models an airport and all the basic information that can be associated
 * to it.
 * 
 * @author Styve Lekane.
 */
class AirPort {

    private:

        /*
        * Two countries can have the same city name, hence the city code is the city
        * unique identifier.
        * It is in the form "City, Country". E.g Accra, Ghana
        */
        string cityCode;
        string country;
        string city;
        string code;
        string id;
        double latitude;
        double longitude;
        double altitude;
        string airline;
        int stops = 0;

    public:

        // Static Variables
        static const int ID_INDEX = 0;
        static const int NAME_INDEX = 1;
        static const int CITY_INDEX = 2;
        static const int COUNTRY_INDEX = 3;
        static const int CODE_INDEX = 4; // IATA CODE
        static const int LATITUDE_INDEX = 6;
        static const int LONGITUDE_INDEX = 7;
        static const int ALTITUDE_INDEX = 8;
        
        AirPort(string country, string city, string code, string id, double latitude, double longitude,
                double altitude, string cityCode) {
            this->city = city;
            this->country = country;
            this->code = code;
            this->id = id;
            this->latitude = latitude;
            this->longitude = longitude;
            this->altitude = altitude;
            this->cityCode = cityCode;
        } 

        // copy constructor.
        AirPort(const AirPort& airport) {
            this->city = airport.getCity();
            this->country = airport.getCountry();
            this->code = airport.getCode();
            this->id = airport.getId();
            this->latitude = airport.getLatitude();
            this->longitude = airport.getLongitude();
            this->altitude = airport.getAltitude();
            this->cityCode = airport.getCityCode();
        }

        string getCountry() const{
            return this->country;
        }

        string getCity() const {
            return this->city;
        }

        string getId() const {
            return this->id;
        }

        string getCode() const {
            return this->code;
        }

        double getLatitude() const {
            return this->latitude;
        }

        double getLongitude() const {
            return this->longitude;
        }

        double getAltitude() const {
            return this->altitude;
        }

        string getCityCode() const {
            return this->cityCode;
        }

        string getAirLine() const {
            return this->airline;
        }

        int getStops() const {
            return this->stops;
        }

        void setAirLineCode(string airlineCode) {
            this->airline = airlineCode;
        }

        void setStops(int stops) {
            this->stops = stops;
        }
};
