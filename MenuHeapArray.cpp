#include <limits>
#include "MenuHeapArray.h"
#include <complex>

template<typename T>
T getNumberInput() {
    T value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::wcout << L"Неверный тип данных.\n";
        } else {
            break;
        }
    }
    return value;
}

std::complex<int> getComplexNumberInput() {
    std::complex<int> value;
    int real, imaginary;

    std::cout << "Enter real part:";
    real = getNumberInput<int>();

    std::cout << "Enter imaginary part:";
    imaginary = getNumberInput<int>();

    value = std::complex<int>(real, imaginary);
    return value;
}


int chooseTypeHeapArray() {
    int type;
    wcout << L"Выберете тип, с которым будете работать: \n"
          << L"\t1: int\n"
          << L"\t2: float\n"
          << L"\t3: complex\n"
          << L"Введите число:";
    type = getNumberInput<int>();

    return type;
}

int chooseFunctionHeapArray() {
    int func;
    wcout << L"Выберете функцию, которую нужно произвести над бинарной кучей: \n"
          << L"\t1: Добавление узла\n"
          << L"\t2: Поиск элемента по ключу\n"
          << L"\t3: Удаление узла\n"
          << L"\t4: Извлечение поддерева\n"
          << L"\t5: Поиск на вхождение поддерева\n"
          << L"Введите число:";
    func = getNumberInput<int>();

    return func;
}


template<class T>
void inputHeapArrayTyped(DynamicArray<HeapArray<T>>* Arr) {
    HeapArray<T> addingHeap;

    wcout << L"Введите колличество узлов в куче" << endl;
    int count;
    count = getNumberInput<int>();

    for (int i = 0; i < count; i++) {
        T item;
        wcout << L"Введите значение добавляемого \"" << i << L"\" узла кучи" << endl;
        item = getNumberInput<T>();

        addingHeap.AddElement(item);
    }

    Arr->Append(addingHeap);
}

void inputComplexArrayTyped(DynamicArray<HeapArray<complex<int>>>* Arr) {
    HeapArray<complex<int>> addingHeap;

    wcout << L"Введите колличество узлов в куче" << endl;
    int count;
    count = getNumberInput<int>();

    for (int i = 0; i < count; i++) {
        complex<int> item;
        wcout << L"Введите значение добавляемого \"" << i << L"\" узла кучи" << endl;
        item = getComplexNumberInput();

        addingHeap.AddElement(item);
    }

    Arr->Append(addingHeap);
}


