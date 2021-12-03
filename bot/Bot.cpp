#include "Bot.h"
#include "../temporal/TemporalUtils.h"
#include <iostream>
using namespace std;


AbstractBot::AbstractBot(){
    this->accountBalance = 10000;
}

AbstractBot::~AbstractBot(){}

void AbstractBot::deposit(double depositAmount)
{
    this->accountBalance += depositAmount;
}
void AbstractBot::buyStock(const Stock *stock, float shares)
{
    
      
    string stockSymbol = stock->getSymbol();

    double price = this->positions[stockSymbol].getCurrentPrice();

    
    this->positions[stockSymbol].addShares(shares);
    this->positions[stockSymbol].setAvgcost(price);
    this->accountBalance -= shares*price;

    cout << "[BUY] " << "Stock: " << stockSymbol << " Shares " << shares <<
        " Price per share: " << price << endl;

}


void AbstractBot::sellStock(const Stock *stock, float shares)
{
    string stockSymbol = stock->getSymbol();

    double price = this->positions[stockSymbol].getCurrentPrice();

    this->positions[stockSymbol].subShares(shares);
    this->accountBalance += shares*price;

    cout << "[SELL] " << "Stock: " << stockSymbol << " Shares " << shares <<
        " Price per share: " << price << endl;
}


void AbstractBot::notify(StockSnapshot* snapshot)
{
    this->positions[snapshot->getSymbol()].snapshots.push_back(snapshot);
}

std::ostream& operator<<(std::ostream& out, const AbstractBot& AbstractBot) {
    cout << "AbstractBot's account balance : " << AbstractBot.accountBalance << endl;
    cout << "AbstractBot's positions" << endl;
	for(auto it=AbstractBot.positions.cbegin(); it!= AbstractBot.positions.cend(); ++it)
    {
        cout << it->first << '\t' << (it->second) << '\n';
    }

	return out;
}


ConservativeBot::ConservativeBot(){
    
}
ConservativeBot::~ConservativeBot(){
    
}
AggressiveBot::AggressiveBot(){
    
}
AggressiveBot::~AggressiveBot(){
    
}

void Bot::setBotType(BotType type)
{
    delete bot_;
    switch(type)
    {
        case CONSERVATIVE:
            bot_ = (AbstractBot *) new ConservativeBot();
            break;
        case AGGRESSIVE:
            bot_ = (AbstractBot *) new AggressiveBot();
            break;
        default:
            bot_ = (AbstractBot *) new ConservativeBot();
    }
    
}
void Bot::notify(StockSnapshot* snapshot)
{
    this->bot_->notify(snapshot);
}
void Bot::trade(void)
{
    this->bot_->trade();
}