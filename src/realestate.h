#ifndef REALESTATE_H
#define REALESTATE_H

#include <string>

class RealEstate
{
public:
    std::string owner;
    std::string date;
    std::string colour;
    int cost;

    RealEstate();
    RealEstate(std::string p_owner, std::string p_date, std::string p_colour, int p_cost);
};

#endif // REALESTATE_H
