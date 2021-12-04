#ifndef AbstractBot_H
#define AbstractBot_H

#include "../stock/Stock.h"
#include "string.h"
#include "Position.h"

#include <map>

enum BotType
{
    CONSERVATIVE,
    AGGRESSIVE
};
class AbstractBot {
    private:
        virtual void trade(void) = 0;
    protected:
        double accountBalance;
        std::map<std::string,class Position> positions;
        void deposit(double depositAmount);
        void buyStock(std::string stockSymbol,double spendingMoney);
        void sellStock(const Stock *stock, float shares);
    public:
		std::string name;
        AbstractBot();
        ~AbstractBot();
        
        void rankStocks();

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
        void trade(void);
};

class AggressiveBot: public AbstractBot
{
    public:
        AggressiveBot();
        ~AggressiveBot();
    private:
        void trade(void);
};
class Bot
{
    public:
        Bot()
        {
            bot_ = NULL;
        }
        void setBotType(BotType type);
        void notify(time_t currentDay,std::vector<StockSnapshot> snapshots);
        void trade(void);
    private:
        AbstractBot * bot_;
};


#endif
