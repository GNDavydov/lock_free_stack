// Copyright 2021 GNDavydov

#ifndef INCLUDE_LOCK_FREE_STACK_HPP_
#define INCLUDE_LOCK_FREE_STACK_HPP_

#include <atomic>
#include <memory>

namespace lock_free {
    template<class T>
    class LockFreeStack {
    private:
        struct Node {
            T data_;
            std::shared_ptr<Node> next_;

            explicit Node(const T &data) : data_(data), next_(nullptr) {}
        };

        std::shared_ptr<Node> head_;

    public:
        LockFreeStack() noexcept: head_(nullptr) {}

        void push(const T &val) {
            std::shared_ptr<Node> new_node = std::make_shared<Node>(val);
            new_node->next_ = std::atomic_load(&head_);
            while (!std::atomic_compare_exchange_weak(&head_, &new_node->next_, new_node));
        }

        bool tryPop(T &val) noexcept {
            if (!head_) {
                return false;
            }

            std::shared_ptr<Node> old_head = std::atomic_load(&head_);
            while (!std::atomic_compare_exchange_weak(&head_, &old_head, old_head->next_)) {
                if (!old_head) {
                    return false;
                }
            }

            val = old_head->data_;
            return true;
        }
    };
}


#endif //INCLUDE_LOCK_FREE_STACK_HPP_
