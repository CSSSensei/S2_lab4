#ifndef LABORATORY_WORK_4_MENUHEAPARRAY_H
#define LABORATORY_WORK_4_MENUHEAPARRAY_H
#include <complex>
#include <iostream>
#include "HeapArray.h"
#include "DynamicArray.h"

using namespace std;

template<class T>
bool operator <  (const complex<T>& a, const complex<T>& b){
    T modA = a.imag() * a.imag() + a.real() * a.real();
    T modB = b.imag() * b.imag() + b.real() * b.real();
    if (modA < modB)
        return true;
    else
        return false;
}
template<class T>
bool operator <= (const complex<T>& a, const complex<T>& b){
    T modA = a.imag() * a.imag() + a.real() * a.real();
    T modB = b.imag() * b.imag() + b.real() * b.real();
    if (modA <= modB)
        return true;
    else
        return false;
}
template<class T>
bool operator >  (const complex<T>& a, const complex<T>& b){
    T modA = a.imag() * a.imag() + a.real() * a.real();
    T modB = b.imag() * b.imag() + b.real() * b.real();
    if (modA > modB)
        return true;
    else
        return false;
}
template<class T>
bool operator >= (const complex<T>& a, const complex<T>& b){
    T modA = a.imag() * a.imag() + a.real() * a.real();
    T modB = b.imag() * b.imag() + b.real() * b.real();
    if (modA >= modB)
        return true;
    else
        return false;
}
template <class T>
T getNumberInput();
std::complex<int> getComplexNumberInput();
int chooseTypeHeapArray();
int chooseFunctionHeapArray();

template<class T>
void inputHeapArrayTyped(DynamicArray<HeapArray<T>> *Arr);
void inputComplexArrayTyped(DynamicArray<HeapArray<complex<int>>> *Arr);

template<class T>
void functionHeapArrayTyped(DynamicArray<HeapArray<T>> *Arr);
void functionComplex(DynamicArray<HeapArray<complex<int>>> *Arr);

template<class T>
void outputHeapArrayTyped(DynamicArray<HeapArray<T>> *Arr);

void MenuHeapArray();

void InputAndSaveHeapArray(DynamicArray<HeapArray<int>> *intArr,
                           DynamicArray<HeapArray<float>> *floatArr,
                           DynamicArray<HeapArray<complex<int>>> *complexArr);

void FunctionWithHeapArray(DynamicArray<HeapArray<int>> *intArr,
                           DynamicArray<HeapArray<float>> *floatArr,
                           DynamicArray<HeapArray<complex<int>>> *complexArr);

void OutputHeapArray(DynamicArray<HeapArray<int>> *intArr,
                     DynamicArray<HeapArray<float>> *floatArr,
                     DynamicArray<HeapArray<complex<int>>> *complexArr);

template<class T>
void PrintHeapArrayMassive(HeapArray<T> heap);

template<class T>
void PrintHeapArrayBeauty(HeapArray<T> heap);



#endif //LABORATORY_WORK_4_MENUHEAPARRAY_H
