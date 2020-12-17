#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include "map.h"

typedef map<int, std::string> Tree;
typedef node<int, std::string> Node;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addBtn_clicked();
    void on_delBtn_clicked();
    void openMap();
    void saveMap();

private:
    Ui::MainWindow *ui;
    Tree *tree;
    QMenu *fileMenu;
    QAction *openAct;
    QAction *saveAct;
    void updateTree();
    void createActions();
    void createMenus();
};
#endif // MAINWINDOW_H
