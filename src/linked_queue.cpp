#include "assignment/linked_queue.hpp"

namespace assignment {

  LinkedQueue::~LinkedQueue() {

    // эквивалентно очистке очереди
    LinkedQueue::Clear();
  }

  void LinkedQueue::Enqueue(int value) {
    if (IsEmpty()) {
      Node* new_node = new Node(value, nullptr);
      front_ = new_node;
      back_= front_;
      size_++;
    } else {
      Node* new_node = new Node(value, nullptr);
      back_->next = new_node;
      back_ = new_node;
      size_++;
    }
  }

  bool LinkedQueue::Dequeue() {
    if (IsEmpty()) {
      return false;
    }
    front_->value = 0;
    front_ = front_->next;
    size_--;
    return true;
  }

  void LinkedQueue::Clear() {
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedQueue::front() const {
    if (IsEmpty()) {
      return std::nullopt;
    }
    return front_->value;
  }

  std::optional<int> LinkedQueue::back() const {
    if (IsEmpty()) {
      return std::nullopt;
    }
    return back_->value;
  }

  bool LinkedQueue::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedQueue::size() const {
    return size_;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedQueue::LinkedQueue(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedQueue::toVector() const {
    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment