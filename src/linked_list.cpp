#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* element = new Node(value);
    if(front_ != nullptr){
      back_ ->next = element;
      back_ = element;
    }
    else{
      front_ = element;
      back_ = element;
    }
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index > size_ || index < 0) {
      return false;
    }
    Node* insertV = new Node(value);
    if (IsEmpty()) {
      back_ = insertV;
      front_ = insertV;
    }
    else if (index == size_){
      back_ -> next = insertV;
      back_ = insertV;
    }
    else if (index == 0){
      insertV -> next = front_;
      front_ = insertV;
    }
    else {
      insertV->next = FindNode(index - 1)->next;
      FindNode(index - 1) -> next = insertV;
    }
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index >= size_ || index < 0) {
      return false;
    }
    else {
      FindNode(index) -> value = new_value;
      return true;
    }
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= size_ || index < 0) {
      return std::nullopt;
    }
    int remValue;
    if (index != 0){
      remValue = FindNode(index)->value;
      FindNode(index-1) -> next = FindNode(index) -> next;
      }
    else {
      remValue = (front_ -> value);
      front_= (front_ -> next);
      }
      size_--;
      return remValue;
  }

  void LinkedList::Clear() {
    Node* temp = front_;
    for (int i = 0; i < size_; i++) {
      Node* curr = temp -> next;
      delete temp;
      temp = curr;
    }
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index >= size_ || index < 0) {
      return std::nullopt;
    }
    else {
      Node* n = FindNode(index);
      return n -> value;
    }
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* temp = front_;
    for (int i = 0; i < size_; i++) {
      if (temp->value == value) {
        return i;
      }
      temp = temp->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    if (IndexOf(value) != std::nullopt){
      return true;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
      return front_->value;
    }
      return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index >= size_ || index < 0){
      return nullptr;
    }
    Node* node = front_;
    for (int i = 0; i < index; i++) {
      node = node->next;
    }
    return node;
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