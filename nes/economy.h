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
    int IndustrialBase();
    int ConsumerGoods();
    int AvailableCapitalGoods();
    int RawMaterialProduction(RawMaterial);
    int DevelopedRawMaterials(RawMaterial);
    void BuildRawMaterialCapacity(RawMaterial,int capital_cost,int development_size);
    void BuildIndustrialCapacity(int capital_cost,int output);
    void DestroyIndustrialCapacity(int output);
    void Run();
private:
    double consumer_goods_share;
    double capital_goods_share;
    int available_capital_goods;
    std::map<RawMaterial,int> developed_raw_materials;
    std::map<RawMaterial,int> raw_material_output;
    int base_industrial_output;
    int population;
    bool dirty;
    int resolved_consumer_goods;
    int resolved_capital_goods;
    void resolve_output();
};

#endif // ECONOMY_H
