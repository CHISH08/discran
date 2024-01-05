void flag_parser(int argc, char* argv[], bool &mode, string &index, string &input, string &output, bool &flag) {
	short i = 1;
	while (i < argc) {
		if (equal_string(argv[i], "--index")) {
			index = argv[i+1];
			++i;
		} else if (equal_string(argv[i], "--input")) {
			input = argv[i+1];
			++i;
		} else if (equal_string(argv[i], "--output")) {
			output = argv[i+1];
			++i;
		} else if (equal_string(argv[i], "search") || equal_string(argv[i], "index")) {
			mode = equal_string(argv[i], "index");
		} else if (equal_string(argv[i], "--full-output")) {
            flag = true;
        }
		++i;
	}
	return;
}

void answer_question(unordered_map<string, string> &dict, vector<string> &mas, string input, string output, bool flag) {
	ifstream input_file(input);
    ofstream output_file(output);
	if (!input_file.is_open()) {
        cerr << "Ошибка: Невозможно открыть файл " << input << endl;
        exit(EXIT_FAILURE);
    }
    if (!output_file.is_open()) {
        cerr << "Ошибка: Невозможно открыть файл " << output << endl;
        exit(EXIT_FAILURE);
    }

	string line;
	while (getline(input_file, line)) {
        output_file << line << ":\n";
		queue<string> postfix = parseToQueue(line);
		queue<int> result = evaluatePostfix(postfix, dict, mas.size());
        output_file << result.size() << '\n';
        if (flag) {
            while (!result.empty()) {
                output_file << mas[result.front()] << "\n";
                result.pop();
            }
        }
	}
    input_file.close();
    output_file.close();
}