bool isOperator(char c) {
    return c == '&' || c == '|' || c == '~';
}

bool isSpecialCharacter(char c) {
    return isOperator(c) || c == '(' || c == ')' || c == ' ';
}

int getPrecedence(char op) {
    if (op == '|') return 1;
    if (op == '&') return 2;
    if (op == '~') return 3;
    return 0;
}

string getWord(const string& s, size_t& pos) {
    string word;
    while (pos < s.length() && !isSpecialCharacter(s[pos])) {
        word += s[pos++];
    }
    return word;
}

bool equal_string(char* a, string b) {
	short i = 0;
	while (a[i] != '\0' && i < b.size()) {
		if (a[i] != b[i]) return 0;
		++i;
	}
	return 1;
}