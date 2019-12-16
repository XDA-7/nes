#ifndef NATION_H
#define NATION_H

#include <map>
#include "economy.h"
#include "population.h"
#include "worldmarket.h"

class Nation
{
public:
    Nation();
    void Run();
    const Population& Population();
    const Economy& Economy();
    const WorldMarket& WorldMarket();
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
    int GetMaxImportAffordable(TradeGood);
private:
    int land;
    int unused_land;
    class Population population;
    class Economy economy;
    std::map<RawMaterial,int> undeveloped_resources;
    std::map<RawMaterial,double> resource_discovery_chance;
    std::map<RawMaterial,int> resource_discovery_size;
    double gold_reserves;
    class WorldMarket world_market;
    std::map<TradeGood,int> import_amounts;
    std::map<TradeGood,int> export_amounts;
    std::map<TradeGood,int> conduct_world_trade();
    void discover_resources();
    void update_population(const std::map<TradeGood,int>& good_balances);
    void update_economy(const std::map<TradeGood,int>& good_balances);
};

#endif // NATION_H
