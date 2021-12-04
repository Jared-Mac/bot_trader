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
Trade AbstractBot::buyStock(std::string stockSymbol, double spendingMoney)
{
    
    double price = this->positions[stockSymbol].getCurrentPrice();

    float shares = spendingMoney / price;

    this->positions[stockSymbol].setAvgcost(price,shares);
    this->positions[stockSymbol].addShares(shares);

    this->accountBalance -= shares*price;
    if (this->accountBalance < 0.009) this->accountBalance = 0;
    

    // cout << "[BUY] " << "Stock: " << stockSymbol << " Shares " << shares <<
    //     " Price per share: " << price << endl;

    return Trade(BUY, shares, price, stockSymbol);

}


Trade AbstractBot::sellStock(std::string stockSymbol, float shares)
{

    // If requesting to sell more shares than bot owns, sell all shares 
    if(shares > this->positions[stockSymbol].getShares())
        shares = this->positions[stockSymbol].getShares();

    double price = this->positions[stockSymbol].getCurrentPrice();
    this->positions[stockSymbol].subShares(shares);
    this->accountBalance += shares*price;

    // cout << "[SELL] " << "Stock: " << stockSymbol << " Shares " << shares <<
    //     " Price per share: " << price << endl;

    return Trade(SELL, shares, price, stockSymbol);
}


void AbstractBot::notify(time_t currentDay,std::vector<StockSnapshot> snapshots)
{
    std::cout << "Account Balance: " << this->accountBalance << std::endl;
    for (auto snapshot: snapshots)
    {
        if(this->positions.find(snapshot.getSymbol()) == this->positions.end())
        {
            Position pos;
            this->positions.insert({snapshot.getSymbol(), pos});
            cout << "New Position added" << endl;
        }
        else
            cout << "Old position found, size = " << positions[snapshot.getSymbol()].snapshots.size() << endl;
        try{
            this->positions[snapshot.getSymbol()].snapshots.push_back(snapshot);
            cout << "Latest snapshot added: " << this->positions[snapshot.getSymbol()].snapshots.back() << endl;
            cout << "New size = " << positions[snapshot.getSymbol()].snapshots.size() << endl;
        }
        catch(exception e)
        {
            cout << e.what() << endl;
        }
    }
    for(auto pos: this->positions)
    {
        cout << pos.second << endl;
    }
}

ConservativeBot::ConservativeBot(){
    
}
ConservativeBot::~ConservativeBot(){
    
}
void ConservativeBot::trade(time_t currentDay)
{
    std::cout << "Conservatively Trading" << std::endl;
    double spendingMoney = this->accountBalance / this->positions.size();

    for(auto position: this->positions)
    {
        if( this->accountBalance > 0.009) 
        this->trades[currentDay].push_back((this->buyStock(position.first, spendingMoney)));

    }
    for(auto trade: this->trades[currentDay])
    {
        cout << trade << endl;
    }
}

AggressiveBot::AggressiveBot(){
    
}
AggressiveBot::~AggressiveBot(){
    
}

void AggressiveBot::trade(time_t currentDay)
{
    std::cout << "Aggressively Trading" << std::endl;
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

void Bot::notify(time_t currentDay,std::vector<StockSnapshot> snapshots)
{
    this->bot_->notify(currentDay,snapshots);
    this->trade(currentDay);
    std::cout<< *bot_ << std::endl;
}
void Bot::trade(time_t currentDay)
{
    this->bot_->trade(currentDay);
}

std::ostream& operator<<(std::ostream& out, const AbstractBot& AbstractBot) {
    cout << "Bot'account balance : " << AbstractBot.accountBalance << endl;
    cout << "Bot's positions" << endl;
    double value = 0;

    for(auto pair : AbstractBot.positions)
    {   
        cout << pair.first << '\t' << pair.second << endl;
        // cout << "Current value: " <<  pair.second.getCurrentPrice() << endl;
        // value += pair.second.getShares() * pair.second.getCurrentPrice();
    }
    // cout << "Portfolio Value: " << value << endl;
	// for(auto it=AbstractBot.positions.cbegin(); it!= AbstractBot.positions.cend(); ++it)
    // {
    //     cout << it->first << '\t' << (it->second) << endl;
    //     v
    // }

	return out;
}
