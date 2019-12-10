#include <limits>
#include "economy.h"

Economy::Economy()
    : consumer_goods_share{0.0}
    , capital_goods_share{1.0}
    , available_capital_goods{3600}
    , developed_raw_materials{std::map<RawMaterial,int>{}}
    , raw_material_output{std::map<RawMaterial,int>{}}
    , base_industrial_output{0}
    , population{0}
    , dirty{true}
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
int Economy::IndustrialBase()
{
    return base_industrial_output;
}
int Economy::ConsumerGoods()
{
    resolve_output();
    return resolved_consumer_goods;
}
int Economy::AvailableCapitalGoods()
{
    return available_capital_goods;
}
int Economy::RawMaterialProduction(RawMaterial rm)
{
    return raw_material_output[rm];
}
int Economy::DevelopedRawMaterials(RawMaterial rm)
{
    return developed_raw_materials[rm];
}
void Economy::BuildRawMaterialCapacity(RawMaterial rm,int capital_cost,int development_size)
{
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    developed_raw_materials[rm] += development_size;
}
void Economy::BuildIndustrialCapacity(int capital_cost,int output)
{
    if(capital_cost > available_capital_goods)
    {
        throw std::exception{};
    }
    available_capital_goods -= capital_cost;
    base_industrial_output += output;
}
void Economy::DestroyIndustrialCapacity(int output)
{
    base_industrial_output -= output;
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

void Economy::resolve_output()
{
    if(!dirty)
    {
        return;
    }
    dirty = false;
    int total_economy_size = 0;
    int limiting_natural_resource = std::numeric_limits<int>::max();
    for(auto developed_material : developed_raw_materials)
    {
        int resource_output = developed_material.second / 60;
        total_economy_size += resource_output;
        raw_material_output[developed_material.first] = resource_output;
        limiting_natural_resource = std::min(limiting_natural_resource,resource_output);
    }
    total_economy_size += base_industrial_output;
    double population_multiplier = static_cast<double>(population) / static_cast<double>(total_economy_size);
    double resource_multiplier = static_cast<double>(limiting_natural_resource) / static_cast<double>(base_industrial_output);
    double industry_multiplier = std::min(population_multiplier,resource_multiplier);
    int resolved_industrial_output = static_cast<int>(base_industrial_output * industry_multiplier);
    resolved_capital_goods = static_cast<int>(resolved_industrial_output * capital_goods_share);
    resolved_consumer_goods = static_cast<int>(resolved_industrial_output * consumer_goods_share);
    dirty = false;
}
