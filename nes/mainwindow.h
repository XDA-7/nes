#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;
    Nation n;
    void refresh_nation_data();
};
#endif // MAINWINDOW_H
