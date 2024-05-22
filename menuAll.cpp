#include "menuAll.h"

void menu(){
    int type;
    cout << "Выберете тип дерева, с которым будете работать: \n"
         << "\t1: Бинарное дерево поиска\n"
         << "\t2: Бинарная куча\n"
         << "Введите число: ";
    cin >> type;

    if (type == 1)
        MenuBinaryTree();
    else
        MenuHeapArray();
}