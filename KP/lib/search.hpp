queue<std::string> parseToQueue(const string &expr) {
    stack<char> opStack;
    queue<string> outputQueue;
    unordered_map<char, int> precedence = {{'|', 1}, {'&', 2}, {'~', 3}};

    for (size_t i = 0; i < expr.length();) {
        if (expr[i] == ' ') {
            i++;
        } else if (!isSpecialCharacter(expr[i])) {
            string word = getWord(expr, i);
            outputQueue.push(word);
        } else if (isOperator(expr[i])) {
            while (!opStack.empty() && isOperator(opStack.top()) &&
                   (precedence[opStack.top()] > precedence[expr[i]] ||
                    (precedence[opStack.top()] == precedence[expr[i]] && expr[i] != '~'))) {
                outputQueue.push(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(expr[i]);
            i++;
        } else if (expr[i] == '(') {
            opStack.push(expr[i]);
            i++;
        } else if (expr[i] == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                outputQueue.push(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.pop();
            i++;
        } else {
            i++;
        }
    }

    while (!opStack.empty()) {
        outputQueue.push(string(1, opStack.top()));
        opStack.pop();
    }

    return outputQueue;
}

queue<int> evaluatePostfix(queue<string>& postfix, unordered_map<string, string>& queues, int article_count) {
    stack<queue<int>> evalStack;

    while (!postfix.empty()) {
        string token = postfix.front();
        postfix.pop();

        if (!isOperator(token[0])) {
            evalStack.push(file_to_queue(queues[token]));
        } else {
            if (token == "~") {
                queue<int> operand = evalStack.top();
                evalStack.pop();
                evalStack.push(queue_negative(operand, article_count));
            } else {
                queue<int> operand2 = evalStack.top();
                evalStack.pop();
                queue<int> operand1 = evalStack.top();
                evalStack.pop();

                if (token == "&") {
                    evalStack.push(queue_intersection(operand1, operand2));
                } else if (token == "|") {
                    evalStack.push(queue_union(operand1, operand2));
                }
            }
        }
    }
    return evalStack.top();
}