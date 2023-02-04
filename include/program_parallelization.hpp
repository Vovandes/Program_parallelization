#pragma once

// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

static bool not_is_first_write{ true };

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string& str);

void count_words(std::istream& stream, Counter& counter, std::mutex& mtx);

void print_topk(std::ostream& stream, const Counter& counter, const std::size_t k);

std::string get_file_path(std::string& tmp_path, const char* arg);

void open_files_mtx(Counter& counter, const std::string& file_name, std::mutex& mtx);