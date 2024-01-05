queue<int> file_to_queue(string filename) {
	ifstream input_file(filename);
	int line;
	queue<int> ans;
	if (!input_file.is_open()) {
        return ans;
    }
	while (input_file >> line) {
		ans.push(line);
	}
	return ans;
}

void load_map(unordered_map<string, string> &dict, vector<string> &mas, string filename) {
	ifstream ifs(filename, ios::binary);
    boost::archive::binary_iarchive ia(ifs);
    ia >> dict >> mas;
	ifs.close();
}