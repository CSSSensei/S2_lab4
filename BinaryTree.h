#ifndef LABORATORY_WORK_4_BINARYTREE_H
#define LABORATORY_WORK_4_BINARYTREE_H

#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>
#include "DynamicArray.h"

template<class T, class K>
class BinaryTree {
private:
    typedef struct Info {
        K key;
        T item;
    } Info;
    typedef struct Node {
        Info info;
        int height;
        Node *left;
        Node *right;
    } Node;

    Info &operator=(Info inf) {
        Info Demo;
        Demo.key = inf.key;
        Demo.item = inf.item;
        return Demo;
    }

    Info *&operator=(Info *inf) {
        Info *Demo;
        Demo->key = inf->key;
        Demo->item = inf->item;
        return Demo;
    }

    Node &operator=(Node nde) {
        Node Demo;
        Demo.info = nde.info;
        Demo.right = nde.right;
        Demo.left = nde.left;
        return Demo;
    }

    Node *&operator=(Node *nde) {
        Node *Demo;
        Demo->info = nde->info;
        Demo->right = nde->right;
        Demo->left = nde->left;
        return Demo;
    }

    Node* root;

    void DeleteElementFirst(Node *temp, Node *temparent) {
        if (temp == temparent->left)
            temparent->left = nullptr;
        else
            temparent->right = nullptr;

        delete temp;
    }

    void DeleteElementSecond(Node *temp, Node *temparent) {
        Node* tempchild = nullptr;
        if (temp->left == nullptr)
            tempchild = temp->right;
        else
            tempchild = temp->left;

        if (temp == temparent->left)
            temparent->left = tempchild;
        else
            temparent->right = tempchild;

        delete temp;
    }

    void DeleteElementThird(Node* temp) {
        Node* nxttemparent = temp;
        Node* nxttemp = temp->right;
        while (nxttemp->left != nullptr) {
            nxttemparent = nxttemp;
            nxttemp = nxttemp->left;
        }

        temp->info.key = nxttemp->info.key;
        temp->info.item = nxttemp->info.item;

        if (nxttemp->left == nullptr && nxttemp->right == nullptr)
            DeleteElementFirst(nxttemp, nxttemparent);
        else
            DeleteElementSecond(nxttemp, nxttemparent);
    }

    void RoundTree(Node* tree, DynamicArray<Info>* arr) {
        if (tree != nullptr) {
            RoundTree(tree->left, arr);
            arr->Append(tree->info);
            RoundTree(tree->right, arr);
        }
    }

    int containTree(Node* tree, Node* contree) {
        if (tree == contree)
            return 1;

        if (contree == nullptr)
            return 1;

        if (tree == nullptr)
            return 0;

        if (tree->info.key != contree->info.key || tree->info.item != contree->info.item)
            return 0;

        if (not(containTree(tree->left, contree->left)))
            return 0;

        if (not(containTree(tree->right, contree->right)))
            return 0;

        return 1;
    }

public:
    class WrongKey {
    };

    BinaryTree() {
        root = nullptr;
    }

