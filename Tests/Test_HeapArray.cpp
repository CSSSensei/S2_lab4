//
// Created by pidor on 26.05.2024.
//

#include <cassert>
#include <iostream>
#include "../HeapArray.h"

// Тест для функции добавления элемента и поиска элемента
void testAddElementAndSearchHeapArray() {
    HeapArray<int> heap;
    heap.AddElement(10);
    heap.AddElement(5);
    assert(heap.GetHeapSize() == 2);
    // Проверяем наличие добавленных элементов
    assert(heap.SearchElement(10));
    assert(heap.SearchElement(5));
}

// Тест для функции удаления элемента
void testDeleteElementHeapArray() {
    HeapArray<int> heap;
    heap.AddElement(123456);
    heap.AddElement(5);
    assert(heap.SearchElement(5));
    heap.DeleteElement(5);
    assert(heap.GetHeapSize() == 1);
    assert(!heap.SearchElement(5));
    for (int i = 0; i < 10000; i++){
        heap.AddElement(i);
    }
    assert(heap.GetHeapSize() == 10001);
    for (int i = 0; i < 10000; i++){
        assert(heap.SearchElement(i));
        heap.DeleteElement(i);
        assert(!heap.SearchElement(i));
    }

}

// Тест для функции поиска элемента и создания новой кучи
void testGetTreeHeapArray() {
    HeapArray<int> heap;
    heap.AddElement(10);
    heap.AddElement(5);
    heap.AddElement(15);

    HeapArray<int>* newHeap = heap.GetTree(5);
    // Проверяем наличие элементов в созданной куче
    assert(newHeap->SearchElement(5));
    assert(newHeap->SearchElement(10) == false);
    assert(newHeap->GetHeapSize() == 1);

    delete newHeap;
}

void testHeapArray() {
    testAddElementAndSearchHeapArray();
    testDeleteElementHeapArray();
    testGetTreeHeapArray();
    std::cout << "Heap Array: all tests passed successfully!" << std::endl;
}
