//
// Created by pidor on 25.05.2024.
//

#ifndef LABORATORY_WORK_4_TEST_BINARYTREE_H
#define LABORATORY_WORK_4_TEST_BINARYTREE_H
#include "../BinaryTree.h"
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

// Функция для измерения времени вставки элементов в дерево
template<typename T>
double measureInsertionTime(BinaryTree<T, T> &tree, const vector<T> &elements) {
    auto start = chrono::high_resolution_clock::now();

    for (const auto &element: elements) {
        tree.AddNode(element, element);
    }
    //tree.PrintTreeVisual(tree.GetRoot());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> insertTime = end - start;

    return insertTime.count();
}

// Функция для измерения времени поиска элементов в дереве
template<typename T>
double measureSearchTime(BinaryTree<T, T> &tree, const vector<T> &elements) {
    auto start = chrono::high_resolution_clock::now();

    for (const auto &element: elements) {
        assert(element == *tree.SearchElement(element));
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> searchTime = end - start;

    return searchTime.count();
}


void testBinaryTreeFunctions();
void testBinaryTree();
void testContainElement();
void testGetTree();
void testIsTree();
void testContainTree();
void testMapFunction();
void testWhereFunction();

#endif //LABORATORY_WORK_4_TEST_BINARYTREE_H
