#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include "nation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_end_turn_clicked();

    void on_build_mine_clicked();

    void on_build_oil_well_clicked();

    void on_build_logging_camp_clicked();

    void on_build_factory_clicked();

    void on_production_share_valueChanged(int value);

    void on_build_farm_clicked();

    void on_food_export_quantity_valueChanged(int arg1);

    void on_wood_export_quantity_valueChanged(int arg1);

    void on_oil_export_quantity_valueChanged(int arg1);

    void on_ore_export_quantity_valueChanged(int arg1);

    void on_consumer_export_quantity_valueChanged(int arg1);

    void on_capital_export_quantity_valueChanged(int arg1);

    void on_food_import_quantity_valueChanged(int arg1);

    void on_wood_import_quantity_valueChanged(int arg1);

    void on_oil_import_quantity_valueChanged(int arg1);

    void on_ore_import_quantity_valueChanged(int arg1);

    void on_consumer_import_quantity_valueChanged(int arg1);

    void on_capital_import_quantity_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Nation n;
    int previous_consumer_goods;
    int previous_capital_goods;
    int previous_agricultural_goods;
    void set_previous_values();
    void refresh_nation_data();
    void change_numeric_value(QLabel* value,QLabel* change,int current_value,int previous_value);
    void limit_export_range();
    void calculate_trade_balance();
};
#endif // MAINWINDOW_H
