#ifndef LABORATORY_WORK_4_DYNAMICARRAY_H
#define LABORATORY_WORK_4_DYNAMICARRAY_H

template <class T>
class DynamicArray {
private:
    T* array;
    int size;
    int filled;
public:
    class IndexOutOfRange {
    };

    //Создание объекта
    DynamicArray(){
        array = nullptr;
        size = 0;
        filled = 0;
    }


    explicit DynamicArray(int newSize) {
        if (newSize < 0) { newSize = 0; }

        array = new T[newSize];
        size = newSize;
        filled = 0;
    }

    //Уадаление объекта
    ~DynamicArray() {
        delete[] array;
        array = nullptr;
        size = 0;
        filled = 0;
    }

    void Delete_DynamicArray() {
        delete[] array;
        array = nullptr;
        size = 0;
        filled = 0;
    }

    //Операции
    void Append(T item) {
        if (filled < 0 || filled > size) {
            filled = 0;
            size = 0;
        }

        if (filled == size) {
            Resize(100);
        }

        array[filled] = item;
        filled += 1;
    };

    void Resize(int newSize) {
        if (newSize < 0) { throw IndexOutOfRange(); }

        if (newSize == 0) { // удаление массива
            delete[] array;
            array = nullptr;
            size = 0;
            return;
        }

        if (newSize == size){return;} // длина не изменится

        if (newSize < size){ // укорачивание массива
            T* new_array = new T[newSize];
            for (int i = 0; i < newSize; i++){
                new_array[i] = array[i];
            }
            delete[] array;
            size = newSize;
            if (filled > newSize){filled = newSize;}
            array = new_array;
            return;
        }

        if (newSize > 0 && size == 0){ //увеличение размера массива и длины
            T* new_array = new T[newSize];
            delete[] array;
            size = newSize;
            array = new_array;
        }

        if (newSize > size){ // увеличение длины
            T* new_array = new T[newSize];
            for (int i = 0; i < filled; i++){
                new_array[i] = array[i];
            }
            delete[] array;
            size = newSize;
            array = new_array;
            return;
        }
    };

    int GetSize(){
        return size;
    }
    int GetFilled(){
        return filled;
    }

    T GetElement(int index) {
        return array[index];
    }

    DynamicArray<T> Concat(const DynamicArray<T> &otherArray) {
        DynamicArray<T> result;
        result.Resize(filled + otherArray.filled);

        for (int i = 0; i < filled; i++) {
            result.Append(array[i]);
        }

        for (int i = 0; i < otherArray.filled; i++) {
            result.Append(otherArray.array[i]);
        }
        return result;
    }

    DynamicArray<T> &operator=(DynamicArray<T> dynamicArray) {
        Resize(dynamicArray.GetSize());
        size = dynamicArray.GetSize();
        filled = dynamicArray.GetFilled();
        for (int i = 0; i < filled; i++){
            array[i] = dynamicArray.array[i];
        }
        return *this;
    }

    DynamicArray<T>* &operator = (DynamicArray<T>* dynamicArray) {
        Resize(dynamicArray->GetSize());
        size = dynamicArray->GetSize();
        filled = dynamicArray->GetFilled();
        for (int i = 0; i < filled; i++){
            array[i] = dynamicArray->array[i];
        }
        return *this;
    }

    T &operator[](int index) {
        if (index < 0 || index >= filled) {
            throw IndexOutOfRange();
        }

        return array[index];
    }
};

#endif //LABORATORY_WORK_4_DYNAMICARRAY_H
