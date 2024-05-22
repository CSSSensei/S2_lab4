#include "MenuBinaryTree.h"

int chooseTypeBinaryTree(){
    int type;
    cout << "Выберете тип, с которым будете работать: \n"
         << "\t1: int\n"
         << "\t2: float\n"
         << "\t3: complex\n"
         << "Введите число: ";
    cin >> type;

    return type;
}
int chooseFunctionBinaryTree(){
    int func;
    cout << "Выберете функцию, которую нужно произвести над бинарным деревом: \n"
         << "\t1: Добавление узла\n"
         << "\t2: Поиск элемента по ключу\n"
         << "\t3: Удаление узла\n"
         << "\t4: Балансировка дерева\n"
         << "\t5: Извлечение поддерева\n"
         << "\t6: Поиск на вхождение поддерева\n"
         << "Введите число: ";
    cin >> func;

    return func;
}

template<class T, class K>
void inputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> *Arr){

    BinaryTree<T, K> addingTree;
    cout << "Введите колличество узлов в дереве" << endl;
    int count;
    cin >> count;

    for (int i = 0; i < count; i++){
        int key, item;
        cout << "Введите ключ \"" << i << "\" узла дерева" << endl;
        cin >> key;
        cout << "Введите значение находящееся в \"" << i << "\" узле дерева" << endl;
        cin >> item;

        addingTree.AddNote(key, item);
    }

    Arr->Append(addingTree);
}

