#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    size_ = 0;
    capacity_ = capacity;
    data_ = new int[capacity_];
    std::fill(data_,data_+capacity_,0);
  }

  ArrayStack::~ArrayStack() {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
  }

  void ArrayStack::Push(int value) {
    if (size_ == capacity_) {
      int* new_arr = new int[capacity_+kCapacityGrowthCoefficient];
      for (int i = 0; i < capacity_; i++) {
        new_arr[i] = data_[i];
      }
      new_arr[size_] = value;
      capacity_ = capacity_ + kCapacityGrowthCoefficient;
      size_++;
      delete[] data_;
      data_ = new_arr;
    } else {
      data_[size_] = value;
      size_++;
    }
  }

  bool ArrayStack::Pop() {
    if (size_ == 0) {
      return false;
    } else {
      size_--;
      return true;
    }
  }

  void ArrayStack::Clear() {
    size_ = 0;
  }

  std::optional<int> ArrayStack::Peek() const {
    if (size_ == 0) {
      return std::nullopt;
    } else {
      return data_[size_-1];
    }
  }

  bool ArrayStack::IsEmpty() const {
    return size_ == 0;
  }

  int ArrayStack::size() const {
    return size_;
  }

  int ArrayStack::capacity() const {
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {
    if (new_capacity <= capacity_) {
      return false;
    }
    int* new_arr = new int[new_capacity];
    for (int i = 0; i < capacity_; i++) {
      new_arr[i] = data_[i];
    }
    capacity_ = new_capacity;
    delete[] data_;
    data_ = new_arr;
    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  ArrayStack::ArrayStack(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment
