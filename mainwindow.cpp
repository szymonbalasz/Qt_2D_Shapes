#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui()
{
    this->ui->renderArea->repaint();
    this->ui->spinScale->setValue(this->ui->renderArea->scale());
    this->ui->spinInterval->setValue(this->ui->renderArea->interval());
    this->ui->spinCount->setValue(this->ui->renderArea->stepCount());
}

void MainWindow::on_btnAstroid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Astroid);
    update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
    update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    update_ui();
}

void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    update_ui();
}

void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    update_ui();
}

void MainWindow::on_btnCircle_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Circle);
    update_ui();
}

void MainWindow::on_btnEllipse_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Ellipse);
    update_ui();
}

void MainWindow::on_btnTwirly_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Twirly);
    update_ui();
}

void MainWindow::on_btnStarfish_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Starfish);
    update_ui();
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->setScale(scale);
}

void MainWindow::on_spinInterval_valueChanged(double interval)
{
    this->ui->renderArea->setInterval(interval);
}

void MainWindow::on_spinCount_valueChanged(int count)
{
    this->ui->renderArea->setStepCount (count);
}

void MainWindow::on_btnBackground_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->backgroundColor(), this, "Select Color");
    ui->renderArea->setBackgroundColor(color);
}

void MainWindow::on_btnLineColor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->shapeColor(), this, "Select Color");
    ui->renderArea->setShapeColor(color);
}

void MainWindow::on_btnAnimate_clicked()
{
    float count = 0;
    float max = (this->ui->renderArea->interval());
    this->ui->renderArea->setInterval(count);
    do {
        count += 0.02;
        this->ui->renderArea->setInterval(count);
        update_ui();
    } while ((this->ui->renderArea->interval()) < max);

}
