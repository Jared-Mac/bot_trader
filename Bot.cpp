#include "Bot.h"
#include <iostream>
using namespace std;

Bot::Bot(){
    this->accountBalance = 100;
}

Bot::~Bot(){}

void Bot::buyStock(Stock stock, float shares)
{
    this->positions.insert({stock.getSymbol(), shares});
    this->accountBalance -= shares*5;

}


void Bot::sellStock(Stock stock, float shares)
{
    this->positions[stock.getSymbol()] -= shares;
    this->accountBalance += shares*5;
}


std::ostream& operator<<(std::ostream& out, const Bot& bot) {
	for(auto it=bot.positions.cbegin(); it!= bot.positions.cend(); ++it)
    {
        cout << it->first << '\t' << it->second << '\n';
    }

	return out;
}

