#include "nation.h"

Nation::Nation()
{
    population = 3600;
    growth_rate = 0.0025;
    unused_land = 360;
    undeveloped_resources = std::map<RawMaterial,int>
    {
        {RawMaterial::Oil,90000},
        {RawMaterial::Ore,90000},
        {RawMaterial::Wood,90000}
    };
    gold_reserves = 0;
}
void Nation::Run()
{
    population = population + static_cast<int>(population * growth_rate);
    economy.UpdatePopulation(population);
    economy.Run();
}
int Nation::Population()
{
    return population;
}
const Economy& Nation::Economy()
{
    return economy;
}
void Nation::BuildMine()
{
    undeveloped_resources[RawMaterial::Ore] -= 3600;
    economy.BuildRawMaterialCapacity(RawMaterial::Ore,180,3600);
}
bool Nation::CanBuildMine()
{
    return undeveloped_resources[RawMaterial::Ore] >= 3600 && economy.AvailableCapitalGoods() > 180;
}
void Nation::BuildOilWell()
{
    undeveloped_resources[RawMaterial::Oil] -= 3600;
    economy.BuildRawMaterialCapacity(RawMaterial::Oil,180,3600);
}
bool Nation::CanBuildOilWell()
{
    return undeveloped_resources[RawMaterial::Oil] >= 3600 && economy.AvailableCapitalGoods() > 180;
}
void Nation::BuildLoggingCamp()
{
    undeveloped_resources[RawMaterial::Wood] -= 3600;
    economy.BuildRawMaterialCapacity(RawMaterial::Wood,180,3600);
}
bool Nation::CanBuildLoggingCamp()
{
    return undeveloped_resources[RawMaterial::Wood] >= 3600 && economy.AvailableCapitalGoods() > 180;
}
void Nation::BuildFactory()
{
    --unused_land;
    economy.BuildIndustrialCapacity(180,60);
}
bool Nation::CanBuildFactory()
{
    return unused_land > 0 && economy.AvailableCapitalGoods() > 180;
}
void Nation::BuildFarm()
{
    --unused_land;
    economy.BuildAgriculturalCapacity(180,60);
}
bool Nation::CanBuildFarm()
{
    return unused_land > 0 && economy.AvailableCapitalGoods() > 180;
}
void Nation::SetProductionShares(int capital,int consumer)
{
    double sum = static_cast<double>(capital) + static_cast<double>(consumer);
    economy.SetProductionShares(consumer / sum,capital / sum);
}
int Nation::RawMaterialUndeveloped(RawMaterial rm)
{
    return undeveloped_resources[rm];
}
int Nation::UnusedLand()
{
    return unused_land;
}
double Nation::GoldReserves()const
{
    return gold_reserves;
}
void Nation::SetImport(TradeGood good,int good_amount)
{
    import_amounts[good] = good_amount;
}
void Nation::SetExport(TradeGood good,int good_amount)
{
    export_amounts[good] = good_amount;
}
double Nation::GetTradeBalance()
{
    double balance = 0.0;
    for(auto pair : import_amounts)
    {
        balance -= world_market.buy_price(pair.first,pair.second);
    }
    for(auto pair : export_amounts)
    {
        balance += world_market.sell_price(pair.first,pair.second);
    }
    return balance;
}
bool Nation::CanAffordTrade()
{
    return gold_reserves - GetTradeBalance() > 0;
}

void Nation::conduct_world_trade()
{
}
