#ifndef BOT_H
#define BOT_H

#include "Stock.h"
#include "string.h"
#include <map>


class Bot {
    private:

        float accountBalance;

        std::map<std::string,float> positions;





    public:
        Bot();
        ~Bot();

        friend std::ostream& operator<<(std::ostream& out, const Bot& bot);

        void buyStock(Stock stock, float shares);
        void sellStock(Stock stock, float shares);


};



#endif
