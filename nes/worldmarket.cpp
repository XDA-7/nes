#include "worldmarket.h"

WorldMarket::WorldMarket()
    : markup{0.2}
{
    sell_rates[TradeGood::Food] = 1.0;
    sell_rates[TradeGood::Oil] = 1.5;
    sell_rates[TradeGood::Ore] = 1.0;
    sell_rates[TradeGood::Wood] = 1.0;
    sell_rates[TradeGood::ConsumerGoods] = 3.0;
    sell_rates[TradeGood::CapitalGoods] = 3.0;
}

double WorldMarket::buy_price(TradeGood good,int good_amount)const
{
    return sell_rates.at(good) * markup * good_amount;
}
double WorldMarket::sell_price(TradeGood good,int good_amount)const
{
    return sell_rates.at(good) * good_amount;
}
void WorldMarket::buy(TradeGood good,int good_amount)
{}
void WorldMarket::sell(TradeGood good,int good_amount)
{}
