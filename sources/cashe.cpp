// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include "cashe.hpp"
#include <iomanip>
#include <string>
#include <algorithm>

Cashe::Cashe() {
  for (int size = 0.5 * cache_size[0]; size <= 1.5 * cache_size[2];
       size *= 2) {
    mem_exp.push_back(size);
  }
}
  void Cashe::direct_type() {
    travel_type = "direction";
    for (const int &i : mem_exp) {
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
      time_exp.push_back(
          static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000);
      delete []arr;
    }
  }

  void Cashe::reverse_type() {
    travel_type = "reverse";
    for (const int& i : mem_exp) {
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
      time_exp.push_back(static_cast<double>(end_time - start_time)
                                      / CLOCKS_PER_SEC * 1000);
      delete []arr;
    }
  }

  void Cashe::random_type() {
    travel_type = "random";
    for (const int& i : mem_exp) {
      int *arr = new int[i / sizeof(int)];
      std::vector<int> index_of_blocks;
      for (size_t j = 0; j < i / sizeof(int); j += 16){
        index_of_blocks.push_back(j);
        k = arr[j];
      }
      std::random_shuffle(index_of_blocks.begin(), index_of_blocks.end());

      int start_time = clock();
      for (size_t num = 0; num < 1000; ++num){
        for (const auto &index : index_of_blocks){
          k = arr[index];
        }
      }
      int end_time = clock();
      time_exp.push_back(static_cast<double>(end_time - start_time)
                                      / CLOCKS_PER_SEC * 1000);
      delete []arr;
    }
  }

  void Cashe::get_information(std::ostream &os,size_t num_exp) const{
    os << "\t- experiment:\n"
        << "\t\tnumber: " << num_exp + 1 << "\n"
        << "\t\tinput_data:\n"
        << "\t\t\tbuffer_size: " << mem_exp[num_exp] / 1024 << "Kb" <<"\n"
        << "\t\tresults:\n"
        << "\t\t\tduration: " << time_exp[num_exp] << "ms" << '\n';
  }

  void Cashe::print(std::ostream &os){
    os << "investigation:\n" << "\ttravel_order: " << travel_type << "\n";
    for (size_t i = 0; i < mem_exp.size(); ++i)
      get_information(os,i);
  }
