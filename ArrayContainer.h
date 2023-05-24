#ifndef ARRAY_CONTAINER_H_
#define ARRAY_CONTAINER_H_

#include <array>
#include <type_traits>

template <typename T, std::size_t U, typename INSTANTIATE_FROM_CONSTRUCTOR = std::false_type>
class ArrayContainer {
 public:
  ArrayContainer() : container_({0}), index_(0) {}
  explicit ArrayContainer(T (&array)[U]) {
    for (int i = 0; i < U; i++) {
      container_[i] = array[i];
    }
  }
  virtual ~ArrayContainer() = default;
  ArrayContainer(const ArrayContainer& obj) = delete;
  ArrayContainer& operator=(const ArrayContainer& obj) = delete;

  using container = std::array<typename std::remove_const<T>::type, U>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  bool PushBack(T arg) {
    if (index_ >= container_.size()) {
      return false;
    }
    container_[index_] = arg;
    index_++;
    return true;
  }

  uint32_t Size() const {
    return index_;
  }

  void Clear() {
    container_.fill(0);
    index_ = 0;
  }

 container& Data() {
    return container_;
  }

  // For "range-based for" statement
  iterator begin() { return container_.begin(); }
  iterator end() { return container_.end(); }
  const_iterator begin() const { return container_.begin(); }
  const_iterator end() const { return container_.end(); }
  typename std::remove_const<T>::type& operator[](std::size_t n) { return container_[n]; }

  // private:
  container container_;
  uint32_t index_;
};

template <typename T, std::size_t U>
class ArrayContainer<T, U, std::true_type> {
 public:
  ArrayContainer() = default;
  virtual ~ArrayContainer() = default;
  ArrayContainer(const ArrayContainer& obj) = delete;
  ArrayContainer& operator=(const ArrayContainer& obj) = delete;

  using container = std::array<typename std::remove_const<T>::type, U>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  bool PushBack(T arg) {
    if (index_ >= container_.size()) {
      return false;
    }
    container_[index_] = arg;
    index_++;
    return true;
  }

  uint32_t Size() const {
    return index_;
  }

  void Clear() {
    container_.fill(0);
    index_ = 0;
  }

container& Data() {
    return container_;
  }

  // For "range-based for" statement
  iterator begin() { return container_.begin(); }
  iterator end() { return container_.end(); }
  const_iterator begin() const { return container_.begin(); }
  const_iterator end() const { return container_.end(); }
  typename std::remove_const<T>::type& operator[](std::size_t n) { return container_[n]; }

 private:
  container container_;
  uint32_t index_;  // no initialized
};

template <typename T, std::size_t N>
constexpr std::size_t ArraySize(T (&)[N]) noexcept {
  return N;
}

#endif  // ARRAY_CONTAINER_H_