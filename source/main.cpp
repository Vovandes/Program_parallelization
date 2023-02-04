#include "program_parallelization.hpp"
#include "simple_timer.hpp"

const std::size_t TOPK = 10;

int main(int argc, char* argv[]) {
	//////////////////////////////////////////////////////////////////////////
	if (argc < 2) {													// Reading arguments cmd
		std::cerr << "Usage: topk_words [FILES...]\n";
		return EXIT_FAILURE;
	}	
	//////////////////////////////////////////////////////////////////////////
	std::vector<std::string> files;									//	Create std::vector files
	for (std::size_t i = 1; i < argc; ++i) {
		std::string path{ __FILE__ };
		files.emplace_back(std::move(get_file_path(path, argv[i])));
	}
	//////////////////////////////////////////////////////////////////////////
	SimpleTimer sm;													//	Timer On
	//////////////////////////////////////////////////////////////////////////
	Counter freq_dict;												//	Create Dictionary
	//////////////////////////////////////////////////////////////////////////
	std::vector<std::thread> th_vect;								//	Create std::vector std::thread
	std::mutex mtx;													//	Create std::mutex
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < files.size(); ++i) {
		std::thread files_thread{ open_files_mtx, std::ref(freq_dict), std::ref(files[i]), std::ref(mtx) };
		th_vect.emplace_back(std::move(files_thread));
	}
	for (auto& elem : th_vect) {							// join threads
		elem.join();
	}
	//////////////////////////////////////////////////////////////////////////
	print_topk(std::cout, freq_dict, TOPK);			// Print TOPK Words
	//////////////////////////////////////////////////////////////////////////	
	sm.End();														//	Timer Off
	sm.Print();														//	Print Time Result
	//////////////////////////////////////////////////////////////////////////
	std::cin.get();
}