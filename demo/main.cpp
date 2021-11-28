#include <cashe.hpp>

int main() {
  Cashe a;
  a.direct_type();
  a.print(a);
  a.reverse_type();
  a.print(a);
  a.random_type();
  a.print(a);
}