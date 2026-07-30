#include <iostream>
#include<string>
class dayTime {
private:
    int hour, minute, second;
public:
    dayTime() {}
    dayTime(int hour, int minute, int second) {
        this->hour = hour;
        this->second = second;
        this->minute = minute;
        if (hour > 24) {
            hour = hour % 24;
        }
        if (minute > 60) {
            minute = minute % 60;
            hour += minute / 60;
        }
        if (second > 60) {
            second = second % 60;
            minute += second % 60;
        }
    }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }
    int asSecond()const { return (hour * 3600 + minute * 60 + second); }
    void operator++(int) {
        second++;
        if (second > 60) {
            second = 1;
            minute++;
        }
    }
    void operator--(int) {
        minute--;
        if (minute < 0) {
            minute = 59;
            hour--;
        }
    }
};
class Dollar {
private:
    float currency, mktrate, offrate;
public:
    float getDollar() {
        return currency;
    }
    float getMarketSoums() {
        return mktrate*currency;
    }
    float getOfficialSoums() {
        return offrate*currency;
    }
    void setRates(float mktrate, float offrate) {
        this->mktrate = mktrate;
        this->offrate = offrate; 
    }
    void operator<<(float currency) {
        this->currency = currency;
    }
};
int main() {
    //first program
    bool isRun = true;
    dayTime dt(12, 12, 12);
    int intTemp;
    std::string strTemp;
    std::cout << "Enter \n1 To Display Time \n2 To Display Time in Seconds \n3 To Increment Seconds \n4 To decrements minutes \n0 To exit \n";
    while (true) {
        std::cin >> intTemp;
        switch (intTemp) {
        case 1:
            std::cout << "hour: " << dt.getHour() << " minute: " << dt.getMinute() << " second: " << dt.getSecond() << std::endl;
            break;
        case 2:
            std::cout << "Time in second: " << dt.asSecond() << std::endl;
            break;
        case 3:
            dt++;
            std::cout << "Seconds were incremented \n";
            break;
        case 4:
            dt--;
            std::cout << "Minutes were decremented \n";
            break;
        case 0:
            isRun = false;
            break;
        default:
            std::cout << "Please pick the number from 1 to 4 \n";
        }
        if (isRun == false) {
            break;
        }
    }
    //second program
    Dollar dl;
    float flTemp1, flTemp2;
    std::cout << "Enter the market rate \n";
    std::cin >> flTemp1;
    std::cout << "Enter the offmarket rate \n";
    std::cin >> flTemp2;
    dl.setRates(flTemp1, flTemp2);
    std::cout << "Enter the amount of money in dollars \n";
    std::cin >> flTemp1;
    dl << flTemp1;
    std::cout << "The amount of dollars: " << dl.getDollar() << std::endl;
    std::cout << "The amount of soums in market rate: " << dl.getMarketSoums() << std::endl;
    std::cout << "The amount of soums in official rate: " << dl.getOfficialSoums() << std::endl;
    system("pause");
    return 0;
}