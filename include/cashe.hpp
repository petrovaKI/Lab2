// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#ifndef INCLUDE_CASHE_HPP_
#define INCLUDE_CASHE_HPP_

#include <set>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

class Cashe {
 public:
  Cashe();
  std::stringstream get_information(size_t num_exp) const;
  std::string type() const;
  size_t get_count_buf() const;
  void direct_type();
  void reverse_type();
  void random_type();
  void print(const Cashe & a);
 private:
  //3 уровня кеша (L1 - 256 КБ, L2 - 1 МБ, L3 - 6 МБ)
  const std::vector<int> cache_size = {256 * 1024,
                                       1024 * 1024,
                                       6 * 1024 * 1024};
  int k;
  std::string travel_type; //тип обхода
  std::vector<int> size_buf;
  std::vector<double> result;
};


#endif // INCLUDE_CASHE_HPP_