    explicit BinaryTree(Node *newroot) {
        root = newroot;
    }
    void CreateTreeFromArray(const std::vector<std::pair<K, T>>& elements) {
        for (const auto& element : elements) {
            AddNode(element.first, element.second);
        }
    }

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }


    void AddNode(K key, T item) {
        Node* newNode = new Node;
        newNode->info.key = key;
        newNode->info.item = item;
        newNode->height = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (root == nullptr) {
            root = newNode;
        } else {
            root = InsertNode(root, newNode);
        }
    }

    Node* InsertNode(Node* root_local, Node* newNode) {
        if (root_local == nullptr) {
            return newNode;
        }

        if (newNode->info.key < root_local->info.key) {
            root_local->left = InsertNode(root_local->left, newNode);
        } else if (newNode->info.key > root_local->info.key) {
            root_local->right = InsertNode(root_local->right, newNode);
        } else {
            // Kлюч уже существует
            return root_local;
        }

        root_local->height = 1 + std::max(getHeight(root_local->left), getHeight(root_local->right));

        int balance = getBalance(root_local);

        if (balance > 1 && newNode->info.key < root_local->left->info.key) {
            return rotateRight(root_local);
        }
        else if (balance < -1 && newNode->info.key > root_local->right->info.key) {
            return rotateLeft(root_local);
        }
        else if (balance > 1 && newNode->info.key > root_local->left->info.key) {
            root_local->left = rotateLeft(root_local->left);
            return rotateRight(root_local);
        }
        else if (balance < -1 && newNode->info.key < root_local->right->info.key) {
            root_local->right = rotateRight(root_local->right);
            return rotateLeft(root_local);
        }

        return root_local;
    }

    Node* rotateRight(Node* root_local) {
        Node* newRoot = root_local->left;
        Node* temp = newRoot->right;

        newRoot->right = root_local;
        root_local->left = temp;

        root_local->height = 1 + std::max(getHeight(root_local->left), getHeight(root_local->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    Node* rotateLeft(Node* root_local) {
        Node* newRoot = root_local->right;
        Node* temp = newRoot->left;

        newRoot->left = root_local;
        root_local->right = temp;

        root_local->height = 1 + std::max(getHeight(root_local->left), getHeight(root_local->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    void PrintTreeVisual(Node* root_local, const std::string &prefix_local = "", bool isLeft = true) {
        if (root_local == nullptr) {
            return;
        }

        std::cout << prefix_local;
        std::wcout << (isLeft ? L"├── " : L"└── ");
        std::cout << "[" << root_local->info.key << "]: " << root_local->info.item << std::endl;

        PrintTreeVisual(root_local->left, prefix_local + (isLeft ? "|    " : "     "), true);
        PrintTreeVisual(root_local->right, prefix_local + (isLeft ? "|    " : "     "), false);
    }

    Node *GetRoot() {
        return root;
    }

    T* SearchElement(K key) {
        Node* temp = new Node;
        Node* search = nullptr;
        temp = root;
        T *tmp = new T;
        while (temp != nullptr && search == nullptr) {
            if (key < temp->info.key)
                temp = temp->left;
            else if (key > temp->info.key)
                temp = temp->right;
            else
                search = temp;
        }

        if (search != nullptr) {
            *tmp = search->info.item;
            return tmp;
        } else
            throw WrongKey();
    }//Поиск элемента по ключу
    bool ContainElement(K key) {
        Node* temp = new Node;
        Node* search = nullptr;
        temp = root;
        while (temp != nullptr && search == nullptr) {
            if (key < temp->info.key)
                temp = temp->left;
            else if (key > temp->info.key)
                temp = temp->right;
            else
                search = temp;
        }

        if (search != nullptr)
            return true;
        else
            return false;
    }//Вхождение элемента
    void DeleteElement(K key) {
        Node* temp = new Node;
        Node* search = nullptr;
        Node* temparent = nullptr;
        temp = root;

        while (temp != nullptr && search == nullptr) {
            if (key < temp->info.key) {
                temparent = temp;
                temp = temp->left;
            } else if (key > temp->info.key) {
                temparent = temp;
                temp = temp->right;
            } else
                search = temp;
        }

        if (search == nullptr)
            throw WrongKey();
        else {
            if (temp->left == nullptr && temp->right == nullptr)
                DeleteElementFirst(temp, temparent);
            else if (temp->left == nullptr || temp->right == nullptr)
                DeleteElementSecond(temp, temparent);
            else if (temp->left != nullptr && temp->right != nullptr)
                DeleteElementThird(temp);
        }
    }//Удаляет узел с этим ключом

    BinaryTree<T, K> GetTree(K key) {
        Node* temp = new Node;
        Node* search = nullptr;
        temp = root;
        while (temp != nullptr && search == nullptr) {
            if (key < temp->info.key)
                temp = temp->left;
            else if (key > temp->info.key)
                temp = temp->right;
            else
                search = temp;
        }

        if (search != nullptr) {
            BinaryTree<T, K> newtree(search);
            return newtree;
        } else
            throw WrongKey();
    }//возвращает поддерево по ключу

    DynamicArray<Info>& RoundTree() {
        auto* arr = new DynamicArray<Info>;
        RoundTree(root, arr);
        return *arr;
    }//возвращает массив с обходом
    int isTree(const BinaryTree<T, K> &tree) {
        if (root == tree.root)
            return 1;

        if (root == nullptr || tree.root == nullptr)
            return 0;

        if (root->info.key != tree.root->info.key || root->info.item != tree.root->info.item)
            return 0;

        if (not(BinaryTree<T, K>(root->left).isTree(BinaryTree<T, K>(tree.root->left))))
            return 0;

        if (not(BinaryTree<T, K>(root->right).isTree(BinaryTree<T, K>(tree.root->right))))
            return 0;

        return 1;
    }//Сравнивает дерево
    int ContainTree(const BinaryTree<T, K> &tree) {
        if (tree.root == nullptr)
            return 1;

        if (root == tree.root)
            return 1;

        if (root == nullptr)
            return 0;

        if (root->info.key == tree.root->info.key) {
            return containTree(root, tree.root);
        }

        if (tree.root->info.key < root->info.key) {
            return BinaryTree<T, K>(root->left).ContainTree(tree);
        } else {
            return BinaryTree<T, K>(root->right).ContainTree(tree);
        }
    }//проверяет дерево на вхождение


    void Balancing() {
        std::wcout << L"Топ-10 бесполезных функций в АВЛ-дереве" << std::endl;
    }


    BinaryTree<T, K> map(T(*func)(T)) {
        BinaryTree<T, K> newTree;
        mapHelper(this->root, func, newTree);
        return newTree;
    }


    void mapHelper(Node* root_local, T(*func)(T), BinaryTree<T, K>& newTree) {
        if (root_local == nullptr) {
            return;
        }

        newTree.AddNode(root_local->info.key, func(root_local->info.item));

        mapHelper(root_local->left, func, newTree);
        mapHelper(root_local->right, func, newTree);
    }

    BinaryTree<T, K> where(bool(*predicate)(T)) {
        BinaryTree<T, K> newTree;
        whereHelper(this->root, predicate, newTree);
        return newTree;
    }

    void whereHelper(Node* root_local, bool(*predicate)(T), BinaryTree<T, K>& newTree) {
        if (root_local == nullptr) {
            return;
        }

        if (predicate(root_local->info.item)) {
            newTree.AddNode(root_local->info.key, root_local->info.item);
        }

        whereHelper(root_local->left, predicate, newTree);
        whereHelper(root_local->right, predicate, newTree);
    }

    BinaryTree<T, K> mergeTrees(BinaryTree<T, K>& tree) {
        DynamicArray<Info> arr1 = this->RoundTree();
        DynamicArray<Info> arr2 = tree.RoundTree();
        DynamicArray<Info> mergedArr = arr1.Concat(arr2);

        BinaryTree<T, K> mergedTree;
        for (int i = 0; i < mergedArr.GetFilled(); i++) {
            mergedTree.AddNode(mergedArr[i].key, mergedArr[i].item);
        }

        return mergedTree;
    }

    void Traversal_KLP_0(){
        Traversal_KLP_Tree_0(root);
    }

    void Traversal_KLP_Tree_0(Node* tree){
        if (tree != nullptr) {
            std::cout << "[" << tree->info.key << "]: " << tree->info.item << ", "; // Корень
            Traversal_KLP_Tree_0(tree->left); // Лево
            Traversal_KLP_Tree_0(tree->right); // Право
        }
    }

    void Traversal_KPL_0(){
        Traversal_KPL_Tree_0(root);
    }

    void Traversal_KPL_Tree_0(Node* tree){
        if (tree != nullptr) {
            std::cout << "[" << tree->info.key << "]: " << tree->info.item << ", "; // Корень
            Traversal_KPL_Tree_0(tree->right); // Право
            Traversal_KPL_Tree_0(tree->left); // Лево
        }
    }

    void Traversal_LPK_0(){
        Traversal_LPK_Tree_0(root);
    }

    void Traversal_LPK_Tree_0(Node* tree){
        if (tree != nullptr) {
            Traversal_LPK_Tree_0(tree->left); // Лево
            Traversal_LPK_Tree_0(tree->right); // Право
            std::cout << "[" << tree->info.key << "]: " << tree->info.item << ", "; // Корень
        }
    }

    void Traversal_LKP_0(){
        Traversal_LKP_Tree_0(root);
    }

    void Traversal_LKP_Tree_0(Node* tree){
        if (tree != nullptr) {
            Traversal_LKP_Tree_0(tree->left); // Лево
            std::cout << "[" << tree->info.key << "]: " << tree->info.item << ", "; // Корень
            Traversal_LKP_Tree_0(tree->right); // Право
        }
    }

    void Traversal_PLK_0(){
        Traversal_PLK_Tree_0(root);
    }

    void Traversal_PLK_Tree_0(Node* tree){
        if (tree != nullptr) {
            std::cout << "[" << tree->info.key << "]: " << tree->info.item << ", "; // Корень
            Traversal_PLK_Tree_0(tree->left); // Лево
            Traversal_PLK_Tree_0(tree->right); // Право
        }
    }

    void Traversal_PKL_0(){
        Traversal_PKL_Tree_0(root);
    }

    void Traversal_PKL_Tree_0(Node* tree){
        if (tree != nullptr) {
            std::cout << "[" << tree->info.key << "]: " << tree->info.item << ", "; // Корень
            Traversal_PKL_Tree_0(tree->right); // Право
            Traversal_PKL_Tree_0(tree->left); // Лево
        }
    }

    void DeleteBinaryTree() {
        if (root == nullptr)
            return;

        if (root->left != nullptr)
            BinaryTree<T, K>(root->left).DeleteBinaryTree();

        if (root->right != nullptr)
            BinaryTree<T, K>(root->right).DeleteBinaryTree();

        delete root;
        root = nullptr;
    }
};


#endif //LABORATORY_WORK_4_BINARYTREE_H
