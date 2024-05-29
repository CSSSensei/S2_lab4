cmake_minimum_required(VERSION 3.17)
project(laboratory_work_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(laboratory_work_4
        main.cpp
        BinaryTree.cpp
        DynamicArray.cpp
        BinaryHeap.cpp
        HeapArray.cpp
        MenuBinaryTree.cpp
        MenuHeapArray.cpp
        menuAll.cpp
        Tests/Test_BinaryTree.cpp
        Tests/Test_HeapArray.cpp
)