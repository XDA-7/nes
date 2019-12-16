#include "population.h"

Population::Population()
    : pop{3600}
    , food_supply{0}
    , food_satisfaction{0.0}
    , goods_supply{0}
    , goods_satisfaction{0.0}
    , growth_rate{1.0025}
{
}

void Population::Run()
{
    pop = static_cast<int>(pop * growth_rate);
    food_satisfaction = static_cast<double>(food_supply) / static_cast<double>(pop);
    goods_satisfaction = static_cast<double>(goods_supply) / static_cast<double>(pop);
}
int Population::Total()const
{
    return pop;
}
void Population::SetFoodSupply(int supply)
{
    food_supply = supply;
    food_satisfaction = static_cast<double>(food_supply) / static_cast<double>(pop);
}
double Population::FoodSatisfaction()const
{
    return food_satisfaction;
}
void Population::SetGoodsSupply(int supply)
{
    goods_supply = supply;
    goods_satisfaction = static_cast<double>(goods_supply) / static_cast<double>(pop);
}
double Population::GoodsSatisfaction()const
{
    return goods_satisfaction;
}
