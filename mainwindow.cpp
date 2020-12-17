#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();
    ui->indexEdit->setValidator(new QIntValidator(1, 1000));
    tree = new Tree;
}

MainWindow::~MainWindow()
{
    delete openAct;
    delete saveAct;
    delete fileMenu;
    delete tree;
    delete ui;
}


void MainWindow::on_addBtn_clicked()
{
    tree->insert(ui->indexEdit->text().toInt(),
                 ui->nameEdit->text().toStdString());
    updateTree();
}

void MainWindow::on_delBtn_clicked()
{
    tree->erase(ui->indexEdit->text().toInt());
    updateTree();
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::New);
    openAct->setStatusTip(tr("Open map from file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openMap);

    saveAct = new QAction(tr("&Save as..."), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save map to file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveMap);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
}

void MainWindow::openMap()
{
    QString path = QFileDialog::getOpenFileName(this, "Read map from file",
                                        QCoreApplication::applicationDirPath(),
                                        "Text file (*.txt)" );
    if (!path.isEmpty())
        tree->read(path.toStdString());
    updateTree();
}

void MainWindow::saveMap()
{
    QString path = QFileDialog::getSaveFileName(this, "Save map to file",
                                        QCoreApplication::applicationDirPath(),
                                        "Text file (*.txt)" );
    if (!path.isEmpty())
        tree->read(path.toStdString());
}

void MainWindow::updateTree()
{
    ui->listWidget->clear();
    int cnt = tree->getSize();
    Node *nodes = new Node[cnt];
    tree->returnAscending(nodes);
    for (int i = 0; i < cnt; ++i) {
        QString str; str.append(QString::number(nodes[i].key)); str.append(": ");
        str.append(QString::fromStdString(nodes[i].value));
        ui->listWidget->addItem(new QListWidgetItem(str));
    }
}
