//
// Created by soven on 05.11.2023.
//
#include <iostream>
#include <vector>

int partition(std::vector<int>& array, int x) {
    int i = 0;
    int j = array.size() - 1;

    while (i <= j) {
        while (array[i] < x) {
            i++;
        }
        while (array[j] > x) {
            j--;
        }

        if (i <= j) {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    return i;
}

int main() {
    int N;
    std::cin >> N;

    std::vector<int> array(N);
    for (int i = 0; i < N; i++) {
        std::cin >> array[i];
    }

    int x;
    std::cin >> x;

    int index = partition(array, x);

    std::cout << N - index << std::endl;
    std::cout << index << std::endl;


    return 0;
}
