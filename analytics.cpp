#include "analytics.h"
void displayStats(time_t start, time_t end, AbstractBot* bot){

    std::unordered_map<time_t,std::vector<Trade *>> trades = bot->getTrades();
    std::vector<double> portfolioValue;


    std::string sStart=timeToString(start),
                sEnd=timeToString(end);
    std::vector<std::string> timeData;
    std::vector<double> values;
    std::vector<double> values2;
    std::vector<std::pair<std::string,double>> data;
    //Generate X-axis for time
    TemporalIterator iter(start,end,DAILY);
    while(iter.hasNext())
    {
        timeData.push_back(timeToString(iter.next()));
    }

    // //Collect stock data
    // for(int i = 0; i < timeData.size();i++)
    // {
    //     values.push_back(i * 400);
    // }
    // //Collect stock data
    // for(int i = 0; i < timeData.size();i++)
    // {
    //     values2.push_back(2*i * 100);
    // }
    for( const auto& n: trades){//iterate thru trade vectors
        double sum = 0;
        //const std::vector<Trade> t = n.second;
        for(int i = 0;i < n.second.size();i++ ){//each trade
            Trade *temp =  n.second[i];
            if(temp->type == BUY){
                sum += temp->shares * temp->sharePrice;
            }
        }
        portfolioValue.push_back(sum);
    }


    for(int i =0; i < timeData.size(); i++)
    {
        std::string time = timeData[i];
        double y = portfolioValue[i];
        data.push_back(std::make_pair(time,y));
    }

    Gnuplot gp;
    gp << "set xdata time\n";
    gp << "set timefmt '%Y-%m-%d'\n";
    gp << "set xrange ['" << sStart <<"':'" << sEnd<< "']\n";
    gp << "set timefmt '%Y-%m-%d'\n";
    gp << "plot '-'  using 1:2 with points title 'test'\n";
    gp.send1d(data);



}
