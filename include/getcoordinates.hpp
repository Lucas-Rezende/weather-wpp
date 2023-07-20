#ifndef GET_COORDINATES
#define GET_COORDINATES

#include <string>

class getCoordinates
{
private:
    mutable float latitude;
    mutable float longitude;
public:
    getCoordinates();
    void Coordinates(std::string local) const;
    float getLongitude();
    float getLatitude();
};

#endif