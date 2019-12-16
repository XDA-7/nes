#include <cstdlib>
#include "nation.h"

Nation::Nation()
{
    unused_land = 360;
    undeveloped_resources = std::map<RawMaterial,int>
    {
        {RawMaterial::Oil,0},
        {RawMaterial::Ore,0},
        {RawMaterial::Wood,0}
    };
    resource_discovery_chance = std::map<RawMaterial,double>
    {
        {RawMaterial::Oil,0.05},
        {RawMaterial::Ore,0.15},
        {RawMaterial::Wood,0.5}
    };
    resource_discovery_size = std::map<RawMaterial,int>
    {
        {RawMaterial::Oil,12 * 3600},
        {RawMaterial::Ore,18 * 3600},
        {RawMaterial::Wood,6 * 3600},
    };
    gold_reserves = 0.0;
}
void Nation::Run()
{
    auto good_balances {conduct_world_trade()};
    update_population(good_balances);
    update_economy(good_balances);
    discover_resources();
}
const Population& Nation::Population()
{
    return population;
}
const Economy& Nation::Economy()
{
    return economy;
}
const WorldMarket& Nation::WorldMarket()
{
    return world_market;
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
        balance -= world_market.BuyPrice(pair.first,pair.second);
    }
    for(auto pair : export_amounts)
    {
        balance += world_market.SellPrice(pair.first,pair.second);
    }
    return balance;
}
bool Nation::CanAffordTrade()
{
    return gold_reserves - GetTradeBalance() > 0;
}
int Nation::GetMaxImportAffordable(TradeGood good)
{
    return static_cast<int>(gold_reserves / world_market.BuyPrice(good,1));
}

std::map<TradeGood,int> Nation::conduct_world_trade()
{
    std::map<TradeGood,int> good_balances{};
    for(auto im : import_amounts)
    {
        world_market.Buy(im.first,im.second);
        gold_reserves -= world_market.BuyPrice(im.first,im.second);
        good_balances[im.first] = im.second;
    }
    for(auto ex : export_amounts)
    {
        world_market.Sell(ex.first,ex.second);
        gold_reserves += world_market.SellPrice(ex.first,ex.second);
        if(good_balances.find(ex.first) == good_balances.end())
        {
            good_balances[ex.first] = -ex.second;
        }
        else
        {
            good_balances[ex.first] -= ex.second;
        }
    }
    return good_balances;
}
void Nation::discover_resources()
{
    for(auto pair : resource_discovery_chance)
    {
        double roll = static_cast<double>(std::rand()) / RAND_MAX;
        if(roll < pair.second)
        {
            undeveloped_resources[pair.first] += resource_discovery_size[pair.first];
        }
    }
}
int get_trade_balance(const std::map<TradeGood,int>& balances,TradeGood good)
{
    auto trade_balance = balances.find(good);
    if(trade_balance == balances.end())
    {
        return 0;
    }
    else
    {
        return trade_balance->second;
    }
}
void Nation::update_population(const std::map<TradeGood,int>& good_balances)
{
    population.SetFoodSupply(economy.AgriculturalGoods() + get_trade_balance(good_balances,TradeGood::Food));
    population.SetGoodsSupply(economy.ConsumerGoods() + get_trade_balance(good_balances,TradeGood::ConsumerGoods));
    population.Run();
}
void Nation::update_economy(const std::map<TradeGood,int>& good_balances)
{
    economy.UpdatePopulation(population.Total());
    economy.SetRawMaterialTradeAmount(RawMaterial::Oil,get_trade_balance(good_balances,TradeGood::Oil));
    economy.SetRawMaterialTradeAmount(RawMaterial::Ore,get_trade_balance(good_balances,TradeGood::Ore));
    economy.SetRawMaterialTradeAmount(RawMaterial::Wood,get_trade_balance(good_balances,TradeGood::Wood));
    economy.SetCapitalGoodsTradeAmount(get_trade_balance(good_balances,TradeGood::CapitalGoods));
    economy.Run();
}
