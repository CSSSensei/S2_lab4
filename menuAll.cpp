#include "menuAll.h"

void menu(){
    int type;
    wcout << L"Выберете тип дерева, с которым будете работать: \n"
         << L"\t1: Бинарное дерево поиска\n"
         << L"\t2: Бинарная куча\n"
         << L"\t3: Тесты\n"
         << L"Введите число:";
    cin >> type;

    if (type == 1)
        MenuBinaryTree();
    else if (type == 2)
        MenuHeapArray();
    else
        testBinaryTree();
        testHeapArray();
}