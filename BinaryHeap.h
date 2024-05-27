//                                                       .--.
//                                                       `.  \
//                                                         \  \
//                                                          .  \
//                                                          :   .
//                                                          |    .
//                                                          |    :
//                                                          |    |
//          ..._  ___                                       |    |
//         `."".`''''""--..___                              |    |
//         ,-\  \             ""-...__         _____________/    |
//         / ` " '                    `""""""""                  .
//         \                                                      L
//         (>                                                      \
//        /                                                         \
//        \_    ___..---.                                            L
//          `--'         '.                                           \
//                         .                                           \_
//                        _/`.                                           `.._
//                     .'     -.                                             `.
//                    /     __.-Y     /''''''-...___,...--------.._            |
//                   /   _."    |    /                ' .      \   '---..._    |
//                  /   /      /    /                _,. '    ,/           |   |
//                  \_,'     _.'   /              /''     _,-'            _|   |
//                          '     /               `-----''               /     |
//                          `...-'                                       `...-'


#ifndef LABORATORY_WORK_4_BINARYHEAP_H
#define LABORATORY_WORK_4_BINARYHEAP_H

template<class T>
class BinaryHeap {
public:
    virtual void AddElement(T item) = 0;  // вставка элемента
    virtual T FindElement(int key) = 0;  // поиск элемента по ключу
    virtual void DeleteElementByKey(int key) = 0;  // удаление объекта по ключу
    virtual void DeleteElement(T value) = 0;
    virtual void MaxHeapify(int key) = 0;
    virtual BinaryHeap<T>* GetTree(T item) = 0;   // извлечение поддерева(по заданному элементу)

};


#endif //LABORATORY_WORK_4_BINARYHEAP_H
