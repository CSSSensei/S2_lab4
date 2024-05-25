//
// Created by pidor on 26.05.2024.
//

#include "Test_BinaryTree.h"

void testBinaryTreeFunctions() {
    vector<int> sizes = {10000, 100000, 1000000, 10000000};
    vector<double> insertionTimes;
    vector<double> searchTimes;
    for (int size: sizes) {
        vector<int> elements(size);
        for (int i = 0; i < size; i++) {
            elements[i] = i;
        }
        shuffle(elements.begin(), elements.end(), mt19937(random_device()()));
        BinaryTree<int, int> tree;
        double insertionTime = measureInsertionTime(tree, elements);
        insertionTimes.push_back(insertionTime);
        double searchtime = measureSearchTime(tree, elements);
        tree.DeleteBinaryTree();
        searchTimes.push_back(searchtime);
        cout << "Size: " << size << ", Time of insertion: " << insertionTime << "s, Search time: " << searchtime
             << "s\n";
    }
}

void testContainElement() {
    BinaryTree<int, int> binaryTree;
    binaryTree.AddNode(5, 50);
    binaryTree.AddNode(3, 30);
    binaryTree.AddNode(8, 80);
    binaryTree.AddNode(2, 20);
    assert(binaryTree.ContainElement(3) == true);
    assert(binaryTree.ContainElement(10) == false);
    assert(binaryTree.ContainElement(3) == true);
    assert(binaryTree.ContainElement(8) == true);
    assert(binaryTree.ContainElement(2) == true);
    binaryTree.DeleteElement(5);
    assert(binaryTree.ContainElement(5) == false);
    BinaryTree<int, int> emptyTree;
    assert(emptyTree.ContainElement(5) == false);
    binaryTree.DeleteBinaryTree();
}

void testGetTree() {
    // Create a new BinaryTree object and add some nodes for testing
    BinaryTree<int, int> binaryTree;
    binaryTree.AddNode(5, 50);
    binaryTree.AddNode(3, 30);
    binaryTree.AddNode(8, 80);
    binaryTree.AddNode(2, 20);
    binaryTree.AddNode(6, 60);

    // Testing when the key to search is present in the tree
    BinaryTree<int, int> resultTree1 = binaryTree.GetTree(3);
    assert(resultTree1.ContainElement(3) == true);
    assert(resultTree1.ContainElement(5) == false);
    assert(resultTree1.ContainElement(2) == true);
    assert(resultTree1.ContainElement(6) == false);
    assert(binaryTree.ContainTree(resultTree1) == 1);
    BinaryTree<int, int> resultTree2 = binaryTree.GetTree(8);
    assert(resultTree2.ContainElement(3) == false);
    assert(resultTree2.ContainElement(5) == false);
    assert(resultTree2.ContainElement(8) == true);
    assert(resultTree2.ContainElement(6) == true);
    assert(resultTree2.ContainElement(5) == false);
    binaryTree.DeleteBinaryTree();
}

void testIsTree() {
    BinaryTree<int, int> binaryTree1;
    binaryTree1.AddNode(5, 50);
    binaryTree1.AddNode(3, 30);
    binaryTree1.AddNode(8, 80);

    BinaryTree<int, int> binaryTree2;
    binaryTree2.AddNode(5, 50);
    binaryTree2.AddNode(3, 30);

    BinaryTree<int, int> binaryTree3;
    binaryTree3.AddNode(5, 50);
    binaryTree3.AddNode(3, 30);
    binaryTree3.AddNode(8, 80);

    // Testing when comparing the same trees should return 1
    assert(binaryTree1.isTree(binaryTree1) == 1);

    // Testing when comparing two identical trees should return 1
    assert(binaryTree1.isTree(binaryTree3) == 1);

    // Testing when comparing two different trees should return 0
    assert(binaryTree1.isTree(binaryTree2) == 0);

    // Testing when comparing an empty tree with a non-empty tree should return 0
    BinaryTree<int, int> emptyTree;
    assert(binaryTree1.isTree(emptyTree) == 0);

    // Testing when comparing two empty trees should return 1
    assert(emptyTree.isTree(emptyTree) == 1);
    binaryTree1.DeleteBinaryTree();
    binaryTree2.DeleteBinaryTree();
    binaryTree3.DeleteBinaryTree();
}

