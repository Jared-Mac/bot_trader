#include <iostream>

#include "stock/StockSimulation.h"
#include "bot/Bot.h"

int main() {
	Bot* bot1 = new Bot();
	bot1->name = "Bot 1";
	Bot* bot2 = new Bot();
	bot2->name = "Bot 2";
	Bot* bot3 = new Bot();
	bot3->name = "Bot 3";

	StockSimulation* simulation = StockSimulation::builder()
	                                .withStartDate("2021-10-01")
	                                .withEndDate("2021-10-07")
	                                .withInterval(DAILY)
	                                // Add Apple to the simulation.
	                                .withStock("AAPL")
	                                // Add Google, Tesla, and Amazon to the simulation.
	                                .withStocks({"GOOGL", "TSLA", "AMZN"})
	                                // Bot 1 will watch all stocks.
	                                .withBot(bot1)
	                                // Bot 2 will only watch Google stock.
	                                .withBotSubscribedTo(bot2, {"GOOGL"})
	                                // Bot 3 will watch Google and Tesla stock.
	                                .withBotSubscribedTo(bot3, {"GOOGL", "TSLA"})
	                                .build();

	simulation->run();

	delete simulation;
	delete bot1;
	delete bot2;
	delete bot3;
} 