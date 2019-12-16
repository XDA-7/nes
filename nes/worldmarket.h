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
    double BuyPrice(TradeGood,int good_amount)const;
    double SellPrice(TradeGood,int good_amount)const;
    void Buy(TradeGood,int good_amount);
    void Sell(TradeGood,int good_amount);
private:
    double markup;
    std::map<TradeGood,double> sell_rates;
};

#endif // WORLDMARKET_H
