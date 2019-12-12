#include <cmath>
#include <limits>
#include "economy.h"

Economy::Economy()
    : consumer_goods_share{0.0}
    , capital_goods_share{1.0}
    , available_capital_goods{3600}
    , developed_raw_materials{std::map<RawMaterial,int>{}}
    , raw_material_output{std::map<RawMaterial,int>{}}
    , base_industrial_output{0}
    , base_agricultural_output{0}
    , population{0}
    , dirty{true}
    , resolved_consumer_goods{0}
    , resolved_capital_goods{0}
    , resolved_agricultural_goods{0}
    , economy_size{0}
    , resource_multiplier{0.0}
    , population_multiplier{0.0}
    , capital_goods_trade{0}
{
    developed_raw_materials.insert({{RawMaterial::Oil,0},{RawMaterial::Ore,0},{RawMaterial::Wood,0}});
    raw_material_output.insert({{RawMaterial::Oil,0},{RawMaterial::Ore,0},{RawMaterial::Wood,0}});
}

void Economy::SetProductionShares(double consumer,double capital)
{
    if(consumer + capital != 1.0)
    {
        throw std::exception{};
    }
    consumer_goods_share = consumer;
    capital_goods_share = capital;
    dirty = true;
}
void Economy::UpdatePopulation(int pop)
{
    population = pop;
    dirty = true;
}
int Economy::IndustrialBase()const
{
    return base_industrial_output;
}
int Economy::AgriculturalBase()const
{
    return base_agricultural_output;
}
int Economy::ConsumerGoods()const
{
    return resolved_consumer_goods;
}
int Economy::CapitalGoods()const
{
    return resolved_capital_goods;
}
int Economy::AvailableCapitalGoods()const
{
    return available_capital_goods;
}
int Economy::AgriculturalGoods()const
{
    return resolved_agricultural_goods;
}
int Economy::RawMaterialProduction(RawMaterial rm)const
{
    return raw_material_output.at(rm);
}
int Economy::DevelopedRawMaterials(RawMaterial rm)const
{
    return developed_raw_materials.at(rm);
}
int Economy::EconomySize()const
{
    return economy_size;
}
double Economy::PopulationMultiplier()const
{
    return population_multiplier;
}
double Economy::ResourceMultiplier()const
{
    return resource_multiplier;
}
void Economy::BuildRawMaterialCapacity(RawMaterial rm,int capital_cost,int development_size)
{
    dirty = true;
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    developed_raw_materials[rm] += development_size;
}
void Economy::BuildIndustrialCapacity(int capital_cost,int output)
{
    dirty = true;
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    base_industrial_output += output;
}
void Economy::DestroyIndustrialCapacity(int output)
{
    dirty = true;
    base_industrial_output -= output;
}
void Economy::BuildAgriculturalCapacity(int capital_cost,int output)
{
    dirty = true;
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    base_agricultural_output += output;
}
void Economy::DestroyAgriculturalCapacity(int output)
{
    dirty = true;
    base_agricultural_output -= output;
}
void Economy::Run()
{
    resolve_output();
    for(auto& developed_material : developed_raw_materials)
    {
        int decrease = raw_material_output[developed_material.first];
        developed_material.second -= decrease;
    }
    available_capital_goods += resolved_capital_goods;
}
void Economy::SetRawMaterialTradeAmount(RawMaterial rm,int amount)
{
    raw_material_trades[rm] = amount;
}
void Economy::SetCapitalGoodsTradeAmount(int amount)
{
    capital_goods_trade = amount;
}

void Economy::resolve_output()
{
    if(!dirty)
    {
        return;
    }
    dirty = false;
    economy_size = 0;
    int limiting_natural_resource = std::numeric_limits<int>::max();
    for(auto developed_material : developed_raw_materials)
    {
        int resource_output = developed_material.second / 60 + raw_material_trades[developed_material.first];
        economy_size += resource_output;
        raw_material_output[developed_material.first] = resource_output;
        limiting_natural_resource = std::min(limiting_natural_resource,resource_output);
    }
    economy_size += base_industrial_output;
    economy_size += base_agricultural_output;
    if(economy_size != 0)
    {
        calculate_population_multiplier();
        resolved_agricultural_goods = static_cast<int>(base_agricultural_output * population_multiplier);
        if(base_industrial_output != 0)
        {
            resource_multiplier = static_cast<double>(limiting_natural_resource) / static_cast<double>(base_industrial_output);
            double industry_multiplier = std::min(population_multiplier,resource_multiplier);
            int resolved_industrial_output = static_cast<int>(base_industrial_output * industry_multiplier);
            resolved_capital_goods = static_cast<int>(resolved_industrial_output * capital_goods_share) + capital_goods_trade;
            resolved_consumer_goods = static_cast<int>(resolved_industrial_output * consumer_goods_share);
        }
    }
    dirty = false;
}
void Economy::calculate_population_multiplier()
{
    double ratio = static_cast<double>(population) / static_cast<double>(economy_size);
    if(ratio < 1.0)
    {
        double diff = 1.0 - ratio;
        population_multiplier = 1.0 - (diff * diff);
    }
    else
    {
        population_multiplier = std::log2(ratio) + 1.0;
    }
}
