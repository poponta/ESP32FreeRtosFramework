//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#include <array>
#include <type_traits>

// see #42
template <typename T, std::size_t U, typename INSTANTIATE_FROM_CONSTRUCTOR = std::false_type>
class ArrayContainer {
 public:
  ArrayContainer() = default;
  virtual ~ArrayContainer() = default;
  ArrayContainer(const ArrayContainer& obj) = delete;
  ArrayContainer& operator=(const ArrayContainer& obj) = delete;

  bool PushBack(T arg) {
    if (index_ >= container_.size()) {
      // Array Full
      log_i("pushBack full error");
      return false;
    }
    container_[index_] = arg;
    index_++;
    return true;
  }

  uint32_t Size() const {
    return index_;
  }

  using container = std::array<T, U>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  // For "range-based for" statement
  iterator begin() { return container_.begin(); }
  iterator end() { return container_.end(); }
  const_iterator begin() const { return container_.begin(); }
  const_iterator end() const { return container_.end(); }
  
  // private:
  container container_;
  uint32_t index_ = 0;  // initialize to zero
};

template <typename T, std::size_t U>
class ArrayContainer<T, U, std::true_type> {
 public:
  ArrayContainer() {log_i("Array Const called from constructor");}
  virtual ~ArrayContainer() = default;
  ArrayContainer(const ArrayContainer& obj) = delete;
  ArrayContainer& operator=(const ArrayContainer& obj) = delete;

  bool PushBack(T arg) {
    if (index_ >= container_.size()) {
      // Array Full
      log_i("pushBack full error");
      return false;
    }
    container_[index_] = arg;
    index_++;
    return true;
  }

  uint32_t Size() const {
    return index_;
  }

  using container = std::array<T, U>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  // For "range-based for" statement
  iterator begin() { return container_.begin(); }
  iterator end() { return container_.end(); }
  const_iterator begin() const { return container_.begin(); }
  const_iterator end() const { return container_.end(); }
  
 private:
  container container_;
  uint32_t index_;  // no initialized
};