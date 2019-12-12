#ifndef NATION_H
#define NATION_H

#include <map>
#include "economy.h"
#include "worldmarket.h"

class Nation
{
public:
    Nation();
    void Run();
    int Population();
    const Economy& Economy();
    void BuildMine();
    bool CanBuildMine();
    void BuildOilWell();
    bool CanBuildOilWell();
    void BuildLoggingCamp();
    bool CanBuildLoggingCamp();
    void BuildFactory();
    bool CanBuildFactory();
    void BuildFarm();
    bool CanBuildFarm();
    void SetProductionShares(int capital,int consumer);
    int RawMaterialUndeveloped(RawMaterial);
    int UnusedLand();
    double GoldReserves()const;
    void SetImport(TradeGood,int good_amount);
    void SetExport(TradeGood,int good_amount);
    double GetTradeBalance();
    bool CanAffordTrade();
private:
    int population;
    double growth_rate;
    int land;
    int unused_land;
    class Economy economy;
    std::map<RawMaterial,int> undeveloped_resources;
    int gold_reserves;
    WorldMarket world_market;
    std::map<TradeGood,int> import_amounts;
    std::map<TradeGood,int> export_amounts;
    void conduct_world_trade();
};

#endif // NATION_H
