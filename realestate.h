#ifndef REALESTATE_H
#define REALESTATE_H

#include <string>

class RealEstate
{
public:
    std::string owner;
    std::string date;
    int cost;

    RealEstate();
    RealEstate(std::string p_owner, std::string p_date, int cost);
};

#endif // REALESTATE_H
