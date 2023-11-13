#include "tree.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>

void test_tree() {
  std::vector<int> numbers;
  for (int i = 0; i < 100; ++i) {
    numbers.push_back(rand() % 10000 + 1);
  }

  std::shuffle(numbers.begin(), numbers.end(), std::mt19937{std::random_device{}()});

  tree_t tree(100);
  for (const auto& number : numbers) {
    tree.set(number, number);
    assert(tree.get(number) == number);
  }

  std::shuffle(numbers.begin(), numbers.end(), std::mt19937{std::random_device{}()});

  for (const auto& number : numbers) {
    assert(tree.get(number) == number);
  }

  std::shuffle(numbers.begin(), numbers.end(), std::mt19937{std::random_device{}()});

  // remove half of the numbers
  for (int i = 0; i < 50; ++i) {
    tree.remove(numbers[i]);
  }

  // test the remaining numbers
  for (int i = 50; i < 100; ++i) {
    assert(tree.get(numbers[i]) == numbers[i]);
  }
}

int main() {
  test_tree();
  return 0;
}