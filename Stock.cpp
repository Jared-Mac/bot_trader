#include "Stock.h"

Stock::Stock(std::string symbol) {
	this->symbol = symbol;
}

Stock::~Stock() {}

size_t Stock::numberOfSnapshots() const {
	return this->snapshots.size();
}

std::string Stock::getSymbol()
{
	return symbol;
}
StockSnapshot Stock::getSnapshot(size_t i) const {
	std::stringstream ss;

	if (i < this->numberOfSnapshots()) {
		return this->snapshots[i];
	}

	ss << i << " is outside of the range for this Stocks loaded data!";

	throw std::invalid_argument(ss.str());
}


StockSnapshot Stock::getSnapshot(std::time_t date) const {
	std::stringstream ss;

	if (isWeekend(date)) {
		ss << "The Stock market is only opened during buisness days! " << timeToString(date) << " is on the weekend!";
		throw std::invalid_argument(ss.str());
	}

	auto snap_itr = std::find_if(this->snapshots.begin(), this->snapshots.end(), [date] (StockSnapshot s) { return s.getDate() == date; });

	if (snap_itr != this->snapshots.end()) {
		return *snap_itr;
	}

	ss << "No information for the date " << timeToString(date) << " could be found!";

	throw std::invalid_argument(ss.str());
}

StockSnapshot Stock::getSnapshot(std::string date) const {
	return this->getSnapshot(stringToTime(date));
}

void Stock::clearSnapshots() {
	this->snapshots.clear();
}

/**
 * Returns the StockSnapshots CSV string of this Stock from the start of
 * the period to the end of the period sampling at the given Interval.
 */
std::string Stock::getHistoricalCSV(const std::time_t start, const std::time_t end, const Interval interval) {
	return downloadYahooCSV(this->symbol, start, end, interval);
}



/**
 * Populates the StockSnapshots vector of this Stock from the start of
 * the period to the end of the period sampling at the given Interval.
 */
void Stock::loadHistoricalSnapshots(const std::time_t start, const std::time_t end, const Interval interval) {
	std::string csv = this->getHistoricalCSV(start, end, interval);
	std::istringstream csv_iss(csv);
	std::string line;

	// Remove the header line
	std::getline(csv_iss, line);

	std::string date;
	double open;
	double high;
	double low;
	double close;
	char comma;

	while (std::getline(csv_iss, line)) {
		std::istringstream iss(line);

		getline(iss, date, ',');

		if (date != "null") {
			// Ignores Adjusted close and volume but they are available as well.
			iss >> open >> comma >> high >> comma >> low >> comma >> close;

			StockSnapshot spot = StockSnapshot(date, open, high, low, close);
			this->snapshots.push_back(spot);
		}
	}
}

/**
 * Populates the StockSnapshot vector of this Quote from the start of
 * the period to the end of the period sampling at the given Interval.
 */
void Stock::loadHistoricalSnapshots(const std::string start, const std::string end, const Interval interval) {
	this->loadHistoricalSnapshots(stringToTime(start), stringToTime(end), interval);
}

std::ostream& operator<<(std::ostream& out, const Stock& stock) {
	for (int i = 0; i < stock.numberOfSnapshots(); i++) {
		out << stock.snapshots[i] << std::endl;
	}

	return out;
}

/**
 * Internal helper callback for downloading Yahoo CSV data.
 */
size_t Stock::writeCallback(char *content, size_t size, size_t nmemb, void *userdata) {
	// Append the content to user data
	((std::string*) userdata)->append(content, size * nmemb);

	// Return the real content size
	return size * nmemb;
}

/**
 * Internal helper downloading Yahoo CSV data.
 */
std::string Stock::downloadYahooCSV(const std::string symbol, const std::time_t start, const std::time_t end, const Interval interval) {
	std::stringstream url_ss;
	url_ss << "https://query1.finance.yahoo.com/v7/finance/download/";
	url_ss << symbol;
	url_ss << "?period1=" << start;
	url_ss << "&period2=" << end;
	url_ss << "&interval=" << interval;
	url_ss << "&events=history";

	CURL* curl = curl_easy_init();
	std::string responseBuffer;

	if (curl) {
		std::string url = url_ss.str().c_str();

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Write result into the buffer
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Stock::writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

		// Perform the request
		CURLcode res = curl_easy_perform(curl);

		// Cleanup
		curl_easy_cleanup(curl);
	}

	return responseBuffer;
}