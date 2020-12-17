#include "mainwindow.h"
#include "map.h"

#include <QApplication>
#include <assert.h>

typedef node<int, std::string> Node;
typedef map<int, std::string> Tree;

int main(int argc, char *argv[])
{
    /* ==== TESTS ====
    Tree tree;
    assert(tree.getSize() == 0);
    tree.insert(6, "A");
    assert(tree.getSize() == 1);
    tree.insert(6, "A");
    assert(tree.getSize() == 1);
    assert(tree.contains(6) == true);
    assert(tree[6] == "A");
    tree.erase(6);
    assert(tree.getSize() == 0);
    tree.erase(5);
    assert(tree.getSize() == 0);
    assert(tree.contains(6) == false);
    tree.insert(5, "B");
    tree.insert(7, "C");
    tree.insert(1, "D");
    tree.insert(4, "E");
    tree.insert(3, "F");
    tree.insert(2, "G");

    tree.printAscending();

    Tree t2 = tree;
    t2.printAscending();

    t2.write("tree.txt");
    tree.read("tree.txt");
    tree.printAscending();
    assert(t2 == tree);

    int cnt = tree.getSize();
    Node *nodes = new Node[cnt];
    std::cout << cnt << '\n';
    tree.returnAscending(nodes);
    for (int i = 0; i < cnt; ++i)
        std::cout << nodes[i].key << ": " << nodes[i].value << "\n";
    ==== END OF TESTS ====*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
