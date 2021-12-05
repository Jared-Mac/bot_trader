#include "Bot.h"
#include "../temporal/TemporalUtils.h"
#include <iostream>
using namespace std;


AbstractBot::AbstractBot(){
    this->accountBalance = 10000;
    int daysToDeposit = 5;
    double depositAmount = 100;
}

AbstractBot::~AbstractBot(){
    for(auto pair: this->positions)
    {
        delete pair.second;
    }
}
AbstractBot::AbstractBot(double startingBalance, int daysToDeposit, double depositAmount)
{
    this->accountBalance = startingBalance;
    this->daysToDeposit = daysToDeposit;
    this->depositAmount = depositAmount;
}
void AbstractBot::deposit(double depositAmount)
{
    this->accountBalance += this->depositAmount;
}
void AbstractBot::checkForDeposit(){
    if (this->daysToDeposit == 0)
        deposit(this->depositAmount);
    else
        this->daysToDeposit--;
}
Trade * AbstractBot::buyStock(std::string stockSymbol, double spendingMoney)
{
    
    double price = this->positions[stockSymbol]->getCurrentPrice();

    float shares = spendingMoney / price;

    this->positions[stockSymbol]->setAvgcost(price,shares);
    this->positions[stockSymbol]->addShares(shares);

    this->accountBalance -= shares*price;
    if (this->accountBalance < 0.009) this->accountBalance = 0;
    

    return new Trade(BUY, shares, price, stockSymbol);

}


Trade * AbstractBot::sellStock(std::string stockSymbol, float shares)
{
    // If requesting to sell more shares than bot owns, sell all shares 
    if(shares > this->positions[stockSymbol]->getShares())
        shares = this->positions[stockSymbol]->getShares();

    double price = this->positions[stockSymbol]->getCurrentPrice();
    this->positions[stockSymbol]->subShares(shares);
    if (this->positions[stockSymbol]->getShares() == 0) this->positions[stockSymbol]->avg_cost = 0;
    this->accountBalance += shares*price;

    return new Trade(SELL, shares, price, stockSymbol);
}


void AbstractBot::notify(time_t currentDay,std::vector<StockSnapshot> snapshots)
{
    this->checkForDeposit();
    std::cout << "Account Balance: " << this->accountBalance << std::endl;
    for (auto snapshot: snapshots)
    {
        if(this->positions.find(snapshot.getSymbol()) == this->positions.end())
        {
            Position * pos = new Position();
            this->positions.insert({snapshot.getSymbol(), pos});

        }
        try{
            this->positions[snapshot.getSymbol()]->snapshots.push_back(snapshot);
        }
        catch(exception e)
        {
            cout << e.what() << endl;
        }
    }
    for(auto pos: this->positions)
    {
        cout << *(pos.second )<< endl;
    }
}

std::map<double,Position *>* AbstractBot::rankStocks(time_t currentDay)
{
    map<double, Position *>* ranked = new map<double, Position *>;
    
    for(auto position_pair: this->positions)
    {

        double change = 0;

        if ( position_pair.second->snapshots.size() > 1)
        {
            auto itr =  position_pair.second->snapshots.rbegin();
            double currentPrice = itr->getLow();
            itr++;
            double lastPrice = itr->getLow();
            change = currentPrice - lastPrice;
        }
    
        ranked->insert({change, position_pair.second});
    }
    return ranked;

}
ConservativeBot::ConservativeBot(){
    
}

ConservativeBot::ConservativeBot(double startingBalance, int daysToDeposit, double depositAmount): AbstractBot(startingBalance, daysToDeposit, depositAmount)
{}
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
        cout << *trade << endl;
    }
}

AggressiveBot::AggressiveBot(){
    
}
AggressiveBot::~AggressiveBot(){
    
}
AggressiveBot::AggressiveBot(double startingBalance, int daysToDeposit, double depositAmount): AbstractBot(startingBalance, daysToDeposit, depositAmount)
{}

PassiveBot::PassiveBot(){}
PassiveBot::PassiveBot(double startingBalance, int daysToDeposit, double depositAmount) : AbstractBot(startingBalance, daysToDeposit, depositAmount)
{}
PassiveBot::~PassiveBot(){}

Bot::~Bot()
{
    delete bot_;
}
void AggressiveBot::trade(time_t currentDay)
{
    
    std::cout << "Aggressively Trading" << std::endl;
    
    std::map<double,Position *> ranks;
    ranks = *(this->rankStocks(currentDay));

    auto itr = ranks.begin();
    auto ritr = ranks.rbegin();

    
    
    if (ritr->first > 0 && ritr->second->getShares() > 0) 
         this->trades[currentDay].push_back((this->sellStock(ritr->second->snapshots.back().getSymbol(),ritr->second->getShares())));
    if (accountBalance == 0) return;
    if (itr->first < 0)  
        this->trades[currentDay].push_back((this->buyStock(itr->second->snapshots.back().getSymbol(),this->accountBalance)));

    for(auto trade: this->trades[currentDay])
    {
        cout << *trade << endl;
    }

}

void PassiveBot::trade(time_t currentDay)
{
    std::cout << "Passive bot does not trade " << std::endl;
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
        case PASSIVE:
            bot_ = (AbstractBot *) new PassiveBot();
        default:
            bot_ = (AbstractBot *) new ConservativeBot();
    }
    
}
void Bot::setBotType(BotType type,double startingBalance, int daysToDeposit, double depositAmount)
{
    delete bot_;
    switch(type)
    {
        case CONSERVATIVE:
            bot_ = (AbstractBot *) new ConservativeBot(startingBalance, daysToDeposit, depositAmount);
            break;
        case AGGRESSIVE:
            bot_ = (AbstractBot *) new AggressiveBot(startingBalance, daysToDeposit, depositAmount);
            break;
        case PASSIVE:
            bot_ = (AbstractBot *) new PassiveBot(startingBalance, daysToDeposit, depositAmount);
        default:
            bot_ = (AbstractBot *) new ConservativeBot(startingBalance, daysToDeposit, depositAmount);
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
        cout << pair.first << '\t' << *(pair.second) << endl;
        value += pair.second->getShares() * pair.second->getCurrentPrice();
    }
    cout << "Portfolio Value: " << value << endl;
    cout << "Total Value: " << value + AbstractBot.accountBalance << endl;

	return out;
}
