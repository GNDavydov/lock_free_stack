// Copyright 2021 GNDavydov

#include <iostream>
#include <vector>
#include <thread>

#include <lock_free_stack.hpp>

using namespace lock_free;

void insert(LockFreeStack<std::size_t> &stack, const std::vector<std::size_t> &numbers) {
    for (auto &num: numbers) {
        stack.push(num);
    }
}

void pop(LockFreeStack<std::size_t> &stack, std::size_t num) {
    std::size_t x;
    for (std::size_t i = 0; i < num; ++i) {
        stack.tryPop(x);
        std::cout << x << std::endl;
    }
}


int main() {
    {
        std::vector<std::size_t> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                                            22, 23, 24, 25, 26, 27, 28};
        LockFreeStack<std::size_t> stack;
        std::thread t1_insert(insert, std::ref(stack), std::ref(numbers));
        std::thread t2_insert(insert, std::ref(stack), std::ref(numbers));
        std::thread t3_insert(insert, std::ref(stack), std::ref(numbers));

        t1_insert.join();
        t2_insert.join();
        t3_insert.join();

        std::thread t1_pop(pop, std::ref(stack), 35);
        std::thread t2_pop(pop, std::ref(stack), 29);
        std::thread t3_pop(pop, std::ref(stack), 20);

        t1_pop.join();
        t2_pop.join();
        t3_pop.join();
    }

    exit(EXIT_SUCCESS);
}
