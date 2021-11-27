#include "Position.h"

#include <iostream>

Position::Position(/* args */)
{
    this->avg_cost = 0;
    this->shares = 0;
    
}

Position::~Position()
{
}

Position::Position(const Position &source)
{
    this->shares = source.shares;
    this->avg_cost = source.avg_cost;
}

void Position::addShares(float shares)
{
    this->shares += shares;
}
void Position::subShares(float shares)
{
    this->shares -= shares;
}
void Position::setAvgcost(double price)
{
    this->avg_cost = price;
}
std::ostream& operator<<(std::ostream& out, const Position& position)
{
    
    std::cout << "Shares: " << position.shares << " at average cost " << position.avg_cost << std::endl;
    return out;
}