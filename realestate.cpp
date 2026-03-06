#include <string>
#include "realestate.h"

RealEstate::RealEstate()
{
    owner = "Vasya Pupkin";
    date = "2020.02.02";
    cost = 1000000;
}

RealEstate::RealEstate(std::string p_owner, std::string p_date, int p_cost)
{
    owner = p_owner;
    date = p_date;
    cost = p_cost;
}
