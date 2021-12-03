#include <iostream>
#include "../stock/StockSnapshot.hpp"
#include <vector>
#include <map>
class Position
{
private:
    double avg_cost;
    float shares;
    std::vector<StockSnapshot *> snapshots;
public:
    Position(/* args */);
    Position(const Position &source);
    ~Position();

    Position& operator=(const Position&source);

    double getCurrentPrice(void);

    void addShares(float shares);
    void subShares(float shares);
    void setAvgcost(double price);
    float getShares()
    {
        return this->shares;
    }

    float getAvgCost()
    {
        return this->avg_cost;
    }
    friend std::ostream& operator<<(std::ostream& out,  const Position& position);

    friend class AbstractBot;
};

