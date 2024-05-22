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
void inputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> *Arr);

template<class T, class K>
void functionBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> *Arr);

template<class T, class K>
void outputBinaryTreeTyped(DynamicArray<BinaryTree<T, K>> * Arr);

void InputAndSaveBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                            DynamicArray<BinaryTree<float, float>> *floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>> *complexArr);
void MenuBinaryTree();

void FunctionWithBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                            DynamicArray<BinaryTree<float, float>> *floatArr,
                            DynamicArray<BinaryTree<complex<int>, int>> *complexArr);

void OutputBinaryTree(DynamicArray<BinaryTree<int, int>> *intArr,
                      DynamicArray<BinaryTree<float, float>> *floatArr,
                      DynamicArray<BinaryTree<complex<int>, int>> *complexArr);

template<class T, class K>
void PrintBinaryTreeMassive(BinaryTree<T, K> tree){
    auto root = tree.GetRoot();
    if (root == nullptr)
        return;

    cout << "[Ключ: " << root->info.key << " Значение: " << root->info.item << "]";
    BinaryTree<T, K> treeLeft (root->left);
    BinaryTree<T, K> treeRight (root->right);
    PrintBinaryTreeMassive(treeLeft);
    PrintBinaryTreeMassive(treeRight);
}

template<class T, class K>
void PrintBinaryTreeBeauty(BinaryTree<T, K> tree, int prob){
    auto root = tree.GetRoot();
    if (root == nullptr)
        return;

    BinaryTree<T, K> treeRight (root->right);
    PrintBinaryTreeBeauty(treeRight, prob + 1);

    for (int i = 0; i < prob; i++)
        cout << "  ";
    cout << root->info.key << endl;

    BinaryTree<T, K> treeLeft (root->left);
    PrintBinaryTreeBeauty(treeLeft, prob + 1);
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
