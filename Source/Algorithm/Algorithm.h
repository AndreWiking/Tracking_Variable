
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>

template<typename T>
void SelectionSort(T *data, size_t size);

template<typename T>
void BubbleSort(T *data, size_t size);


template<typename T>
void SelectionSort(T *data, size_t size) {

    for (int i = 0; i + 1 < size; i++) {

        int id = i;
        for (int j = i + 1; j < size; j++)
            if (data[j] < data[id])
                id = j;

        std::swap(data[i], data[id]);
    }
}

template<typename T>
void BubbleSort(T *data, size_t size) {
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            if (data[j] < data[i]) {
                std::swap(data[i], data[j]);
            }
}

template<typename T>
void FillRandom(T *data, size_t size, size_t max_val){
    for (int i = 0; i < size; ++i)
        data[i] = rand() % max_val;
}

#endif //ALGORITHM_H
