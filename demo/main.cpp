#include <cashe.hpp>

int main() {
  Cashe one;
  one.direct_type();
  one.print(std::cout);
  Cashe two;
  two.reverse_type();
  two.print(std::cout);
  Cashe three;
  three.random_type();
  three.print(std::cout);
}