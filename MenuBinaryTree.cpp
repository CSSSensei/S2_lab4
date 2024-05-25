#include "MenuBinaryTree.h"
#include "MenuHeapArray.h"

int chooseTypeBinaryTree() {
    wcout << L"Выберите тип, с которым будете работать: \n"
          << L"\t1: int\n"
          << L"\t2: float\n"
          << L"\t3: complex\n"
          << L"Введите число:";
    int type = getNumberInput<int>();

    return type;
}

int chooseFunctionBinaryTree() {
    int func = 0;
    while (true) {
        wcout << L"Выберите функцию, которую нужно произвести над бинарным деревом: \n"
              << L"\t1: Добавление узла\n"
              << L"\t2: Поиск элемента по ключу\n"
              << L"\t3: Удаление узла\n"
              << L"\t4: Балансировка дерева\n"
              << L"\t5: Извлечение поддерева\n"
              << L"\t6: Поиск на вхождение поддерева\n"
              << L"\t7: Слияние двух деревьев\n"
              << L"Введите число:";

        func = getNumberInput<int>();
        if (func <= 0 || func > 7) {
            wcout << L"Такого варинта нет!\n";
        } else {
            break;
        }
    }

    return func;
}

template<class T, class K>
void inputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> *Arr) {

    BinaryTree<T, K> addingTree;
    wcout << L"Введите колличество узлов в дереве" << endl;
    int count = getNumberInput<int>();

    for (int i = 0; i < count; i++) {
        K key;
        T item;
        wcout << L"Введите ключ \"" << i << L"\" узла дерева" << endl;
        key = getNumberInput<K>();
        wcout << L"Введите значение находящееся в \"" << i << L"\" узле дерева" << endl;
        cin >> item;

        addingTree.AddNode(key, item);
    }

    Arr->Append(addingTree);
}

void inputComplexBinaryTreeTyped(DynamicArray<BinaryTree<complex<int>, int>> *Arr) {

    BinaryTree<complex<int>, int> addingTree;
    wcout << L"Введите колличество узлов в дереве" << endl;
    int count = getNumberInput<int>();

    for (int i = 0; i < count; i++) {
        int key;
        complex<int> item;
        wcout << L"Введите ключ \"" << i << L"\" узла дерева" << endl;
        key = getNumberInput<int>();
        wcout << L"Введите значение находящееся в \"" << i << L"\" узле дерева" << endl;
        item = getComplexNumberInput();

        addingTree.AddNode(key, item);
    }

    Arr->Append(addingTree);
}


