#ifndef AbstractBot_H
#define AbstractBot_H

#include <map>

#include "../stock/Stock.h"
#include "string.h"
#include "Position.h"
#include "Trade.h"


enum BotType
{
    CONSERVATIVE,
    AGGRESSIVE
};
class AbstractBot {
    private:
        virtual void trade(time_t currentDay) = 0;

    protected:
        double accountBalance;
        int daysToDeposit;
        double depositAmount;
        std::unordered_map<std::string,Position *> positions;
        std::unordered_map<time_t,std::vector<Trade *>> trades;

        void deposit(double depositAmount);
        Trade * buyStock(std::string stockSymbol,double spendingMoney);
        Trade * sellStock(std::string stockSymbol, float shares);
    public:
		std::string name;
        AbstractBot();
        ~AbstractBot();
        
        void checkForDeposit();

        std::map<double,Position *>* rankStocks(time_t currentDay);

        void notify(time_t currentDay,std::vector<StockSnapshot> snapshots);

        friend std::ostream& operator<<(std::ostream& out, const AbstractBot& AbstractBot);

        friend class Bot;

};

class ConservativeBot: public AbstractBot
{
    public:
        ConservativeBot();
        ~ConservativeBot();
    private:
        void trade(time_t currentDay);
};

class AggressiveBot: public AbstractBot
{
    public:
        AggressiveBot();
        ~AggressiveBot();
    private:
        void trade(time_t currentDay);
};
class Bot
{
    public:
        Bot()
        {
            bot_ = NULL;
        }
        ~Bot();
        void setBotType(BotType type);
        void notify(time_t currentDay,std::vector<StockSnapshot> snapshots);
        void trade(time_t currentDay);
    private:
        AbstractBot * bot_;
};


#endif
