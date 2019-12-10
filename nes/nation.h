#ifndef NATION_H
#define NATION_H

#include <map>
#include <set>
#include <vector>
#include "economy.h"

class Nation
{
public:
    Nation();
    void Run();
    int Population();
    void BuildMine();
    bool CanBuildMine();
    void BuildOilWell();
    bool CanBuildOilWell();
    void BuildLoggingCamp();
    bool CanBuildLoggingCamp();
    void BuildFactory();
    bool CanBuildFactory();
    void SetProductionShares(int capital,int consumer);
    int RawMaterialProduction(RawMaterial);
    int RawMaterialDeveloped(RawMaterial);
    int RawMaterialUndeveloped(RawMaterial);
    int UnusedLand();
    int IndustrialBase();
    int ConsumerGoodsProduction();
    int ConsumerGoodsChange();
    int CapitalGoods();
    int CapitalGoodsChange();
private:
    int population;
    double growth_rate;
    int land;
    int unused_land;
    Economy economy;
    std::map<RawMaterial,int> undeveloped_resources;
    int previous_consumer_goods;
    int previous_capital_goods;
    int consumer_goods_change;
    int capital_goods_change;
};

#endif // NATION_H
