#include "Bot.h"
#include "time_utils.h"
#include <iostream>
using namespace std;

Bot::Bot(){
    this->accountBalance = 10000;
}

Bot::~Bot(){}

void Bot::buyStock(Stock &stock, float shares)
{
    
    Position newPos;
    
    
    string stockSymbol = stock.getSymbol();

    double price = stock.getSnapshot(this->date).getLow();

    if (this->positions.find(stockSymbol) == positions.end())
    {
        
        this->positions.insert({stockSymbol, newPos});
    }
    
    this->positions[stockSymbol].addShares(shares);
    this->positions[stockSymbol].setAvgcost(price);
    this->accountBalance -= shares*price;

    cout << "[BUY] " << "Stock: " << stockSymbol << " Shares " << shares <<
        " Price per share: " << price << endl;

}


void Bot::sellStock(Stock &stock, float shares)
{
    Position newPos;
    string stockSymbol = stock.getSymbol();

    double price = stock.getSnapshot(this->date).getLow();

    if (this->positions.find(stockSymbol) == positions.end())
    {
        this->positions.insert({stockSymbol, newPos});
    }

    this->positions[stockSymbol].subShares(shares);
    this->accountBalance += shares*price;

    cout << "[SELL] " << "Stock: " << stockSymbol << " Shares " << shares <<
        " Price per share: " << price << endl;
}


std::ostream& operator<<(std::ostream& out, const Bot& bot) {
    cout << "Bot's account balance : " << bot.accountBalance << endl;
    cout << "Bot's positions" << endl;
	for(auto it=bot.positions.cbegin(); it!= bot.positions.cend(); ++it)
    {
        cout << it->first << '\t' << (it->second) << '\n';
    }

	return out;
}

