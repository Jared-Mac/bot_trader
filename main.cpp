#include <iostream>

#include "stock/StockSimulation.h"
#include "bot/Bot.h"
//#include "analytics.h"

int main() {
	Bot* bot1 = new Bot();
	// bot1->name = "Bot 1";
	//               Bot_type, Starting Balance, Deposit period (in terms of interval), Recurring Deposit amount
	bot1->setBotType(CONSERVATIVE, 1000, 5, 100);
	Bot* bot2 = new Bot();
	bot2->setBotType(AGGRESSIVE, 1000, 5, 100);
	// bot2->name = "Bot 2";
	Bot* bot3 = new Bot();
	bot3->setBotType(PASSIVE, 1000, 5, 100);
	// bot3->name = "Bot 3";


	StockSimulation* simulation = StockSimulation::builder()
	                                .withStartDate("2021-11-01")
	                                .withEndDate("2021-11-30")
	                                .withInterval(DAILY)
	                                // Add Apple to the simulation.
	                                .withStock("AAPL")
	                                // Add Google, Tesla, and Amazon to the simulation.
	                                .withStocks({"GOOGL", "TSLA", "AMZN"})
	                                // Bot 1 will watch all stocks.
	                                .withBot(bot1)
									.withBot(bot2)
									.withBot(bot3)
	                                // Bot 2 will only watch Google stock.
	                                // .withBotSubscribedTo(bot2, {"GOOGL"})
	                                // Bot 3 will watch Google and Tesla stock.
	                                // .withBotSubscribedTo(bot3, {"GOOGL", "TSLA"})
	                                .build();

	simulation->run();
	//exportData(stringToTime("2021-11-01"),bot1);
	//displayStats(stringToTime("2021-11-01"),stringToTime("2021-11-30"), bot1);

	delete simulation;
	delete bot1;
	delete bot2;
	delete bot3;
}