template<class T>
void functionHeapArrayTyped(DynamicArray<HeapArray<T>>* Arr) {
    int function = chooseFunctionHeapArray();
    int amountOfHeapArray = Arr->GetFilled(), indexOfHeap1 = -1, indexOfHeap2 = -1;

    if (function == 5) {
        wcout << L"В памяти находится \"" << amountOfHeapArray << L"\" куч" << endl;
        wcout << L"Выберете индекс кучи, которую хотите проверить на вхождение:" << endl;
        indexOfHeap1 = getNumberInput<int>();
        wcout << L"Выберете индекс кучи, вхождение которой нужно проверять:" << endl;
        indexOfHeap2 = getNumberInput<int>();
        if (indexOfHeap1 >= amountOfHeapArray || indexOfHeap1 < 0 || indexOfHeap2 >= amountOfHeapArray ||
            indexOfHeap2 < 0) {
            wcout << L"Кучи с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    } else {
        wcout << L"В памяти находится \"" << amountOfHeapArray << L"\" куч" << endl;
        wcout << L"Выберете индекс кучи, с которой хотите работать:" << endl;
        indexOfHeap1 = getNumberInput<int>();
        if (indexOfHeap1 >= amountOfHeapArray || indexOfHeap1 < 0) {
            wcout << L"Кучи с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    }

    int key;
    bool flag;
    T item;
    HeapArray<T> newheap, newheap2;


    switch (function) {
        case 1:
            wcout << L"Введите значение добавляемого узла кучи" << endl;
            item = getNumberInput<T>();

            newheap = Arr->GetElement(indexOfHeap1);
            newheap.AddElement(item);
            Arr->Append(newheap);
            break;
        case 2:
            wcout << L"Введите индекс узла кучи, по которому хотите искать:" << endl;
            key = getNumberInput<int>();
            if (key < 0 || key >= Arr->GetElement(indexOfHeap1).GetHeapSize()){
                wcout << L"Неправильный индекс. В куче находится " << Arr->GetElement(indexOfHeap1).GetHeapSize() << L" элемента(-ов)" << endl;
                break;
            }
            item = Arr->GetElement(indexOfHeap1).FindElement(key);
            wcout << L"В узле с таким индексом лежит - \"" << item << L"\"" << endl;
            break;
        case 3:
            wcout << L"Введите индекс узла кучи, который хотите удалить:" << endl;
            key = getNumberInput<int>();
            if (key < 0 || key >= Arr->GetElement(indexOfHeap1).GetHeapSize()){
                wcout << L"Неправильный индекс. В куче находится " << Arr->GetElement(indexOfHeap1).GetHeapSize() << L" элемента(-ов)" << endl;
                break;
            }
            newheap = Arr->GetElement(indexOfHeap1);
            newheap.DeleteElementByKey(key);
            Arr->Append(newheap);
            break;
        case 4:
            wcout << L"Введите значение узла кучи, который будет являться корнем извлекаемой кучи:" << endl;
            item = getNumberInput<T>();

            Arr->Append(*(Arr->GetElement(indexOfHeap1).GetTree(item)));
            break;
        case 5:
            newheap = Arr->GetElement(indexOfHeap1);
            newheap2 = Arr->GetElement(indexOfHeap2);

            flag = newheap.ContainTree(newheap2);

            if (flag)
                wcout << L"Эта куча ЯВЛЯЕТСЯ поддеревом исходноой кучи!!!" << endl;
            else
                wcout << L"Эта куча НЕ ЯВЛЯЕТСЯ поддеревом исходной кучи!!!" << endl;
            break;
        default:
            break;
    }

    if (function == 1 || function == 3 || function == 4) {
        HeapArray<T> resultheap = Arr->GetElement(Arr->GetFilled() - 1);

        int variant;
        wcout << L"Выберете тип вывода кучи: \n"
              << L"\t1: Как массив\n"
              << L"\t2: Как дерево\n"
              << L"Введите число:";
        variant = getNumberInput<int>();

        switch (variant) {
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

void functionComplex(DynamicArray<HeapArray<complex<int>>>* Arr) {
    int function = chooseFunctionHeapArray();
    int amountOfHeapArray = Arr->GetFilled(), indexOfHeap1 = -1, indexOfHeap2 = -1;

    if (function == 5) {
        wcout << L"В памяти находится \"" << amountOfHeapArray << L"\" куч" << endl;
        wcout << L"Выберете индекс кучи, которую хотите проверить на вхождение:" << endl;
        indexOfHeap1 = getNumberInput<int>();
        wcout << L"Выберете индекс кучи, вхождение которой нужно проверять:" << endl;
        indexOfHeap2 = getNumberInput<int>();
        if (indexOfHeap1 >= amountOfHeapArray || indexOfHeap1 < 0 || indexOfHeap2 >= amountOfHeapArray ||
            indexOfHeap2 < 0) {
            wcout << L"Кучи с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    } else {
        wcout << L"В памяти находится \"" << amountOfHeapArray << L"\" куч" << endl;
        wcout << L"Выберете индекс кучи, с которой хотите работать:" << endl;
        indexOfHeap1 = getNumberInput<int>();
        if (indexOfHeap1 >= amountOfHeapArray || indexOfHeap1 < 0) {
            wcout << L"Кучи с таким индексом нет в памяти!!!" << endl;
            function = -1;
        }
    }

    int key;
    bool flag;
    complex<int> item;
    HeapArray<complex<int>> newheap, newheap2;

    switch (function) {
        case 1:
            wcout << L"Введите значение добавляемого узла кучи" << endl;
            item = getComplexNumberInput();

            newheap = Arr->GetElement(indexOfHeap1);
            newheap.AddElement(item);
            Arr->Append(newheap);
            break;
        case 2:
            wcout << L"Введите индекс узла кучи, по которому хотите искать:" << endl;
            key = getNumberInput<int>();
            item = Arr->GetElement(indexOfHeap1).FindElement(key);
            wcout << L"В узле с таким индексом лежит - \"" << item << L"\"" << endl;
            break;
        case 3:
            wcout << L"Введите индекс узла кучи, который хотите удалить:" << endl;
            key = getNumberInput<int>();

            newheap = Arr->GetElement(indexOfHeap1);
            newheap.DeleteElementByKey(key);
            Arr->Append(newheap);
            break;
        case 4:
            wcout << L"Введите значение узла кучи, который будет являться корнем извлекаемой кучи:" << endl;
            item = getComplexNumberInput();

            Arr->Append(*(Arr->GetElement(indexOfHeap1).GetTree(item)));
            break;
        case 5:
            newheap = Arr->GetElement(indexOfHeap1);
            newheap2 = Arr->GetElement(indexOfHeap2);

            flag = newheap.ContainTree(newheap2);

            if (flag)
                wcout << L"Эта куча ЯВЛЯЕТСЯ поддеревом исходноой кучи!!!" << endl;
            else
                wcout << L"Эта куча НЕ ЯВЛЯЕТСЯ поддеревом исходной кучи!!!" << endl;
            break;
        default:
            break;
    }

    if (function == 1 || function == 3 || function == 4) {
        HeapArray<complex<int>> resultheap = Arr->GetElement(Arr->GetFilled() - 1);

        int variant;
        wcout << L"Выберете тип вывода кучи: \n"
              << L"\t1: Как массив\n"
              << L"\t2: Как дерево\n"
              << L"Введите число:";
        variant = getNumberInput<int>();

        switch (variant) {
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
void outputHeapArrayTyped(DynamicArray<HeapArray<T>>* Arr) {
    int amountOfHeapArray = Arr->GetFilled();
    int index, variant;
    wcout << L"В памяти находится \"" << amountOfHeapArray << L"\" куч" << endl;
    wcout << L"Выберете индекс кучи, которую хотите вывести" << endl;
    index = getNumberInput<int>();

    wcout << L"Выберете тип вывода кучи: \n"
          << L"\t1: Как массив\n"
          << L"\t2: Как дерево\n"
          << L"Введите число:";
    variant = getNumberInput<int>();

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


void MenuHeapArray() {
    auto* intArr = new DynamicArray<HeapArray<int>>;
    auto* floatArr = new DynamicArray<HeapArray<float>>;
    auto* complexArr = new DynamicArray<HeapArray<complex<int>>>;

    int operation;
    while (true) {
        wcout << L"Выберете операцию: \n"
              << L"\t1: Ввести и запомнить бинарную кучу\n"
              << L"\t2: Выполнить операцию над кучей\n"
              << L"\t3: Вывести кучу в консоль\n"
              << L"\t4: Закончить выполнение программы\n"
              << L"Введите число:";
        operation = getNumberInput<int>();

        if (operation == 4)
            break;

        switch (operation) {
            case 1:
                InputAndSaveHeapArray(intArr, floatArr, complexArr);
                break;
            case 2:
                FunctionWithHeapArray(intArr, floatArr, complexArr);
                break;
            case 3:
                OutputHeapArray(intArr, floatArr, complexArr);
                break;
            default:
                break;
        }
    }
}

void InputAndSaveHeapArray(DynamicArray<HeapArray<int>>* intArr,
                           DynamicArray<HeapArray<float>>* floatArr,
                           DynamicArray<HeapArray<complex<int>>>* complexArr) {
    int type = chooseTypeHeapArray();

    switch (type) {
        case 1:
            inputHeapArrayTyped(intArr);
            break;
        case 2:
            inputHeapArrayTyped(floatArr);
            break;
        case 3:
            inputComplexArrayTyped(complexArr);
            break;
        default:
            break;
    }
}

void FunctionWithHeapArray(DynamicArray<HeapArray<int>>* intArr,
                           DynamicArray<HeapArray<float>>* floatArr,
                           DynamicArray<HeapArray<complex<int>>>* complexArr) {
    int type = chooseTypeHeapArray();

    switch (type) {
        case 1:
            functionHeapArrayTyped(intArr);
            break;
        case 2:
            functionHeapArrayTyped(floatArr);
            break;
        case 3:
            functionComplex(complexArr);
            break;
        default:
            break;
    }
}

void OutputHeapArray(DynamicArray<HeapArray<int>>* intArr,
                     DynamicArray<HeapArray<float>>* floatArr,
                     DynamicArray<HeapArray<complex<int>>>* complexArr) {
    int type = chooseTypeHeapArray();

    switch (type) {
        case 1:
            outputHeapArrayTyped(intArr);
            break;
        case 2:
            outputHeapArrayTyped(floatArr);
            break;
        case 3:
            outputHeapArrayTyped(complexArr);
            break;
        default:
            break;
    }
}


template<class T>
void PrintHeapArrayMassive(HeapArray<T> heap) {
    for (int i = 0; i < heap.GetHeapSize(); i++) {
        cout << heap.FindElement(i) << "  ";
    }
    cout << endl;
}


template<class T>
void PrintHeapArrayBeauty(HeapArray<T> heap) {
    heap.PrintHeapVisual(heap);
}







