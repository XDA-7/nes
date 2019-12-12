#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , n{Nation{}}
    , previous_consumer_goods{0}
    , previous_capital_goods{0}
    , previous_agricultural_goods{0}
{
    ui->setupUi(this);
    refresh_nation_data();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_end_turn_clicked()
{
    set_previous_values();
    n.Run();
    refresh_nation_data();
}
void MainWindow::set_previous_values()
{
    previous_capital_goods = n.Economy().CapitalGoods();
    previous_consumer_goods = n.Economy().ConsumerGoods();
    previous_agricultural_goods = n.Economy().AgriculturalGoods();
}
void MainWindow::refresh_nation_data()
{
    ui->population_val->setNum(n.Population());
    ui->ore_production->setNum(n.Economy().RawMaterialProduction(RawMaterial::Ore));
    ui->oil_production->setNum(n.Economy().RawMaterialProduction(RawMaterial::Oil));
    ui->wood_production->setNum(n.Economy().RawMaterialProduction(RawMaterial::Wood));
    ui->ore_developed->setNum(n.Economy().DevelopedRawMaterials(RawMaterial::Ore));
    ui->oil_developed->setNum(n.Economy().DevelopedRawMaterials(RawMaterial::Oil));
    ui->wood_developed->setNum(n.Economy().DevelopedRawMaterials(RawMaterial::Wood));
    ui->ore_undeveloped->setNum(n.RawMaterialUndeveloped(RawMaterial::Ore));
    ui->oil_undeveloped->setNum(n.RawMaterialUndeveloped(RawMaterial::Oil));
    ui->wood_undeveloped->setNum(n.RawMaterialUndeveloped(RawMaterial::Wood));

    ui->unused_land->setNum(n.UnusedLand());
    ui->industrial_base->setNum(n.Economy().IndustrialBase());
    ui->agricultural_base->setNum(n.Economy().AgriculturalBase());
    ui->pop_sat->setNum(n.Economy().PopulationMultiplier());
    ui->res_sat->setNum(n.Economy().ResourceMultiplier());
    ui->capital_stock->setNum(n.Economy().AvailableCapitalGoods());

    change_numeric_value(ui->consumer_goods,ui->consumer_goods_change,n.Economy().ConsumerGoods(),previous_consumer_goods);
    change_numeric_value(ui->capital_goods,ui->capital_goods_change,n.Economy().CapitalGoods(),previous_capital_goods);
    change_numeric_value(ui->agricultural_goods,ui->agricultural_goods_change,n.Economy().AgriculturalGoods(),previous_agricultural_goods);

    ui->build_mine->setEnabled(n.CanBuildMine());
    ui->build_oil_well->setEnabled(n.CanBuildOilWell());
    ui->build_logging_camp->setEnabled(n.CanBuildLoggingCamp());
    ui->build_factory->setEnabled(n.CanBuildFactory());
    ui->build_farm->setEnabled(n.CanBuildFarm());

    limit_export_range();
}
void MainWindow::change_numeric_value(QLabel* value,QLabel* change,int current_value,int previous_value)
{
    value->setNum(current_value);
    change->setText("(" + QString::number(current_value - previous_value) + ")");
}
void MainWindow::limit_export_range()
{
    ui->food_export_quantity->setMaximum(n.Economy().AgriculturalGoods());
    ui->wood_export_quantity->setMaximum(n.Economy().RawMaterialProduction(RawMaterial::Wood));
    ui->ore_export_quantity->setMaximum(n.Economy().RawMaterialProduction(RawMaterial::Ore));
    ui->oil_export_quantity->setMaximum(n.Economy().RawMaterialProduction(RawMaterial::Oil));
    ui->consumer_export_quantity->setMaximum(n.Economy().ConsumerGoods());
    ui->capital_export_quantity->setMaximum(n.Economy().CapitalGoods());
}
void MainWindow::calculate_trade_balance()
{
    ui->trade_balance->setNum(n.GetTradeBalance());
}

void MainWindow::on_build_mine_clicked()
{
    n.BuildMine();
    refresh_nation_data();
}

void MainWindow::on_build_oil_well_clicked()
{
    n.BuildOilWell();
    refresh_nation_data();
}

void MainWindow::on_build_logging_camp_clicked()
{
    n.BuildLoggingCamp();
    refresh_nation_data();
}

void MainWindow::on_build_factory_clicked()
{
    n.BuildFactory();
    refresh_nation_data();
}

void MainWindow::on_production_share_valueChanged(int value)
{
    n.SetProductionShares(100 - value,value);
}

void MainWindow::on_build_farm_clicked()
{
    n.BuildFarm();
    refresh_nation_data();
}

void MainWindow::on_food_export_quantity_valueChanged(int arg1)
{
    n.SetExport(TradeGood::Food,arg1);
    calculate_trade_balance();
}

void MainWindow::on_wood_export_quantity_valueChanged(int arg1)
{
    n.SetExport(TradeGood::Wood,arg1);
    calculate_trade_balance();
}

void MainWindow::on_oil_export_quantity_valueChanged(int arg1)
{
    n.SetExport(TradeGood::Oil,arg1);
    calculate_trade_balance();
}

void MainWindow::on_ore_export_quantity_valueChanged(int arg1)
{
    n.SetExport(TradeGood::Ore,arg1);
    calculate_trade_balance();
}

void MainWindow::on_consumer_export_quantity_valueChanged(int arg1)
{
    n.SetExport(TradeGood::ConsumerGoods,arg1);
    calculate_trade_balance();
}

void MainWindow::on_capital_export_quantity_valueChanged(int arg1)
{
    n.SetExport(TradeGood::CapitalGoods,arg1);
    calculate_trade_balance();
}

void MainWindow::on_food_import_quantity_valueChanged(int arg1)
{
    n.SetImport(TradeGood::Food,arg1);
    calculate_trade_balance();
}

void MainWindow::on_wood_import_quantity_valueChanged(int arg1)
{
    n.SetImport(TradeGood::Wood,arg1);
    calculate_trade_balance();
}

void MainWindow::on_oil_import_quantity_valueChanged(int arg1)
{
    n.SetImport(TradeGood::Oil,arg1);
    calculate_trade_balance();
}

void MainWindow::on_ore_import_quantity_valueChanged(int arg1)
{
    n.SetImport(TradeGood::Ore,arg1);
    calculate_trade_balance();
}

void MainWindow::on_consumer_import_quantity_valueChanged(int arg1)
{
    n.SetImport(TradeGood::ConsumerGoods,arg1);
    calculate_trade_balance();
}

void MainWindow::on_capital_import_quantity_valueChanged(int arg1)
{
    n.SetImport(TradeGood::CapitalGoods,arg1);
    calculate_trade_balance();
}
