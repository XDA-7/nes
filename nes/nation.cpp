#include "nation.h"

Nation::Nation()
{
    population = 3600;
    growth_rate = 0.03;
    unused_land = 360;
    undeveloped_resources = std::map<RawMaterial,int>
    {
        {RawMaterial::Oil,90000},
        {RawMaterial::Ore,90000},
        {RawMaterial::Wood,90000}
    };
    previous_consumer_goods = 0;
    previous_capital_goods = 0;
}
void Nation::Run()
{
    population = population + static_cast<int>(population * growth_rate);
    economy.UpdatePopulation(population);
    economy.Run();
    consumer_goods_change = economy.ConsumerGoods() - previous_consumer_goods;
    capital_goods_change = economy.AvailableCapitalGoods() - previous_capital_goods;
    previous_consumer_goods = economy.ConsumerGoods();
    previous_capital_goods = economy.AvailableCapitalGoods();
}
int Nation::Population()
{
    return population;
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
void Nation::SetProductionShares(int capital,int consumer)
{
    double sum = static_cast<double>(capital) + static_cast<double>(consumer);
    economy.SetProductionShares(consumer / sum,capital / sum);
}
int Nation::RawMaterialProduction(RawMaterial rm)
{
    return economy.RawMaterialProduction(rm);
}
int Nation::RawMaterialDeveloped(RawMaterial rm)
{
    return economy.DevelopedRawMaterials(rm);
}
int Nation::RawMaterialUndeveloped(RawMaterial rm)
{
    return undeveloped_resources[rm];
}
int Nation::UnusedLand()
{
    return unused_land;
}
int Nation::IndustrialBase()
{
    return economy.IndustrialBase();
}
int Nation::ConsumerGoodsProduction()
{
    return economy.ConsumerGoods();
}
int Nation::ConsumerGoodsChange()
{
    return consumer_goods_change;
}
int Nation::CapitalGoods()
{
    return economy.AvailableCapitalGoods();
}
int Nation::CapitalGoodsChange()
{
    return capital_goods_change;
}
