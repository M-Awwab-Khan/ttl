vector<int> extract_cycle(int x) {
    int a = x;
    int b = teleport[x];
    while (a != b) {
        a = teleport[a];
        b = teleport[teleport[b]];
    }
    vector<int> cycle;
    do {
        a = teleport[a];
        cycle.push_back(a);
    } while (a != b);
    return cycle;
}
