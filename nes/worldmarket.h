#ifndef WORLDMARKET_H
#define WORLDMARKET_H

#include "economy.h"
#include <map>

enum class TradeGood
{
    Food,Wood,Oil,Ore,ConsumerGoods,CapitalGoods
};

class WorldMarket
{
public:
    WorldMarket();
    double buy_price(TradeGood,int good_amount)const;
    double sell_price(TradeGood,int good_amount)const;
    void buy(TradeGood,int good_amount);
    void sell(TradeGood,int good_amount);
private:
    double markup;
    std::map<TradeGood,double> sell_rates;
};

#endif // WORLDMARKET_H
