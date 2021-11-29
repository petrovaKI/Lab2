#include <cashe.hpp>

int main() {
  Cashe a;
  a.direct_type();
  a.print(a);
  Cashe b;
  b.reverse_type();
  b.print(b);
  Cashe c;
  c.random_type();
  c.print(c);
}