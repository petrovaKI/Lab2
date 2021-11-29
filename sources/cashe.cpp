// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include "cashe.hpp"
#include <iomanip>
#include <string>
#include <algorithm>
#include <random>

Cashe::Cashe() {
  for (int size = 1.0 / 2 * cache_size[0]; size <= 3.0 / 2 * cache_size[2];
       size *= 2) {
    size_buf.push_back(size);
  }
}
  size_t Cashe::get_count_buf() const
  {
    return size_buf.size(); //определяем количество экспериментов
  }

  void Cashe::direct_type() {
    travel_type = "direction";
    for (const int &i : size_buf) {
      int *arr = new int[i / sizeof(int)];
      //прогрев
      for (size_t j = 0; j < i / sizeof(int); j += 16) {
        k = arr[j];
      }
      //подсчёт
      int start_time = clock();
      for (size_t num = 0; num < 1000; ++num) {
        for (size_t j = 0; j < i / sizeof(int); j += 16) {
          k = arr[j];
        }
      }
      int end_time = clock();
      result.push_back(
          static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000);
      delete []arr;
    }
  }

  void Cashe::reverse_type() {
    travel_type = "reverse";
    for (const int& i : size_buf) {
      int* arr = new int[i / sizeof(int)];

      //прогрев
      for (size_t j = i / sizeof(int); j > 0 ; j -= 16){
        k = arr[j];
      }
      //подсчёт
      int start_time = clock();
      for (size_t num = 0; num < 1000; ++num){
        for (size_t j = i / sizeof(int); j > 0; j -= 16){
          k = arr[j];
        }
      }
      int end_time = clock();
      result.push_back(static_cast<double>(end_time - start_time)
                                      / CLOCKS_PER_SEC * 1000);
      delete []arr;
    }
  }

  void Cashe::random_type() {
    travel_type = "random";
    for (const int& i : size_buf) {
      int *arr = new int[i / sizeof(int)];
      std::vector<int> index_of_blocks;
      for (size_t j = 0; j < i / sizeof(int); j += 16){
        index_of_blocks.push_back(j);
        k = arr[j];
      }
      auto rng = std::default_random_engine {};
      std::shuffle(index_of_blocks.begin(), index_of_blocks.end(), rng);

      int start_time = clock();
      for (size_t num = 0; num < 1000; ++num){
        for (auto index : index_of_blocks){
          k = arr[index];
        }
      }
      int end_time = clock();
      result.push_back(static_cast<double>(end_time - start_time)
                                      / CLOCKS_PER_SEC * 1000);
      delete []arr;
    }
  }

  std::stringstream Cashe::get_information(size_t num_exp) const{
    std::stringstream out;
    out << "\t- experiment:\n"
        << "\t\tnumber: " << num_exp + 1 << "\n"
        << "\t\tinput_data:\n"
        << "\t\t\tbuffer_size: " << size_buf[num_exp] / 1024 << "Kb" <<"\n"
        << "\t\tresults:\n"
        << "\t\t\tduration: " << result[num_exp] << "ms" << '\n';
    return out;
  }

  std::string Cashe::type() const {
    return travel_type;
  }

  void Cashe::print(const Cashe &a){
    std::cout << "investigation:\n" << "\ttravel_order: " << a.type() << "\n";
    for (size_t i = 0; i < a.get_count_buf(); ++i)
      std::cout << a.get_information(i).str();

    std::cout << "\n";
  }