void testContainTree() {
    BinaryTree<int, int> binaryTree1;
    binaryTree1.AddNode(5, 50);
    binaryTree1.AddNode(3, 30);
    binaryTree1.AddNode(8, 80);

    BinaryTree<int, int> binaryTree2;
    binaryTree2.AddNode(3, 30);
    binaryTree2.AddNode(2, 20);
    binaryTree2.AddNode(4, 40);

    BinaryTree<int, int> binaryTree3;
    binaryTree3.AddNode(8, 30);
    binaryTree3.AddNode(100, 1);

    BinaryTree<int, int> binaryTree4;
    binaryTree4.AddNode(3, 30);
    binaryTree4.AddNode(5, 50);
    binaryTree4.AddNode(8, 30);
    binaryTree4.AddNode(4, 80);
    binaryTree4.AddNode(100, 1);
    // Testing when checking a tree containing itself should return 1
    assert(binaryTree1.ContainTree(binaryTree1) == 1);

    // Testing when checking a tree contained in another tree should return 0
    assert(binaryTree1.ContainTree(binaryTree2) == 0);

    // Testing when checking a tree not contained in another tree should return 0
    assert(binaryTree1.ContainTree(binaryTree3) == 0);
    assert(binaryTree4.ContainTree(binaryTree3) == 1);

    // Testing when checking an empty tree should return 1
    BinaryTree<int, int> emptyTree;
    assert(emptyTree.ContainTree(binaryTree1) == 0);
    binaryTree1.DeleteBinaryTree();
    binaryTree2.DeleteBinaryTree();
    binaryTree3.DeleteBinaryTree();
    binaryTree4.DeleteBinaryTree();

}

void testMapFunction() {
    BinaryTree<int, int> binaryTree;
    binaryTree.AddNode(5, 10);
    binaryTree.AddNode(3, 6);
    binaryTree.AddNode(7, 14);

    // Lambda function to square the item value
    auto squareMapper = [](int value) {
        return value * value;
    };

    // Calling the map function with the squareMapper lambda
    BinaryTree<int, int> squaredTree = binaryTree.map(squareMapper);

    // Asserting the mapped values are correct
    assert(*squaredTree.SearchElement(5) == 100);
    assert(*squaredTree.SearchElement(3) == 36);
    assert(*squaredTree.SearchElement(7) == 196);

    // Lambda function to add 5 to the item value
    auto addFiveMapper = [](int value) {
        return value + 5;
    };

    // Calling the map function with the addFiveMapper lambda
    BinaryTree<int, int> modifiedTree = binaryTree.map(addFiveMapper);

    // Asserting the modified values are correct
    assert(*modifiedTree.SearchElement(5) == 15);
    assert(*modifiedTree.SearchElement(3) == 11);
    assert(*modifiedTree.SearchElement(7) == 19);

    binaryTree.DeleteBinaryTree();
    squaredTree.DeleteBinaryTree();
    modifiedTree.DeleteBinaryTree();
}

void testWhereFunction() {
    // Creating a BinaryTree and adding some nodes
    BinaryTree<int, int> binaryTree;
    binaryTree.AddNode(5, 10);
    binaryTree.AddNode(3, 6);
    binaryTree.AddNode(7, 15);
    binaryTree.AddNode(8, 3);

    // Testing where function with lambda functions as predicates
    BinaryTree<int, int> evenNumbersTree = binaryTree.where([](int num) { return num % 2 == 0; });
    BinaryTree<int, int> greaterThanTenTree = binaryTree.where([](int num) { return num >= 10; });

    // Asserting the values in the new trees are as expected
    assert(*evenNumbersTree.SearchElement(5) == 10);
    assert(*evenNumbersTree.SearchElement(3) == 6);
    try { evenNumbersTree.SearchElement(7); }
    catch (const BinaryTree<int, int>::WrongKey &e) {
        assert(true);
    }
    try { evenNumbersTree.SearchElement(8); }
    catch (const BinaryTree<int, int>::WrongKey &e) {
        assert(true);
    }

    assert(*greaterThanTenTree.SearchElement(5) == 10);
    try { greaterThanTenTree.SearchElement(3); }
    catch (const BinaryTree<int, int>::WrongKey &e) {
        assert(true);
    }
    assert(*greaterThanTenTree.SearchElement(7) == 15);
    try { greaterThanTenTree.SearchElement(8); }
    catch (const BinaryTree<int, int>::WrongKey &e) {
        assert(true);
    }
    binaryTree.DeleteBinaryTree();
    evenNumbersTree.DeleteBinaryTree();
    greaterThanTenTree.DeleteBinaryTree();
    // 8 -> 3 (not greater than 10)

}


void testBinaryTree() {
    //testBinaryTreeFunctions();
    testContainElement();
    testGetTree();
    testIsTree();
    testContainTree();
    testMapFunction();
    testWhereFunction();
    cout << "BinaryTree: all test passed successfully\n";
}