queue<int> queue_intersection(queue<int> q1, queue<int> q2) {
    queue<int> intersect;
    while (!(q1.empty() || q2.empty())) {
        if (q1.front() < q2.front()) {
            q1.pop();
        } else if (q1.front() > q2.front()) {
            q2.pop();
        } else {
            intersect.push(q1.front());
            q1.pop();
            q2.pop();
        }
    }
    return intersect;
}

queue<int> queue_union(queue<int> q1, queue<int> q2) {
    queue<int> un;
    while (!q1.empty() || !q2.empty()) {
        if (q2.empty() || (!q1.empty() && q1.front() < q2.front())) {
            un.push(q1.front());
            q1.pop();
        } else if (q1.empty() || q1.front() > q2.front()) {
            un.push(q2.front());
            q2.pop();
        } else {
            un.push(q1.front());
            q1.pop();
            q2.pop();
        }
    }
    return un;
}

queue<int> queue_negative(queue<int> q1, int article_count) {
    queue<int> neg;
    for (int i = 0; i < article_count; ++i) {
        if (!q1.empty() && q1.front() == i) {
            q1.pop();
            continue;
        }
        neg.push(i);
    }
    return neg;
}