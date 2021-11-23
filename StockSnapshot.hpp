#ifndef STOCK_SNAPSHOT_HPP
#define STOCK_SNAPSHOT_HPP

#include <iomanip>
#include <string>
#include <ctime>

#include "time_utils.h"

class StockSnapshot {
	private:
		std::time_t date;
		double open;
		double high;
		double low;
		double close;

	public:
		StockSnapshot(std::time_t date, double open, double high, double low, double close)  {
			this->date = date;
			this->open = open;
			this->high = high;
			this->low = low;
			this->close = close;
		}

		StockSnapshot(std::string date, double open, double high, double low, double close) : StockSnapshot(stringToTime(date), open, high, low, close) {}
		StockSnapshot(std::time_t date, double price) : StockSnapshot(date, price, price, price, price) {}
		StockSnapshot(std::string date, double price) : StockSnapshot(stringToTime(date), price, price, price, price) {}

		~StockSnapshot() {}

		inline std::time_t getDate() const {
			return this->date;
		}

		inline std::string getDateString() const {
			return timeToString(this->date);
		}

		inline double getOpening() const {
			return this->open;
		}

		inline double getHigh() const {
			return this->high;
		}

		inline double getLow() const {
			return this->low;
		}

		inline double getClosing() const {
			return this->close;
		}

		std::string toString() const {
			std::ostringstream oss;
			oss << "Date: " << this->getDateString() << " ";
			oss << "Open: " << this->getOpening() << " ";
			oss << "High: " << this->getHigh() << " ";
			oss << "Low: " << this->getLow() << " ";
			oss << "Close: " << this->getClosing();

			return oss.str();
		}

		friend std::ostream& operator<<(std::ostream& out, const StockSnapshot& snapshot) {
			return out << snapshot.toString();
		}
};

#endif
