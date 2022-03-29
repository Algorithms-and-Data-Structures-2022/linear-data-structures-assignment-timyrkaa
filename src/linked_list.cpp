#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    if (IsEmpty()) {
      back_ = new Node(value, nullptr);
      front_ = back_;
      size_++;
    } else {
      Node* new_node = new Node(value, nullptr);
      back_->next = new_node;
      back_ = new_node;
      size_++;
    }
  }

  bool LinkedList::Insert(int index, int value) {
    if ((index < 0)||(index > size_)||(IsEmpty()&&(index > 0))) {
      return false;
    }
    if ((size_ == 1)&&(index == 0)) {
      Node* new_node = new Node(value,back_);
      front_ = new_node;
      size_++;
      return true;
    }
    if (IsEmpty()||(index == size_)||((size_ == 1)&&(index == 1))) {
      Add(value);
      return true;
    }
    if (index == 0) {
      Node* new_node = new Node(value, front_);
      front_ = new_node;
      size_++;
      return true;
    }
    Node* new_node = new Node(value, FindNode(index));
    Node* first_before_inserted = FindNode(index-1);
    first_before_inserted->next = new_node;
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (IsEmpty()||(index < 0)||(index >= size_)) {
      return false;
    }
    Node* changed_node = front_;
    for (int i = 0; i < index; i++) {
      Node* next_node = changed_node->next;
      changed_node = next_node;
    }
    changed_node->value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (IsEmpty() || (index < 0) || (index >= size_)) {
      return std::nullopt;
    }
    int deleted_value;
    if (index == 0) {
      deleted_value = front_->value;
      front_ = front_->next;
      size_--;
      return deleted_value;
    }
    Node* search_node = front_;
    for (int i = 0; i < index; i++) {
      if ((index == size_-1)&&(i == index-1)) {
        deleted_value = back_->value;
        search_node->next = nullptr;
        back_ = search_node;
        size_--;
        return deleted_value;
      }
      if (i == index-1) {
        deleted_value = search_node->next->value;
        search_node->next = search_node->next->next;
        size_--;
        return deleted_value;
      }
      search_node = search_node->next;
    }
  }


  void LinkedList::Clear() {
      size_ = 0;
      front_ = nullptr;
      back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (IsEmpty()||(index < 0)||(index >= size_)) {
      return std::nullopt;
    }
    Node* search_node = front_;
    for (int i = 0; i < index; i++) {
      Node* next_node = search_node->next;
      search_node = next_node;
    }
    return search_node->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* search_node = front_;
    for (int i = 0; i < size_-1; i++) {
      Node* next_node = search_node->next;
      if (search_node->value == value) {
        return i;
      }
      search_node = next_node;
    }
    if (search_node->value == value) {
      return size_-1;
    }
    return false;
  }

  bool LinkedList::Contains(int value) const {
    Node* search_node = front_;
    for (int i = 0; i < size_-1; i++) {
      Node* next_node = search_node->next;
      if (search_node->value == value) {
        return true;
      }
      search_node = next_node;
    }
    return search_node->value == value;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (IsEmpty()) {
      return std::nullopt;
    }
    return front_->value;
  }

  std::optional<int> LinkedList::back() const {
    if (IsEmpty()) {
      return std::nullopt;
    }
    return back_->value;
  }

  Node* LinkedList::FindNode(int index) const {
    if (IsEmpty()||(index < 0)||(index >= size_)) {
      return nullptr;
    }
    Node* search_node = front_;
    for (int i = 0; i < index; i++) {
      Node* next_node = search_node->next;
      search_node = next_node;
    }
    return search_node;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

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

  std::vector<int> LinkedList::toVector() const {

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
