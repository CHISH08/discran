#include"../lib/library.hpp"
#include "../lib/operator.hpp"
#include "../lib/load.hpp"
#include "../lib/save.hpp"
#include "../lib/function.hpp"
#include "../lib/index.hpp"
#include "../lib/search.hpp"
#include "../lib/parser.hpp"

int main(int argc, char* argv[]) {
	bool mode, flag = false;
	string index, input, output;
	unordered_map<string, string> dict;
	vector<string> mas;
	flag_parser(argc, argv, mode, index, input, output, flag);

	if (mode) { // index
		text_to_map(input, dict, mas);
		save_struct(dict, mas, output);
	} else { // search
		load_map(dict, mas, index);
		answer_question(dict, mas, input, output, flag);
	}
}
