#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , n{Nation{}}
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
    n.Run();
    refresh_nation_data();
}
void MainWindow::refresh_nation_data()
{
    ui->population_val->setNum(n.Population());
    ui->ore_production->setNum(n.RawMaterialProduction(RawMaterial::Ore));
    ui->oil_production->setNum(n.RawMaterialProduction(RawMaterial::Oil));
    ui->wood_production->setNum(n.RawMaterialProduction(RawMaterial::Wood));
    ui->ore_developed->setNum(n.RawMaterialDeveloped(RawMaterial::Ore));
    ui->oil_developed->setNum(n.RawMaterialDeveloped(RawMaterial::Oil));
    ui->wood_developed->setNum(n.RawMaterialDeveloped(RawMaterial::Wood));
    ui->ore_undeveloped->setNum(n.RawMaterialUndeveloped(RawMaterial::Ore));
    ui->oil_undeveloped->setNum(n.RawMaterialUndeveloped(RawMaterial::Oil));
    ui->wood_undeveloped->setNum(n.RawMaterialUndeveloped(RawMaterial::Wood));

    ui->unused_land->setNum(n.UnusedLand());
    ui->industrial_base->setNum(n.IndustrialBase());
    ui->consumer_goods->setNum(n.ConsumerGoodsProduction());
    ui->consumer_goods_change->setText("(" + QString::number(n.ConsumerGoodsChange()) + ")");
    ui->capital_goods->setNum(n.CapitalGoods());
    ui->capital_goods_change->setText("(" + QString::number(n.CapitalGoodsChange()) + ")");

    ui->build_mine->setEnabled(n.CanBuildMine());
    ui->build_oil_well->setEnabled(n.CanBuildOilWell());
    ui->build_logging_camp->setEnabled(n.CanBuildLoggingCamp());
    ui->build_factory->setEnabled(n.CanBuildFactory());
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
