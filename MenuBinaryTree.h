#ifndef LABORATORY_WORK_4_MENUBINARYTREE_H
#define LABORATORY_WORK_4_MENUBINARYTREE_H
#include <complex>
#include <iostream>
#include "BinaryTree.h"
#include "DynamicArray.h"

using namespace std;

int chooseTypeBinaryTree();
int chooseFunctionBinaryTree();

template<class T, class K>
void inputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>>* Arr);
void inputComplexBinaryTreeTyped(DynamicArray<BinaryTree<complex<int>, int>>* Arr);

template<class T, class K>
void functionBinaryTreeTyped(DynamicArray<BinaryTree<T, K>>* Arr);

template<class T, class K>
void outputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>>*  Arr);

void InputAndSaveBinaryTree(DynamicArray<BinaryTree<int, int>>* intArr,
                            DynamicArray<BinaryTree<float, float>>* floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>>* complexArr);
void MenuBinaryTree();

void FunctionWithBinaryTree(DynamicArray<BinaryTree<int, int>>* intArr,
                            DynamicArray<BinaryTree<float, float>>* floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>>* complexArr);

void OutputBinaryTree(DynamicArray<BinaryTree<int, int>>* intArr,
                      DynamicArray<BinaryTree<float, float>>* floatArr,
                      DynamicArray<BinaryTree<complex<int>, int>>* complexArr);

template<class T, class K>
void PrintBinaryTreeMassive(BinaryTree<T, K> tree){
    std::wcout << L"КЛП: ";
    tree.Traversal_KLP_0();
    std::wcout << L"\nКПЛ: ";
    tree.Traversal_KPL_0();
    std::wcout << L"\nЛКП: ";
    tree.Traversal_LKP_0();
    std::wcout << L"\nЛПК: ";
    tree.Traversal_LPK_0();
    std::wcout << L"\nПКЛ: ";
    tree.Traversal_PKL_0();
    std::wcout << L"\nПЛК: ";
    tree.Traversal_PLK_0();

}

template <class T, class K>
void PrintBinaryTreeBeauty(BinaryTree<T, K> tree) {
    auto root = tree.GetRoot(); // Получаем указатель на корневой узел
    tree.PrintTreeVisual(root);
}



template<class T>
complex<T> &operator < (complex<T> a, complex<T> b){
    T modA = a.imag() * a.imag() + a.real() * a.real();
    T modB = b.imag() * b.imag() + b.real() * b.real();
    if (modA < modB)
        return true;
    else
        return false;
}

#endif //LABORATORY_WORK_4_MENUBINARYTREE_H
