cmake_minimum_required(VERSION 3.17)
project(laboratory_work_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(laboratory_work_4 main.cpp BinaryTree.cpp BinaryTree.h DynamicArray.cpp DynamicArray.h BinaryHeap.cpp BinaryHeap.h HeapArray.cpp HeapArray.h MenuBinaryTree.cpp MenuBinaryTree.h MenuHeapArray.cpp MenuHeapArray.h menuAll.cpp menuAll.h
        Tests/Test_BinaryTree.h
        Tests/Test_BinaryTree.cpp
)