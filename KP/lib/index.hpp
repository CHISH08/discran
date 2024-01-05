void text_to_map(string input, unordered_map<string, string> &dict, vector<string> &mas) {
	ifstream input_file(input);
	if (!input_file.is_open()) {
        cerr << "Ошибка: Невозможно открыть файл " << input << endl;
        exit(EXIT_FAILURE);
    }

	string lines;
	bool mode = false;
	string name = "";
	unordered_map<string, int> end_name;
	int j = -1;

	while (getline(input_file, lines))
	{
		if (!mode) {
			for (int i = lines.size()-3; lines[i] != '\"'; --i) name = lines[i] + name;
			mode = true;
			mas.push_back(name);
			++j;
		} else {
			if (lines.substr(0, 2) == "</") {
				mode = false;
				name = "";
				continue;
			}
			istringstream iss(lines);
			while (iss >> lines) {
				save_file(j, lines, end_name, dict);
			}
		}
	}
	
	input_file.close();
	return;
}