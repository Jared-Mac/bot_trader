#include <iostream>

#include "Stock.h"
#include "Bot.h"

using namespace std;

int main() {
	// S&P 500
	Stock snp500("^GSPC");

	snp500.loadHistoricalSnapshots("2020-10-01", "2020-10-07", DAILY);
	snp500.loadHistoricalSnapshots("2021-10-01", "2021-10-07", DAILY);

	std::cout << "S&P 500 data from 10-01 to 10-07 in 2020 and 2021:" << std::endl;
	// std::cout << snp500 << std::endl;
	// Tesla
	Stock tesla("tsla");

	tesla.loadHistoricalSnapshots("2020-10-01", "2020-10-07", DAILY);
	tesla.loadHistoricalSnapshots("2021-10-01", "2021-10-07", DAILY);

	std::cout << "Tesla data from 10-01 to 10-07 in 2020 and 2021:" << std::endl;
	// std::cout << tesla << std::endl;



	Bot* mybot = new Bot;




	float numShares = 5;
	try
	{
		mybot->buyStock(snp500,numShares);
		mybot->buyStock(tesla,numShares*2);
		cout << *mybot << endl;
		mybot->sellStock(tesla,numShares);
		cout << *mybot << endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	


	// try {
	// 	StockSnapshot snap = snp500.getSnapshot("2021-10-05");
	// 	std::cout << "Snapshot at 2021-10-05:" << std::endl;
	// 	std::cout << snap << std::endl;
	// } catch(const std::exception &e) {
	// 	std::cerr << e.what() << std::endl;
	// }

	// try {
	// 	// Try to access during the weekend/holiday or outside of the range.
	// 	StockSnapshot snap = snp500.getSnapshot("2021-10-02");
	// 	std::cout << "Snapshot at 2021-10-02:" << std::endl;
	// 	std::cout << snap << std::endl;
	// } catch(const std::exception &e) {
	// 	std::cout << "Snapshot at 2021-10-02:" << std::endl;
	// 	std::cerr << e.what() << std::endl;
	// }





	// Ugly testing to ensure the time utilities are working as expected.
	// time_t base = stringToTime("2021-10-01");
	// std::cout << std::endl << "Time iteration test:" << std::endl;
	// std::cout << "Starting day is: " << timeToString(base) << std::endl;
	// std::cout << "Next day is: " << timeToString(nextDay(base)) << std::endl;
	// std::cout << "Next monday is: " << timeToString(nextWeek(base)) << std::endl;
	// std::cout << "Monday after next is: " << timeToString(nextWeek(nextWeek(base))) << std::endl;
	// std::cout << "First day of the next month is: " << timeToString(nextMonth(base)) << std::endl;
	// std::cout << "First day of the month after next is: " << timeToString(nextMonth(nextMonth(base))) << std::endl;

	// std::cout << std::endl;
	// std::cout << "Starting day is: " << timeToString(base) << std::endl;
	// std::cout << "Previous day is: " << timeToString(previousDay(base)) << std::endl;
	// std::cout << "Previous monday is: " << timeToString(previousWeek(base)) << std::endl;
	// std::cout << "Monday before the previous is: " << timeToString(previousWeek(previousWeek(base))) << std::endl;
	// std::cout << "Previous first of the month is: " << timeToString(previousMonth(base)) << std::endl;
	// std::cout << "First day of the month before previous is: " << timeToString(previousMonth(previousMonth(base))) << std::endl;

	// std::cout << std::boolalpha << std::endl;
	// std::cout << timeToString(base) << ", a Friday, is a weekday: " << isWeekday(base) << std::endl;
	// std::cout << timeToString(base) << ", a Friday, is during the weekend: " << isWeekend(base) << std::endl;
	// std::cout << timeToString(nextDay(base)) << ", a Saturday, is a weekday: " << isWeekday(nextDay(base)) << std::endl;
	// std::cout << timeToString(nextDay(base)) << ", a Saturday, is during the weekend: " << isWeekend(nextDay(base)) << std::endl;
	// std::cout << timeToString(nextDay(nextDay(base))) << ", a Sunday, is during the weekend: " << isWeekend(nextDay(nextDay(base))) << std::endl;
	// std::cout << timeToString(nextDay(nextDay(nextDay(base)))) << ", a Monday, is a weekday: " << isWeekday(nextDay(nextDay(nextDay(base)))) << std::endl;
}