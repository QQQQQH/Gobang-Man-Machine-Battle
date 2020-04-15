#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menubar->hide();
    ui->statusbar->hide();

    setWindowTitle(tr("Gomoku"));

    setMinimumSize(640, 480);
    resize(800, 600);

    gomoku = ui->gomoku;

    gomoku->setEnabled(false);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::setupGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGame() {
    if (gomoku->getState() == GomokuBoard::END) {
        gomoku->setEnabled(true);
        gomoku->start(ui->humanRadioButton->isChecked() ? 1 : 2,
                      ui->depthSlider->value());
        ui->pushButton->setText(tr("Reset"));
    }
    else {
        gomoku->reset();
        gomoku->setEnabled(false);
        ui->pushButton->setText(tr("Start"));
    }
}

