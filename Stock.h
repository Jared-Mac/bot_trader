#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <algorithm>
#include <curl/curl.h>

#include "StockSnapshot.hpp"
#include "Interval.h"


class Stock {
	private:
		std::string symbol;
		// Might be worthwhile to swap this out for an unordered_map<time_t, StockSnapshot>
		std::vector<StockSnapshot> snapshots;

		/**
		 * Internal helper callback for downloading Yahoo CSV data.
		 */
		static size_t writeCallback(char* content,
							 size_t size,
							 size_t nmemb,
							 void* userdata);

		/**
		 * Internal helper downloading Yahoo CSV data.
		 */
		static std::string downloadYahooCSV(const std::string symbol,
									 const std::time_t start,
									 const std::time_t end,
									 const Interval interval);

	public:
		
		Stock(std::string symbol);

		~Stock();

		size_t numberOfSnapshots() const;

		std::string getSymbol();

		StockSnapshot getSnapshot(size_t i) const;
		StockSnapshot getSnapshot(std::time_t date) const;
		StockSnapshot getSnapshot(std::string date) const;

		void clearSnapshots();

		/**
		* Returns the StockSnapshot CSV string of this Quote from the start of
		* the period to the end of the period sampling at the given Interval.
		*/
		std::string getHistoricalCSV(std::time_t start,
									std::time_t end,
									const Interval interval);

		
		/**
		* Populates the StockSnapshot vector of this Quote from the start of
		* the period to the end of the period sampling at the given Interval.
		*/
		void loadHistoricalSnapshots(std::time_t start,
								std::time_t end,
								const Interval interval);

		/**
		* Populates the StockSnapshot vector of this Quote from the start of
		* the period to the end of the period sampling at the given Interval.
		*/
		void loadHistoricalSnapshots(const std::string start,
								const std::string end,
								const Interval interval);

		friend std::ostream& operator<<(std::ostream& out, const Stock& stock);
};

#endif
