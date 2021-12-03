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

        double accountBalance;

        void deposit(double depositAmount);

        std::map<std::string,class Position> positions;

        virtual void trade(void) = 0;
        // void trade(void){}
        
    public:
		std::string name;
        AbstractBot();
        ~AbstractBot();
        
        // Temporarily public for testing, should be private
        void buyStock(const Stock *stock, float shares);
        void sellStock(const Stock *stock, float shares);

        void notify(StockSnapshot* snapshot);

        friend std::ostream& operator<<(std::ostream& out, const AbstractBot& AbstractBot);

        friend class Bot;

};

class ConservativeBot: public AbstractBot
{
    public:
        ConservativeBot();
        ~ConservativeBot();
    private:
        void trade(void){}
};

class AggressiveBot: public AbstractBot
{
    public:
        AggressiveBot();
        ~AggressiveBot();
    private:
        void trade(void){}
};
class Bot
{
    public:
        Bot()
        {
            bot_ = NULL;
        }
        void setBotType(BotType type);
        void notify(StockSnapshot* snapshot);
        void trade(void);
    private:
        AbstractBot * bot_;
};


#endif
