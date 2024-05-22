#include "MenuHeapArray.h"

int chooseTypeHeapArray(){
    int type;
    cout << "Выберете тип, с которым будете работать: \n"
         << "\t1: int\n"
         << "\t2: float\n"
         << "\t3: complex\n"
         << "Введите число: ";
    cin >> type;

    return type;
}
int chooseFunctionHeapArray(){
    int func;
    cout << "Выберете функцию, которую нужно произвести над бинарной кучей: \n"
         << "\t1: Добавление узла\n"
         << "\t2: Поиск элемента по ключу\n"
         << "\t3: Удаление узла\n"
         << "\t4: Извлечение поддерева\n"
         << "\t5: Поиск на вхождение поддерева\n"
         << "Введите число: ";
    cin >> func;

    return func;
}

template<class T>
void inputHeapArrayTyped(DynamicArray<HeapArray<T>> *Arr){
    HeapArray<T> addingHeap;

    cout << "Введите колличество узлов в куче" << endl;
    int count;
    cin >> count;

    for (int i = 0; i < count; i++){
        int item;
        cout << "Введите значение добавляемого \"" << i << "\" узла кучи" << endl;
        cin >> item;

        addingHeap.AddElement(item);
    }

    Arr->Append(addingHeap);
}

template<class T>
void functionHeapArrayTyped(DynamicArray<HeapArray<T>> *Arr){
    int function = chooseFunctionHeapArray();
    int amountOfHeapArray = Arr->GetFilled();
    int indexOfHeap1 = -1;
    int indexOfHeap2 = -1;

    if (function == 5){
        cout << "В памяти находится \"" << amountOfHeapArray << "\" куч" << endl;
        cout << "Выберете индекс кучи, которую хотите проверить на вхождение:" << endl;
        cin >> indexOfHeap1;
        cout << "Выберете индекс кучи, вхождение которой нужно проверять:" << endl;
        cin >> indexOfHeap2;
        if (indexOfHeap1 >= amountOfHeapArray || indexOfHeap1 < 0 || indexOfHeap2 >= amountOfHeapArray|| indexOfHeap2 < 0){
            cout << "Кучи с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    }else{
        cout << "В памяти находится \"" << amountOfHeapArray << "\" куч" << endl;
        cout << "Выберете индекс кучи, с которой хотите работать:" << endl;
        cin >> indexOfHeap1;
        if (indexOfHeap1 >= amountOfHeapArray || indexOfHeap1 < 0){
            cout << "Кучи с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    }

    int bol, key;
    T item;
    HeapArray<T> newheap, newheap2;


    switch (function) {
        case 1:
            cout << "Введите значение добавляемого узла кучи" << endl;
            cin >> item;

            newheap = Arr->GetElement(indexOfHeap1);
            newheap.AddElement(item);
            Arr->Append(newheap);
            break;
        case 2:
            cout << "Введите индекс узла кучи, по которому хотите искать:" << endl;
            cin >> key;
            item = Arr->GetElement(indexOfHeap1).FindElement(key);
            cout << "В узле с таким индексом лежит - \"" << item << "\"" << endl;
            break;
        case 3:
            cout << "Введите индекс узла кучи, который хотите удалить:" << endl;
            cin >> key;

            newheap = Arr->GetElement(indexOfHeap1);
            newheap.DeleteElement(key);
            Arr->Append(newheap);
            break;
        case 4:
            cout << "Введите значение узла кучи, который будет являться корнем извлекаемой кучи:" << endl;
            cin >> item;

            Arr->Append(*(Arr->GetElement(indexOfHeap1).GetTree(item)));
            break;
        case 5:
            newheap = Arr->GetElement(indexOfHeap1);
            newheap2 = Arr->GetElement(indexOfHeap2);

            bol = newheap.ContainTree(newheap2);

            if (bol == 1)
                cout << "Эта куча ЯВЛЯЕТСЯ поддеревом исходноой кучи!!!" << endl;
            else
                cout << "Эта куча НЕ ЯВЛЯЕТСЯ поддеревом исходной кучи!!!" << endl;
            break;
        default:
            break;
    }

    if (function == 1 || function == 3 || function == 4){
        HeapArray<T> resultheap = Arr->GetElement(Arr->GetFilled() - 1);

        int variant;
        cout << "Выберете тип вывода кучи: \n"
             << "\t1: Как массив\n"
             << "\t2: Как дерево\n"
             << "Введите число: ";
        cin >> variant;

        switch (variant){
            case 1:
                PrintHeapArrayMassive(resultheap);
                break;
            case 2:
                PrintHeapArrayBeauty(resultheap);
                break;
            default:
                break;
        }
    }

}

template<class T>
void outputHeapArrayTyped(DynamicArray<HeapArray<T>> *Arr){
    int amountOfHeapArray = Arr->GetFilled();
    int index, variant;
    cout << "В памяти находится \"" << amountOfHeapArray << "\" куч" << endl;
    cout << "Выберете индекс кучи, которую хотите вывести" << endl;
    cin >> index;

    cout << "Выберете тип вывода кучи: \n"
         << "\t1: Как массив\n"
         << "\t2: Как дерево\n"
         << "Введите число: ";
    cin >> variant;

    if (index < 0 || index >= amountOfHeapArray)
        variant = 0;

    switch (variant) {
        case 1:
            PrintHeapArrayMassive(Arr->GetElement(index));
            break;
        case 2:
            PrintHeapArrayBeauty(Arr->GetElement(index));
            break;
        default:
            break;
    }
}


void MenuHeapArray(){
    auto *intArr = new DynamicArray<HeapArray<int>>;
    auto *floatArr = new DynamicArray<HeapArray<float>>;
    auto *complexArr = new DynamicArray<HeapArray<complex<int>>>;


    int operation;
    while(true){
        cout << "Выберете операцию: \n"
             << "\t1: Ввести и запомнить бинарную кучу\n"
             << "\t2: Выполнить операцию над кучей\n"
             << "\t3: Вывести кучу в консоль\n"
             << "\t4: Закончить выполнение программы\n"
             << "Введите число: ";
        cin >> operation;

        if (operation == 4)
            break;

        switch(operation){
            case 1: InputAndSaveHeapArray(intArr, floatArr, complexArr); break;
            case 2: FunctionWithHeapArray(intArr, floatArr, complexArr); break;
            case 3: OutputHeapArray(intArr, floatArr, complexArr); break;
            default: break;
        }
    }
}

void InputAndSaveHeapArray(DynamicArray<HeapArray<int>> *intArr,
                           DynamicArray<HeapArray<float>> *floatArr,
                           DynamicArray<HeapArray<complex<int>>> *complexArr){
    int type = chooseTypeHeapArray();

    switch(type){
        case 1: inputHeapArrayTyped(intArr); break;
        case 2: inputHeapArrayTyped(floatArr); break;
        case 3: inputHeapArrayTyped(complexArr); break;
        default: break;
    }
}

void FunctionWithHeapArray(DynamicArray<HeapArray<int>> *intArr,
                           DynamicArray<HeapArray<float>> *floatArr,
                           DynamicArray<HeapArray<complex<int>>> *complexArr){
    int type = chooseTypeHeapArray();

    switch(type){
        case 1: functionHeapArrayTyped(intArr); break;
        case 2: functionHeapArrayTyped(floatArr); break;
        case 3: functionHeapArrayTyped(complexArr); break;
        default: break;
    }
}

void OutputHeapArray(DynamicArray<HeapArray<int>> *intArr,
                     DynamicArray<HeapArray<float>> *floatArr,
                     DynamicArray<HeapArray<complex<int>>> *complexArr){
    int type = chooseTypeHeapArray();


    switch (type){
        case 1:outputHeapArrayTyped(intArr); break;
        case 2:outputHeapArrayTyped(floatArr); break;
        case 3:outputHeapArrayTyped(complexArr); break;
        default: break;
    }
}

template<class T>
void PrintHeapArrayMassive(HeapArray<T> heap){
    for (int i = 0; i < heap.GetHeapSize(); i++){
        cout << heap.FindElement(i) << "  ";
    }

    cout << endl;
}

template<class T>
void PrintHeapArrayBeauty(HeapArray<T> heap){
    int levels = heap.GetLevels();
    int levelnow = -1;

    for (int i = 0; i < heap.GetHeapSize(); i++){
        int parents = heap.GetAmountOfParent(i);
        if (parents > levelnow){

            if (levelnow == -1)
                levelnow =parents;
            else{
                cout << endl;
                levelnow = parents;
            }
        }

        int prob = 1;
        for (int j = 0; j < levels - parents; j++)
            prob *= 2;

        for (int k = 0; k < prob; k++)
            cout << " ";

        cout << heap.FindElement(i);
    }

    cout << endl;
}








