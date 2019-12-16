#ifndef POPULATION_H
#define POPULATION_H


class Population
{
public:
    Population();
    void Run();
    int Total()const;
    void SetFoodSupply(int);
    double FoodSatisfaction()const;
    void SetGoodsSupply(int);
    double GoodsSatisfaction()const;
private:
    int pop;
    int food_supply;
    double food_satisfaction;
    int goods_supply;
    double goods_satisfaction;
    double growth_rate;
};

#endif // POPULATION_H
