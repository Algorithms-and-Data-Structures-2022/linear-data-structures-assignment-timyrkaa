#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {
  DynamicArray::DynamicArray(int capacity) {
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    size_ = 0;
    capacity_ = capacity;
    data_ = new int[capacity_];
    std::fill(data_,data_+capacity_,0);

  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;

    delete[] data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
    if (size_ == capacity_) {
      int* new_data = new int[capacity_ + kCapacityGrowthCoefficient];
      for (int i = 0; i < size_; i++) {
        new_data[i] = data_[i];
      }
      new_data[size_] = value;
      delete[] data_;
      data_ = new_data;
      size_++;
      capacity_ = capacity_ + kCapacityGrowthCoefficient;
    } else {
      data_[size_] = value;
      size_++;
    }
  }

  bool DynamicArray::Insert(int index, int value) {
    if ((index < 0)||(index > size_)) {
      return false;
    }
    if ((size_ == 0)||(index == size_)||((size_ == 1)&&(index == 1))) {
      Add(value);
      return true;
    }
    if ((size_ == 1)&&(index == 0)) {
      Add(data_[0]);
      data_[0] = value;
      return true;
    }
    if (size_ == capacity_) {
      int* new_array = new int[capacity_+kCapacityGrowthCoefficient];
      for (int i = 0; i <= size_; i++) {
        if (i < index) {
          new_array[i] = data_[i];
        }
        if (i == index) {
          new_array[i] = value;
        }
        if (i > index) {
          new_array[i] = data_[i-1];
        }
      }
      size_++;
      capacity_ = capacity_+kCapacityGrowthCoefficient;
      data_ = new_array;
      return true;
    }
    for (int i = size_; i > index; i--) {
      data_[i] = data_[i-1];
    }
    data_[index] = value;
    size_++;
    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {
    if ((size_ == 0)||(index >= size_)||(index < 0)) {
      return false;
    }
    data_[index] = new_value;
    return true;

  }

  std::optional<int> DynamicArray::Remove(int index) {
    if (IsEmpty()||(index < 0)||(index >= size_)) {
      return std::nullopt;
    }
    int deleted_element = data_[index];
    if ((size_ == 1)||(index == size_-1)) {
      data_[index] = 0;
      size_--;
      return deleted_element;
    }
    for (int i = index; i < size_-1; i++) {
      data_[i] = data_[i+1];
    }
    size_--;
    return deleted_element;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (size_ == 0) {
      return std::nullopt;
    } else if ((index < size_)&&(index >= 0)) {
      return data_[index];
    } else {
      return std::nullopt;
    }
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity <= capacity_) {
      return false;
    }
    int* new_arr = new int[new_capacity];
    std::copy(data_,data_+size_,new_arr);
    delete[] data_;
    data_ = new_arr;
    capacity_ = new_capacity;
    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment