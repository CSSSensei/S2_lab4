#ifndef LABORATORY_WORK_4_HEAPARRAY_H
#define LABORATORY_WORK_4_HEAPARRAY_H

#include <complex>
#include "BinaryHeap.h"

template <class T>
class HeapArray : BinaryHeap<T>{
private:
    int SIZE = 100;
    T* heap;
    int HeapSize;

    int IsParent(int parent, int child){
        int temp = 0;
        if (parent == 0)
            return 1;

        if (parent == child)
            return 0;

        while (child >= parent){
            if (child == parent){
                temp = 1;
                break;
            }
            child = (child - 1)/2;
        }

        return temp;
    }
public:
    class IndexOutOfRange{};
    class WrongItem{};

    HeapArray(){
        HeapSize = 0;
        heap = new T[SIZE];
    }

    void Resize(){
        if (HeapSize == SIZE){
            SIZE += 100;
        }
    }
    void AddElement(T item){
        Resize();
        int i, parent;
        i = HeapSize;
        parent = (i - 1)/2;
        heap[i] = item;

        if (SearchElement(item))
            throw WrongItem();

        while (true){
            if (heap[parent] >= heap[i]){
                break;
            }else{
                T temp = heap[parent];
                heap[parent] = heap[i];
                heap[i] = temp;
                i = parent;
                parent = (i - 1)/2;
            }
        }
        HeapSize ++;
    }
    T FindElement(int key){
        if (key >= HeapSize || key < 0){
            throw IndexOutOfRange();
        }

        return heap[key];
    }
    int SearchElement (const T& item){
        int temp = 0;
        for (int i = 0; i < HeapSize; i++){
            if (item == heap[i])
                temp = 1;
            if (temp == 1)
                break;
        }

        return temp;
    }
    void MaxHeapify(int i){
        int right, left;
        T temp;
        left = 2 * i + 1;
        right = 2 * i + 2;
        if (left < HeapSize){
            if(heap[i] <= heap[left]){
                temp = heap[left];
                heap[left] = heap[i];
                heap[i] = temp;
                MaxHeapify(left);
            }
        }
        if (right < HeapSize){
            if (heap[i] <= heap[right]){
                temp = heap[right];
                heap[right] = heap[i];
                heap[i] = temp;
                MaxHeapify(right);
            }
        }
    }
    void DeleteElement(int key){
        if (key >= HeapSize || key < 0){
            throw IndexOutOfRange();
        }

        for (int i = key; i < HeapSize - 1; i++){
            heap[i] = heap[i + 1];
        }
        //delete heap[HeapSize - 1];
        HeapSize --;

        for (int j = 0 ;j < GetLevels(); j++){
            for (int k = 0; k < HeapSize; k++){
                MaxHeapify(k);
            }
        }
    }
    HeapArray<T>* GetTree(T searched){
        int k = -1;
        for (int i = 0; i < HeapSize; i++){
            if (heap[i] == searched) {
                k = i;
                break;
            }
        }//в k будет находиться индекс искомого элемента

        if (k != -1){
            auto* newHeaparr1 = new T[HeapSize];
            int newHeap1size = 1;
            newHeaparr1[0] = searched;
            for (int i = k + 1; i < HeapSize; i++){
                if (IsParent(k, i) == 1){
                    newHeaparr1[newHeap1size] = heap[i];
                    newHeap1size++;
                }
            }

            T* newHeaparr = new T[newHeap1size];
            for (int i = 0; i < newHeap1size; i ++){
                newHeaparr[i] = newHeaparr1[i];
            }

            auto* newheap = new HeapArray<T>;
            newheap->heap = newHeaparr;
            newheap->HeapSize = newHeap1size;
            newheap->SIZE = SIZE;

            //удаление
            delete[] newHeaparr1;

            return newheap;
        }else
            return nullptr;
    }
    int ContainTree(HeapArray<T> searched){
        if (searched.HeapSize > HeapSize)
            return 0;

        int temp = 1;
        for (int i = 0; i < searched.HeapSize; i++){
            temp *= SearchElement(heap[i]);
        }

        return temp;
    }
    int GetHeapSize(){
        return HeapSize;
}

    int GetLevels(){
        int levels = 0;
        int i = HeapSize;

        if (i == 0)
            return 0;

        while (i != 0){
            levels++;
            i = (i - 1)/2;
        }

        return levels;
    }
    int GetAmountOfParent(int key){
        int parents = 0;

        if (key == 0)
            return 0;

        while (key != 0){
            parents++;
            key = (key - 1)/2;
        }

        return parents;
    }


};


#endif //LABORATORY_WORK_4_HEAPARRAY_H