template<class T, class K>
void functionBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> *Arr) {
    int function = chooseFunctionBinaryTree(), amountOfBinaryTree = Arr->GetFilled(), indexOfTree1 = -1, indexOfTree2 = -1;

    if (function == 6) {
        wcout << L"В памяти находится \"" << amountOfBinaryTree << L"\" деревьев" << endl;
        wcout << L"Выберите индекс дерева, которое хотите проверить на вхождение:" << endl;
        indexOfTree1 = getNumberInput<int>();
        wcout << L"Выберите индекс дерева, вхождение которого нужно проверять:" << endl;
        indexOfTree2 = getNumberInput<int>();
        if (indexOfTree1 >= amountOfBinaryTree || indexOfTree1 < 0 || indexOfTree2 >= amountOfBinaryTree ||
            indexOfTree2 < 0) {
            wcout << L"Дерева с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    } else if (function == 7) {
        wcout << L"В памяти находится \"" << amountOfBinaryTree << L"\" деревьев" << endl;
        wcout << L"Выберите индексы дерева, которые хотите слить в одно:" << endl;
        indexOfTree1 = getNumberInput<int>();
        indexOfTree2 = getNumberInput<int>();
        if (indexOfTree1 >= amountOfBinaryTree || indexOfTree1 < 0 || indexOfTree2 >= amountOfBinaryTree ||
            indexOfTree2 < 0) {
            wcout << L"Дерева с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }

    } else {
        wcout << L"В памяти находится \"" << amountOfBinaryTree << L"\" деревьев" << endl;
        wcout << L"Выберите индекс дерева, с которым хотите работать:" << endl;
        indexOfTree1 = getNumberInput<int>();
        if (indexOfTree1 >= amountOfBinaryTree || indexOfTree1 < 0) {
            wcout << L"Дерева с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    }

    int bol;
    K key;
    T item;
    BinaryTree<T, K> newtree, newtree2, mergedTree;

    switch (function) {
        case 1:
            wcout << L"Введите ключ узла, который хотите добавить в дерево" << endl;
            key = getNumberInput<K>();
            wcout << L"Введите значение находящееся в этом узле" << endl;
            cin >> item;

            newtree = Arr->GetElement(indexOfTree1);
            newtree.AddNode(key, item);
            Arr->Append(newtree);
            break;
        case 2:
            wcout << L"Введите ключ, по которому хотите искать:" << endl;
            key = getNumberInput<K>();
            item = *(Arr->GetElement(indexOfTree1).SearchElement(key));
            wcout << L"В узле с таким ключом лежит — \"" << item << L"\"" << endl;
            break;
        case 3:
            wcout << L"Введите ключ, узел с которым хотите удалить:" << endl;
            key = getNumberInput<K>();

            newtree = Arr->GetElement(indexOfTree1);
            newtree.DeleteElement(key);
            Arr->Append(newtree);
            break;
        case 4:
            newtree = Arr->GetElement(indexOfTree1);
            newtree.Balancing();
            Arr->Append(newtree);
            break;
        case 5:
            wcout << L"Введите ключ, который бдует являться корнем извлекаемого дерева:" << endl;
            key = getNumberInput<K>();

            Arr->Append(Arr->GetElement(indexOfTree1).GetTree(key));
            break;
        case 6:
            newtree = Arr->GetElement(indexOfTree1);
            newtree2 = Arr->GetElement(indexOfTree2);
            bol = newtree.ContainTree(newtree2);

            if (bol == 1)
                wcout << L"Это дерево ЯВЛЯЕТСЯ поддеревом исходного!!!" << endl;
            else
                wcout << L"Это дерево НЕ ЯВЛЯЕТСЯ поддеревом исходного!!!" << endl;
            break;
        case 7:
            newtree = Arr->GetElement(indexOfTree1);
            newtree2 = Arr->GetElement(indexOfTree2);
            mergedTree = newtree.mergeTrees(newtree2);
            Arr->Append(mergedTree);
            break;
        default:
            break;
    }

    if (function == 1 || function == 3 || function == 4 || function == 5 || function == 7) {
        BinaryTree<T, K> resulttree = Arr->GetElement(Arr->GetFilled() - 1);

        wcout << L"Выберите тип вывода дерева: \n"
              << L"\t1: Как массив\n"
              << L"\t2: Как дерево\n"
              << L"Введите число:";
        int variant = getNumberInput<int>();

        switch (variant) {
            case 1:
                PrintBinaryTreeMassive(resulttree);
                break;
            case 2:
                PrintBinaryTreeBeauty(resulttree);
                break;
            default:
                break;
        }
    }

}

template<class T, class K>
void outputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> *Arr) {
    int amountOfBinaryTree = Arr->GetFilled();
    int index, variant;
    wcout << L"В памяти находится \"" << amountOfBinaryTree << L"\" деревьев" << endl;
    wcout << L"Выберите индекс дерева, которое хотите вывести" << endl;
    index = getNumberInput<int>();

    wcout << L"Выберите тип вывода дерева: \n"
          << L"\t1: Как массив\n"
          << L"\t2: Как дерево\n"
          << L"Введите число:";
    variant = getNumberInput<int>();

    if (index < 0 || index >= amountOfBinaryTree)
        variant = 0;

    switch (variant) {
        case 1:
            PrintBinaryTreeMassive(Arr->GetElement(index));
            break;
        case 2:
            PrintBinaryTreeBeauty(Arr->GetElement(index));
            break;
        default:
            break;
    }
}

void MenuBinaryTree() {
    auto *intArr = new DynamicArray<BinaryTree<int, int>>;
    auto *floatArr = new DynamicArray<BinaryTree<float, float>>;
    auto *complexArr = new DynamicArray<BinaryTree<complex<int>, int>>;


    int operation;
    while (true) {
        wcout << L"Выберите операцию: \n"
              << L"\t1: Ввести и запомнить бинарное дерево\n"
              << L"\t2: Выполнить операцию над бинарным деревом\n"
              << L"\t3: Вывести бинарное дерево в консоль\n"
              << L"\t4: Закончить выполнение программы\n"
              << L"Введите число:";
        operation = getNumberInput<int>();

        if (operation == 4)
            break;

        switch (operation) {
            case 1:
                InputAndSaveBinaryTree(intArr, floatArr, complexArr);
                break;
            case 2:
                FunctionWithBinaryTree(intArr, floatArr, complexArr);
                break;
            case 3:
                OutputBinaryTree(intArr, floatArr, complexArr);
                break;
            default:
                break;
        }
    }
}

void InputAndSaveBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                            DynamicArray<BinaryTree<float, float>> *floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>> *complexArr) {
    int type = chooseTypeBinaryTree();

    switch (type) {
        case 1:
            inputBinaryTreeTyped(intArr);
            break;
        case 2:
            inputBinaryTreeTyped(floatArr);
            break;
        case 3:
            inputComplexBinaryTreeTyped(complexArr);
            break;
        default:
            break;
    }
}

void FunctionWithBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                            DynamicArray<BinaryTree<float, float>> *floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>> *complexArr) {
    int type = chooseTypeBinaryTree();

    switch (type) {
        case 1:
            functionBinaryTreeTyped(intArr);
            break;
        case 2:
            functionBinaryTreeTyped(floatArr);
            break;
        case 3:
            functionBinaryTreeTyped(complexArr);
            break;
        default:
            break;
    }
}

void OutputBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                      DynamicArray<BinaryTree<float, float>> *floatArr,
                      DynamicArray<BinaryTree<complex<int>, int>> *complexArr) {
    int type = chooseTypeBinaryTree();


    switch (type) {
        case 1:
            outputBinaryTreeTyped(intArr);
            break;
        case 2:
            outputBinaryTreeTyped(floatArr);
            break;
        case 3:
            outputBinaryTreeTyped(complexArr);
            break;
        default:
            break;
    }
}

