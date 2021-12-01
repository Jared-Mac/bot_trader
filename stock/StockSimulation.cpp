#include "StockSimulation.h"

StockSimulation::StockSimulation(std::unordered_map<Stock*, std::vector<Bot*>> stocks, std::time_t start, std::time_t end, Interval interval) {
	this->stocks = stocks;
	this->start = start;
	this->end = end;
	this->interval = interval;
}

StockSimulation::~StockSimulation() {
	for (auto stock_pair : this->stocks) {
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
	for (auto stock_pair : stocks) {
		YahooFinanceAPI::getInstance()->populateHistoricalStockData(*stock_pair.first, start, end, interval);
	}

	TemporalIterator itr(start, end, interval);

	while (itr.hasNext()) {
		time_t current = itr.next();
		for (auto stock_pair : stocks) {
			try {
				StockSnapshot snapshot = stock_pair.first->getSnapshot(current);

				for (auto bot : stock_pair.second) {
					// bot->notify(snapshot);
				}
			} catch (std::out_of_range e) {
				// Do nothing, the date was probably just a holiday or weekend.
			}
		}
	}
}