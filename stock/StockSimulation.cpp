#include "StockSimulation.h"

StockSimulation::StockSimulation(std::unordered_map<Stock*, std::vector<Bot*>> stock_mapping, std::unordered_map<Bot*, std::vector<Stock*>> bot_mapping, std::time_t start, std::time_t end, Interval interval) {
	this->stock_mapping = stock_mapping;
	this->bot_mapping = bot_mapping;
	this->start = start;
	this->end = end;
	this->interval = interval;
}

StockSimulation::~StockSimulation() {
	// Delete all Stock objects we created but leave the bots.
	for (auto stock_pair : this->stock_mapping) {
		delete stock_pair.first;
	}
}

StockSimulationBuilder StockSimulation::builder() {
	return StockSimulationBuilder();
}

/**
 * Executes the stock simulation.
 */
void StockSimulation::run() {
	for (auto stock_pair : this->stock_mapping) {
		YahooFinanceAPI::getInstance()->populateHistoricalStockData(*stock_pair.first, start, end, interval);
	}

	TemporalIterator itr(start, end, interval);

    while (itr.hasNext()) {
        time_t current_day = itr.next();

		if (isWeekend(current_day)) {
			// Try to avoid unnecessary looping when no Stock data is available.
			// Might still happen for undetectable holidays.
			continue;
		}

		for (auto bot_pair : this->bot_mapping) {
			std::vector<StockSnapshot> daily_snapshots;

			for (auto stock : bot_pair.second) {
				try {
					daily_snapshots.push_back(stock->getSnapshot(current_day));
				} catch (std::out_of_range e) {
					// Do nothing, the date was probably just a holiday or weekend.
				}
			}

			if (daily_snapshots.empty()) {
				// If no stock data was found for this bot, don't notify.
				// Move on to the next bot.
				continue;
			}

			// bot_pair.first->notify(current_day, daily_snapshots);
        }
    }
}