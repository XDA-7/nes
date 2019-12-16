#ifndef ECONOMY_H
#define ECONOMY_H

#include<map>
#include<vector>

enum class RawMaterial
{
    Wood,Ore,Oil
};

class Economy
{
public:
    Economy();
    void SetProductionShares(double consumer,double capital);
    void UpdatePopulation(int pop);
    int IndustrialBase()const;
    int AgriculturalBase()const;
    int ConsumerGoods()const;
    int CapitalGoods()const;
    int AvailableCapitalGoods()const;
    int AgriculturalGoods()const;
    int RawMaterialProduction(RawMaterial)const;
    int DevelopedRawMaterials(RawMaterial)const;
    int EconomySize()const;
    double PopulationMultiplier()const;
    double ResourceMultiplier()const;
    void BuildRawMaterialCapacity(RawMaterial,int capital_cost,int development_size);
    void BuildIndustrialCapacity(int capital_cost,int output);
    void DestroyIndustrialCapacity(int output);
    void BuildAgriculturalCapacity(int capital_cost,int output);
    void DestroyAgriculturalCapacity(int output);
    void SetRawMaterialTradeAmount(RawMaterial,int amount);
    void SetCapitalGoodsTradeAmount(int amount);
    void Run();
private:
    double consumer_goods_share;
    double capital_goods_share;
    int available_capital_goods;
    std::map<RawMaterial,int> developed_raw_materials;
    std::map<RawMaterial,int> raw_material_output;
    int base_industrial_output;
    int base_agricultural_output;
    int population;
    int resolved_consumer_goods;
    int capital_goods_output;
    int resolved_capital_goods;
    int resolved_agricultural_goods;
    int economy_size;
    double resource_multiplier;
    double population_multiplier;
    //trade variables
    std::map<RawMaterial,int> raw_material_trades;
    int capital_goods_trade;

    void resolve_output();
    void calculate_economy_size();
    double calculate_multiplier(int numerator,int denominator);
};

#endif // ECONOMY_H
