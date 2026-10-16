for (int i = 1; i <= n; ++i) {
    for (auto [from, to, score] : edges) {
        if(distance[from] == INF) continue;
        ll new_distance = min(distance[to], distance[from] + score);
        if (i == n && new_distance < distance[to]) {
            cout << -1 << '\n'; // Negative Cycle
            return 0;
        }
        distance[to] = new_distance;
    }
}
cout << distance[n] << '\n';