void save_file(int name, string lines, unordered_map<string, int> &end_name, unordered_map<string, string> &dict) {
	if (dict.find(lines) == dict.end()) {
		dict[lines] = "../data/" + lines + ".txt";
		ofstream outfile("../data/" + lines + ".txt");
		outfile.close();
	}
	if (end_name.find(lines) == end_name.end() || end_name[lines] != name) {
		ofstream outfile("../data/" + lines + ".txt", ios::app);
		outfile << name << '\n';
		end_name[lines] = name;
		outfile.close();
	}
}

void save_struct(unordered_map<string, string> &dict, vector<string> &mas, string filename) {
	ofstream ofs(filename, ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << dict << mas;
	ofs.close();
}