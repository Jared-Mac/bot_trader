#ifndef BOT_H
#define BOT_H

#include "Stock.h"
#include "string.h"
#include "Position.h"

#include <map>


class Bot {
    private:

        float accountBalance;

        std::map<std::string,class Position> positions;

    public:
        Bot();
        ~Bot();

        std::string date = "2021-10-05";
        
        // Temporarily public for testing, should be private
        void buyStock(Stock &stock, float shares);
        void sellStock(Stock &stock, float shares);

        friend std::ostream& operator<<(std::ostream& out, const Bot& bot);

};



#endif
