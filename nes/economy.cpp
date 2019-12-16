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
    , resolved_consumer_goods{0}
    , capital_goods_output{0}
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
    resolve_output();
}
void Economy::UpdatePopulation(int pop)
{
    population = pop;
    resolve_output();
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
    return capital_goods_output;
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
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    developed_raw_materials[rm] += development_size;
    resolve_output();
}
void Economy::BuildIndustrialCapacity(int capital_cost,int output)
{
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    base_industrial_output += output;
    resolve_output();
}
void Economy::DestroyIndustrialCapacity(int output)
{
    base_industrial_output -= output;
    resolve_output();
}
void Economy::BuildAgriculturalCapacity(int capital_cost,int output)
{
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    base_agricultural_output += output;
    resolve_output();
}
void Economy::DestroyAgriculturalCapacity(int output)
{
    base_agricultural_output -= output;
    resolve_output();
}
void Economy::Run()
{
    for(auto& developed_material : developed_raw_materials)
    {
        int decrease = raw_material_output[developed_material.first];
        developed_material.second -= decrease;
        raw_material_trades[developed_material.first] = std::min(raw_material_trades[developed_material.first],developed_material.second);
    }
    available_capital_goods += resolved_capital_goods;
    resolve_output();
}
void Economy::SetRawMaterialTradeAmount(RawMaterial rm,int amount)
{
    raw_material_trades[rm] = amount;
    resolve_output();
}
void Economy::SetCapitalGoodsTradeAmount(int amount)
{
    capital_goods_trade = amount;
    resolve_output();
}

void Economy::resolve_output()
{
    economy_size = 0;
    int limiting_natural_resource = std::numeric_limits<int>::max();
    for(auto developed_material : developed_raw_materials)
    {
        int base_res_output = developed_material.second / 60;
        int resource_output = base_res_output + raw_material_trades[developed_material.first];
        economy_size += base_res_output;
        raw_material_output[developed_material.first] = base_res_output;
        limiting_natural_resource = std::min(limiting_natural_resource,resource_output);
    }
    economy_size += base_industrial_output;
    economy_size += base_agricultural_output;
    if(economy_size != 0)
    {
        population_multiplier = calculate_multiplier(population,economy_size);
        resolved_agricultural_goods = static_cast<int>(base_agricultural_output * population_multiplier);
        if(base_industrial_output != 0)
        {
            resource_multiplier = calculate_multiplier(limiting_natural_resource,base_industrial_output);
            double industry_multiplier = std::min(population_multiplier,resource_multiplier);
            int resolved_industrial_output = static_cast<int>(base_industrial_output * industry_multiplier);
            capital_goods_output = static_cast<int>(resolved_industrial_output * capital_goods_share);
            resolved_consumer_goods = static_cast<int>(resolved_industrial_output * consumer_goods_share);
        }
        resolved_capital_goods = capital_goods_output + capital_goods_trade;
    }
}
double Economy::calculate_multiplier(int numerator,int denominator)
{
    double ratio = static_cast<double>(numerator) / static_cast<double>(denominator);
    if(ratio < 1.0)
    {
        double diff = 1.0 - ratio;
        return 1.0 - (diff * diff);
    }
    else
    {
        return std::log2(ratio) + 1.0;
    }
}
