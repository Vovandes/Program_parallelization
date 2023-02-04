#include "program_parallelization.hpp"

//	Все слова в нижний регистр
std::string tolower(const std::string& str) {
	std::string lower_str;
	std::transform(
		std::cbegin(str), std::cend(str),
		std::back_inserter(lower_str),
		[](unsigned char ch) {
			return static_cast<unsigned char>(std::tolower(ch));
		});
	return lower_str;
};

//	Подсчет повторяющихся слов
void count_words(std::istream& stream, Counter& counter, std::mutex& mtx) {
	Counter tmp;
	std::for_each(
		std::istream_iterator<std::string>(stream),
		std::istream_iterator<std::string>(),
		[&tmp](const std::string& s) {
			++tmp[tolower(s)];
		});	
	std::lock_guard lock{ mtx };
	if (not_is_first_write) {
		counter = std::move(tmp);
		not_is_first_write = false;
	}
	else {
		std::for_each(
			tmp.cbegin(),
			tmp.cend(),
			[&counter](auto& it) {
				counter[it.first] += it.second;
			});
	}
}

//	Вывод повторяющихся слов
void print_topk(std::ostream& stream, const Counter& counter, const std::size_t k) {
	std::vector<Counter::const_iterator> words;
	words.reserve(counter.size());

	for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
		words.emplace_back(it);
	}
	auto k_new{ k };
	if (counter.size() < k) {
		k_new = counter.size();
	}
	std::partial_sort(
		std::begin(words), std::begin(words) + k_new, std::end(words),
		[](auto lhs, auto& rhs) {
			return lhs->second > rhs->second;
		});
	
	std::for_each(
		std::begin(words), std::begin(words) + k_new,
		[&stream](const Counter::const_iterator& pair) {
			stream << std::setw(4) << pair->second << " " << pair->first
				<< '\n';
		});
}

//	Переход в каталог \data
std::string get_file_path(std::string& tmp_path, const char* arg) {
	tmp_path = tmp_path.substr(0, tmp_path.find_last_of("\\"));
	tmp_path = tmp_path.substr(0, tmp_path.find_last_of("\\"));
	tmp_path += "\\data\\";
	tmp_path += arg;

	return tmp_path;
}

// Открытие файлов
void open_files_mtx(Counter& counter, const std::string& file_name, std::mutex& mtx) {
	std::ifstream input{ file_name };
	if (!input.is_open()) {
		std::cerr << "Failed to open file " << file_name << std::endl;
		return;
	}
	count_words(input, counter, std::ref(mtx));
}