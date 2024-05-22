#ifndef LABORATORY_WORK_4_BINARYTREE_H
#define LABORATORY_WORK_4_BINARYTREE_H
#include "DynamicArray.h"

template<class T, class K>
class BinaryTree {
private:
    typedef struct Info{
        K key;
        T item;
    } Info;
    typedef struct Node{
        Info info;
        Node* left;
        Node* right;
    } Node;

    Info &operator = (Info inf){
        Info Demo;
        Demo.key = inf.key;
        Demo.item = inf.item;
        return Demo;
    }
    Info* &operator = (Info* inf){
        Info* Demo;
        Demo->key = inf->key;
        Demo->item = inf->item;
        return Demo;
    }
    Node &operator = (Node nde){
        Node Demo;
        Demo.info = nde.info;
        Demo.right = nde.right;
        Demo.left = nde.left;
        return Demo;
    }
    Node* &operator = (Node* nde){
        Node* Demo;
        Demo->info = nde->info;
        Demo->right = nde->right;
        Demo->left = nde->left;
        return Demo;
    }

    Node* root;

    void DeleteElementFirst(Node* temp, Node* temparent){
        if (temp == temparent->left)
            temparent->left = nullptr;
        else
            temparent->right = nullptr;

        delete temp;
    }
    void DeleteElementSecond(Node* temp, Node* temparent){
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
    void DeleteElementThird(Node* temp){
        Node* nxttemparent = temp;
        Node* nxttemp = temp->right;
        while(nxttemp->left != nullptr){
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
    void RoundTree(Node* tree, DynamicArray<Info>* arr){
        if (tree != nullptr) {
            RoundTree(tree->left, arr);
            arr->Append(tree->info);
            RoundTree(tree->right, arr);
        }
    }
    int containTree(Node* tree, Node* contree){
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
    class WrongKey{};

    BinaryTree(){
        root = nullptr;
    }
    explicit BinaryTree(Node* newroot){
        root = newroot;
    }

    void AddNote(K key, T item){
        Node *par = root;
        Node *ptr = root;

        auto newnode = new Node;
        newnode->info.key = key;
        newnode->info.item = item;
        newnode->left = nullptr;
        newnode->right = nullptr;


        if(ptr == nullptr)
            root = newnode;
        else {
            while (ptr != nullptr) {
                if (key < ptr->info.key) {
                    par = ptr;
                    ptr = ptr->left;
                } else if (key > ptr->info.key) {
                    par = ptr;
                    ptr = ptr->right;
                }else
                    throw WrongKey();
            }
            if (key < par->info.key)
                par->left = newnode;
            else
                par->right = newnode;
        }
    }
    Node* GetRoot(){
        return root;
    }
    T* SearchElement(K key){
        Node* temp = new Node;
        Node* search = nullptr;
        temp = root;
        T* tmp = new T;
        while(temp != nullptr && search == nullptr){
            if (key < temp->info.key)
                temp = temp->left;
            else if (key > temp->info.key)
                temp = temp->right;
            else
                search = temp;
        }

        if (search != nullptr){
            *tmp = search->info.item;
            return tmp;
        }else
            throw WrongKey();
    }//Поиск элемента по ключу
    bool ContainElement(K key){
        Node* temp = new Node;
        Node* search = nullptr;
        temp = root;
        while(temp != nullptr && search == nullptr){
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
    void DeleteElement(K key){
        Node* temp = new Node;
        Node* search = nullptr;
        Node* temparent = nullptr;
        temp = root;

        while(temp != nullptr && search == nullptr){
            if (key < temp->info.key){
                temparent = temp;
                temp = temp->left;
            }
            else if (key > temp->info.key){
                temparent = temp;
                temp = temp->right;
            }
            else
                search = temp;
        }

        if (search == nullptr)
            throw WrongKey();
        else{
            if (temp->left == nullptr && temp->right == nullptr)
                DeleteElementFirst(temp, temparent);
            else if (temp->left == nullptr || temp->right == nullptr)
                DeleteElementSecond(temp, temparent);
            else if (temp->left != nullptr && temp->right != nullptr)
                DeleteElementThird(temp);
        }
    }//Удаляет узел с этим ключом
    BinaryTree<T, K> GetTree(K key){
        Node* temp = new Node;
        Node* search = nullptr;
        temp = root;
        while(temp != nullptr && search == nullptr){
            if (key < temp->info.key)
                temp = temp->left;
            else if (key > temp->info.key)
                temp = temp->right;
            else
                search = temp;
        }

        if (search != nullptr){
            BinaryTree<T, K> newtree (search);
            return newtree;
        }else
            throw WrongKey();
    }//возвращает поддерево по ключу
    DynamicArray<Info>& RoundTree(){
        auto* arr = new DynamicArray<Info>;
        RoundTree(root, arr);
        return *arr;
    }//возвращает массив с обходом
    int isTree(const BinaryTree<T, K>& tree){
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
    int ContainTree(const BinaryTree<T, K>& tree){
        if (tree.root == nullptr)
            return 1;

        if (root== tree.root)
            return 1;

        if (root == nullptr)
            return 0;

        if (root->info.key == tree.root->info.key) {
            return containTree(root, tree.root);
        }

        if (tree.root->info.key < root->info.key) {
            return BinaryTree<T, K>(root->left).ContainTree(tree);
        }
        else {
            return BinaryTree<T, K>(root->right).ContainTree(tree);
        }
    }//проверяет дерево на вхождение

    /*
    int ContainTree(BinaryTree<T, K> tree, BinaryTree<T, K> searched){
        if (searched.root == nullptr)
            return 1;
        if (tree.root == nullptr)
            return 0;

        if (ContainElement(searched.root->info.key)){
            BinaryTree<T, K> mbtree;
            mbtree = tree.GetTree(searched.root->info.key);
            //mbtree = this->GetTree(searched.root->info.key);

            DynamicArray<Info> arrsearched;
            arrsearched = searched.RoundTree();

            int temp = 1;
            for (int i = 0; i < arrsearched.GetFilled(); i++){
                temp *= mbtree.ContainElement(arrsearched.GetElement(i).key);

                if (mbtree.ContainElement(arrsearched.GetElement(i).key))
                    if(*(mbtree.SearchElement(arrsearched.GetElement(i).key)) != arrsearched.GetElement(i).item)
                        temp = 0;

                if (temp == 0)
                    break;
            }

            BinaryTree<T, K> treeLeft (tree.root->left);
            BinaryTree<T, K> treeRight (tree.root->right);
            BinaryTree<T, K> searchedLeft (searched.root->left);
            BinaryTree<T, K> searchedRight (searched.root->right);

            temp *= ContainTree(treeLeft, searchedLeft);
            temp *= ContainTree(treeRight, searchedRight);

            return temp;
        }else
            return 0;
    }//Вхождение дерева (не работает до конца)
    */

    void Balancing(){
        DynamicArray<Info> arr;
        arr = RoundTree();
        BinaryTree<T, K> newtree;

        Node* newroot = new Node;
        newroot->info = arr.GetElement(arr.GetFilled()/2);
        newroot->right = nullptr;
        newroot->left = nullptr;

        newtree.root = newroot;

        for(int i = 0; i < arr.GetFilled(); i++){
            if (i == arr.GetFilled()/2)
                continue;

            newtree.AddNote((arr.GetElement(i)).key, (arr.GetElement(i)).item);
        }

        root = newtree.GetRoot();
    }
    void DeleteBinaryTree(){
        if(root == nullptr)
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