template<class T, class K>
void functionBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> *Arr){
    int function = chooseFunctionBinaryTree();
    int amountOfBinaryTree = Arr->GetFilled();
    int indexOfTree1 = -1;
    int indexOfTree2 = -1;

    if (function == 6){
        cout << "В памяти находится \"" << amountOfBinaryTree << "\" деревьев" << endl;
        cout << "Выберете индекс дерева, которое хотите проверить на вхождение:" << endl;
        cin >> indexOfTree1;
        cout << "Выберете индекс дерева, вхождение которого нужно проверять:" << endl;
        cin >> indexOfTree2;
        if (indexOfTree1 >= amountOfBinaryTree || indexOfTree1 < 0 || indexOfTree2 >= amountOfBinaryTree|| indexOfTree2 < 0){
            cout << "Дерева с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    }else{
        cout << "В памяти находится \"" << amountOfBinaryTree << "\" деревьев" << endl;
        cout << "Выберете индекс дерева, с которым хотите работать:" << endl;
        cin >> indexOfTree1;
        if (indexOfTree1 >= amountOfBinaryTree || indexOfTree1 < 0){
            cout << "Дерева с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    }

    int bol;
    K key;
    T item;
    BinaryTree<T, K> newtree, newtree2;

    switch (function) {
        case 1:
            cout << "Введите ключ узла, который хотите добавить в дерево" << endl;
            cin >> key;
            cout << "Введите значение находящееся в этом узле" << endl;
            cin >> item;

            newtree = Arr->GetElement(indexOfTree1);
            newtree.AddNote(key, item);
            Arr->Append(newtree);
            break;
        case 2:
            cout << "Введите ключ, по которому хотите искать:" << endl;
            cin >> key;
            item = *(Arr->GetElement(indexOfTree1).SearchElement(key));
            cout << "В узле с таким ключом лежит - \"" << item << "\"" << endl;
            break;
        case 3:
            cout << "Введите ключ, узел с которым хотите удалить:" << endl;
            cin >> key;

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
            cout << "Введите ключ, который бдует являться корнем извлекаемого дерева:" << endl;
            cin >> key;

            Arr->Append(Arr->GetElement(indexOfTree1).GetTree(key));
            break;
        case 6:
            newtree = Arr->GetElement(indexOfTree1);
            newtree2 = Arr->GetElement(indexOfTree2);
            bol = newtree.ContainTree(newtree2);

            if (bol == 1)
                cout << "Это дерево ЯВЛЯЕТСЯ поддеревом исходного!!!" << endl;
            else
                cout << "Это дерево НЕ ЯВЛЯЕТСЯ поддеревом исходного!!!" << endl;
            break;
        default:
            break;
    }

    if (function == 1 || function == 3 || function == 4 || function == 5){
        BinaryTree<T, K> resulttree = Arr->GetElement(Arr->GetFilled() - 1);

        int variant;
        cout << "Выберете тип вывода дерева: \n"
             << "\t1: Как массив\n"
             << "\t2: Как дерево\n"
             << "Введите число: ";
        cin >> variant;

        switch (variant){
            case 1:
                PrintBinaryTreeMassive(resulttree);
                break;
            case 2:
                PrintBinaryTreeBeauty(resulttree, 2);
                break;
            default:
                break;
        }
    }

}

template<class T, class K>
void outputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> * Arr){
    int amountOfBinaryTree = Arr->GetFilled();
    int index, variant;
    cout << "В памяти находится \"" << amountOfBinaryTree << "\" деревьев" << endl;
    cout << "Выберете индекс дерева, которое хотите вывести" << endl;
    cin >> index;

    cout << "Выберете тип вывода дерева: \n"
         << "\t1: Как массив\n"
         << "\t2: Как дерево\n"
         << "Введите число: ";
    cin >> variant;

    if (index < 0 || index >= amountOfBinaryTree)
        variant = 0;

    switch (variant) {
        case 1:
            PrintBinaryTreeMassive(Arr->GetElement(index));
            break;
        case 2:
            PrintBinaryTreeBeauty(Arr->GetElement(index), 2);
            break;
        default:
            break;
    }
}

void MenuBinaryTree(){
    auto *intArr = new DynamicArray<BinaryTree<int, int>>;
    auto *floatArr = new DynamicArray<BinaryTree<float, float>>;
    auto *complexArr = new DynamicArray<BinaryTree<complex<int>, int>>;


    int operation;
    while(true){
        cout << "Выберете операцию: \n"
             << "\t1: Ввести и запомнить бинарное дерево\n"
             << "\t2: Выполнить операцию над бинарным деревом\n"
             << "\t3: Вывести бинарное дерево в консоль\n"
             << "\t4: Закончить выполнение программы\n"
             << "Введите число: ";
        cin >> operation;

        if (operation == 4)
            break;

        switch(operation){
            case 1: InputAndSaveBinaryTree(intArr, floatArr, complexArr); break;
            case 2: FunctionWithBinaryTree(intArr, floatArr, complexArr); break;
            case 3: OutputBinaryTree(intArr, floatArr, complexArr); break;
            default: break;
        }
    }
}

void InputAndSaveBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                            DynamicArray<BinaryTree<float, float>> *floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>> *complexArr){
    int type = chooseTypeBinaryTree();

    switch(type){
        case 1: inputBinaryTreeTyped(intArr); break;
        case 2: inputBinaryTreeTyped(floatArr); break;
        case 3: inputBinaryTreeTyped(complexArr); break;
        default: break;
    }
}

void FunctionWithBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                            DynamicArray<BinaryTree<float, float>> *floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>> *complexArr){
    int type = chooseTypeBinaryTree();

    switch(type){
        case 1: functionBinaryTreeTyped(intArr); break;
        case 2: functionBinaryTreeTyped(floatArr); break;
        case 3: functionBinaryTreeTyped(complexArr); break;
        default: break;
    }
}

void OutputBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                      DynamicArray<BinaryTree<float, float>> *floatArr,
                      DynamicArray<BinaryTree<complex<int>, int>> *complexArr){
    int type = chooseTypeBinaryTree();


    switch (type){
        case 1:outputBinaryTreeTyped(intArr); break;
        case 2:outputBinaryTreeTyped(floatArr); break;
        case 3:outputBinaryTreeTyped(complexArr); break;
        default: break;
    }
}

