# ifndef GRAPH_H
# define GRAPH_H

# include <iostream>
# include <unordered_map>
# include <unordered_set>
# include <vector>
# include <queue>
# include <utility>

// T -> Vertices

template <typename T> class Graph {
private:
    bool directed = false;
    bool weighted = false;
    int vertices = 0;

    std::unordered_map<T, std::vector<std::pair<T, int>>> adjList;

    void DFS(T s, std::unordered_set<T>& visited, bool print = true);

    void DFSForBridge(std::unordered_map<T, int>& ids, std::unordered_map<T, int>& low, std::unordered_set<T>& visited, std::vector<std::pair<T, T>>& b, int& id, T curr, T parent, bool hasParent = true);

    void DFSForBridge(T u, std::unordered_map<T, int>& disc, std::unordered_map<T, int>& low, std::unordered_map<T, T>& parent, std::unordered_set<std::pair<T, T>>& bridges);

    void DFSForArticulationPoints(T u, std::unordered_map<T, int>& disc, std::unordered_map<T, T>& parent, std::unordered_map<T, int>& low, std::unordered_set<T>& articulationPoints);

    T min(T& a, T& b);

public:
    Graph(bool d = false, bool w = false);

    void addVertex(T v);

    void addEdge(T u, T v, int W = 0);

    void print();

    void DFS(T s);

    ///DFS(T s, std::unordered_set<T>& visited, bool print = true);

    void DFSComplete();

    void BFS(T s);

    void BFSComplete();

    void BFS(T s, std::unordered_set<T>& visited);

    /*
    Weighted Graph
    No Negative Weight
    Calculates the shortest to all Vertices from source.
    */
    void dijkstra(T s);

    int connectedComponents();

    // For Unweighted Graph
    void shortestPathBFS(T s, T e);

    void topSortHelper(std::unordered_set<T>& visited, T s, int& i, std::unordered_map<T, int>& res);

    // Works for only Directed Graph with no Cycle
    std::unordered_map<T, int> topSort();

    // Single Source Shortes Path
    // Can be used with negative cycles
    // O(E.V)
    void bellmanFord(T s);

    // All Pairs Shortest Path
    // Can be used with negative cycles
    // O(V^3)

    //void floydWarshall();

    // O(V + E)


    std::unordered_set<T> getArticulationPoints();

    // O(V + E)
    // Bridge is the edge, whose removal increases the number of connected components in the graph.
    std::vector<std::pair<T, T>> getBridges();
    

};

// For Priority Queue
template <typename T> class Compare {
public:
    bool operator() (std::pair<T, int> p1, std::pair<T, int> p2);

};

template <typename T>
bool Compare<T>::operator() (std::pair<T, int> p1, std::pair<T, int> p2) {
    return p1.second > p2.second;
}



template <typename T>
T Graph<T>::min(T& a, T& b) {
        if(a < b) {return a;}
        return b;
}

template <typename T>
Graph<T>::Graph(bool d, bool w) {directed = d; weighted = w;}

template <typename T>
void Graph<T>::addVertex(T v) {adjList[v] = {}; vertices++;}

template <typename T>
void Graph<T>::addEdge(T u, T v, int W) {
    adjList[u].push_back( std::make_pair(v, W) );
    if(!directed) {
        adjList[v].push_back( std::make_pair(u, W) );
    }
}

template <typename T>
void Graph<T>::print() {
    for(auto [u, V]: adjList) {
        std::cout << u << ": ";
        for(std::pair<T, int> p: V) {
            if(weighted) {
                std::cout << "{ " << p.first << ", " << p.second << " } ";
            }
            else {
                std::cout << p.first << ' ';
            }
        }
        std::cout << '\n';
    }
} 

template <typename T>
void Graph<T>::DFS(T s) {
    std::unordered_set<T> visited;
    DFS(s, visited);
    std::cout << '\n';
}

template <typename T>
void Graph<T>::DFS(T s, std::unordered_set<T>& visited, bool print) {
    visited.insert(s);
    if(print) {std::cout << s << ' ';}
    

    for(std::pair<T, int> p: adjList[s]) {
        if(visited.find(p.first) == visited.end()) {
            DFS(p.first, visited, print);
        }
    }

}

template <typename T>
void Graph<T>::DFSComplete() {
    std::unordered_set<T> visited;

    for (auto [u, V]: adjList) {
        for(std::pair<T, int> p: V) {
            if(visited.find(p.first) == visited.end()) {
                DFS(p.first, visited);
            }
        }
        
    }

    std::cout << '\n';

}

template <typename T>
void Graph<T>::BFS(T s) {
    std::unordered_set<T> visited;
    std::queue<T> q;
    q.push(s);
    while(!q.empty()) {
        T curr = q.front();
        q.pop();
        visited.insert(curr);
        std::cout << curr << ' ';

        for(std::pair<T, int> p: adjList[curr]) {
            if(visited.find(p.first) == visited.end()) {q.push(p.first);}
        }

    }
    std::cout << '\n';
}

// For Complete BFS
template <typename T>
void Graph<T>::BFS(T s, std::unordered_set<T>& visited) {
    std::queue<T> q;
    q.push(s);
    visited.insert(s);
    while(!q.empty()) {
        T curr = q.front();
        q.pop();
        visited.insert(curr);
        std::cout << curr << ' ';

        for(std::pair<T, int> p: adjList[curr]) {
            if(visited.find(p.first) == visited.end()) {q.push(p.first); visited.insert(p.first);}
        }

    }
}

template <typename T>
void Graph<T>::BFSComplete() {
    std::unordered_set<T> visited;
    //queue<T> q;

    for(auto [u, V]: adjList) {
        if(visited.find(u) == visited.end()) {BFS(u, visited);}

    }

    std::cout << '\n';

} 

template <typename T>
int Graph<T>::connectedComponents() {
    int count = 0;

    std::unordered_set<T> visited;
    for(auto [k, v]: adjList) {
        if(visited.find(k) == visited.end()) {
            count++;
            DFS(k, visited, false);
        }
    }

    return count;
}

template <typename T>
void Graph<T>::dijkstra(T s) {
    if(!weighted) {
        std::cout << "Dijkstra not applicable on unweighted graph.\n";
        return;
    }

        std::unordered_map<T, int> dist;
        for(auto [k, v]: adjList) {dist[k] = INT_MAX;}

        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, Compare<T> > pq;
        dist[s] = 0;
        pq.push( std::make_pair(s, 0) );

        T u, v;
        int w, d;
        while(!pq.empty()) {
            u = pq.top().first;
            d = pq.top().second;
            pq.pop();

            for(std::pair<T, int> p: adjList[u]) {
                v = p.first;
                w = p.second;
                if( dist[v] > d + w ) {
                    dist[v] = d + w;
                    pq.push( std::make_pair(v, dist[v]) );
                }
            }

        }

        std::cout << "Shortest Path\n";
        for(auto [k, v]: dist) {
            std::cout << k << ": " << v << '\n';
        }
}

template <typename T>
void Graph<T>::shortestPathBFS(T s, T e) {
    std::unordered_map<T, T> parent;
    std::unordered_set<T> visited;

    parent[s] = s;
    std::queue<T> q;
    q.push(s);
    visited.insert(s);
    T curr, next;

    while(!q.empty()) {
        curr = q.front();
        q.pop();
        if(curr == e) {break;}

        for(std::pair<T, int> p: adjList[curr]) {
            next = p.first;
            if(visited.find(next) == visited.end()) {
                q.push(next);
                visited.insert(next);
                parent[next] = curr;
            }
        }
    }

    if(parent.find(e) != parent.end()) {
        std::vector<T> path;
        T curr = e;
        while(true) {
            path.push_back(curr);
            if(curr == parent[curr]) {break;}
            curr = parent[curr];
        }

        for(int i = path.size() - 1; i >= 0; i--) {
            std::cout << path[i] << ' ';
        }
        std::cout << '\n';

    }
    else {
        std::cout << "Path Doesn't Exist\n";
    }

}

template <typename T>
void Graph<T>::topSortHelper(std::unordered_set<T>& visited, T s, int& i, std::unordered_map<T, int>& res) {
    visited.insert(s);
    for(auto p: adjList[s]) {
        if(visited.find(p.first) == visited.end()) {
            topSortHelper(visited, p.first, i, res);
        }
    }
    res[s] = i--;
}

template <typename T>
std::unordered_map<T, int> Graph<T>::topSort() {
    int i = vertices - 1;
    std::unordered_map<T, int> result;
    std::unordered_set<T> visited;

    for(auto [k, v]: adjList) {
        if(visited.find(k) == visited.end()) {
            topSortHelper(visited, k, i, result);
        }
    }

    return result;

}


template <typename T>
void Graph<T>::bellmanFord(T s) {
    std::unordered_map<T, int> dist;
    for(auto [k, v]: adjList) {
        dist[k] = INT_MAX;
    }
    dist[s] = 0;

    for(int i = 0; i < vertices - 1; i++) {
        for(auto [k, v]: adjList) {
            if(dist[k] == INT_MAX) {continue;}
            for(std::pair<T, int> p: v) {
                int newDist = dist[k] + p.second;
                if(newDist < dist[p.first]) {
                    dist[p.first] = newDist;
                }
            }
        }
    }

    for(int i = 0; i < vertices - 1; i++) {
        for(auto [k, v]: adjList) {
            if(dist[k] == INT_MAX) {continue;}
            for(std::pair<T, int> p: v) {
                int newDist = dist[k] + p.second;
                if(newDist < dist[p.first]) {
                    dist[p.first] = INT_MIN;
                }
            }
        }
    }

    std::cout << "Shortest Distance\n";
    for(auto [k, v]: adjList) {
        std::cout << k << ": " << dist[k] << '\n';
    }

}

/*
Articulation Points
-> A node such that removing it, increases the connected components.

Conditions:
1. Node U is the root (DFS) and has atleast 2 children (Subgraph).

2. Node U is not the root of DFS tree and it has a child V such that no vertex in subtree rooted with V has a beckedge to one of the ancestors of U.


Checks:
1. Keep the child count of the node, If the child count > 1 then check is it a root.

2. For each node
   We'll keep track of its discovery time and earliest accessible node to get backedge.



**Special**
Don't consider the child to parent edge.
*/

template <typename T>
void Graph<T>::DFSForArticulationPoints(T u, std::unordered_map<T, int>& disc, std::unordered_map<T, T>& parent, std::unordered_map<T, int>& low, std::unordered_set<T>& articulationPoints) {
    static int time = 0;
    disc[u] = time;
    low[u] = time;
    time++;
    int children = 0;
    for(auto [v, w]: adjList[u]) {
        if(disc.find(v) == disc.end()) {
            // Unvisited Node
            children++;
            parent[v] = u;
            
            DFSForArticulationPoints(v, disc, parent, low, articulationPoints);
            low[u] = min(low[u], low[v]);

            if(parent.find(u) == parent.end() && children > 1) {
                // u is Root
                articulationPoints.insert(u);
            }
            
            if(parent.find(u) != parent.end() && low[v] >= disc[u]) {
                articulationPoints.insert(u);
            }


        }
        else if(v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
        
    }

}


template <typename T>
std::unordered_set<T> Graph<T>::getArticulationPoints() {
    std::unordered_map<T, int> disc, low;
    std::unordered_map<T, T> parent;
    std::unordered_set<T> articulationPoints;

    for(auto [u, v]: adjList) {
        if(disc.find(u) == disc.end()) {
            DFSForArticulationPoints(u, disc, parent, low, articulationPoints);
        }
    }   

    std::cout << "Articulation Points:\n";
    for(T u: articulationPoints) {
        std::cout << u << ' ';
    }
    std::cout << '\n';
    return articulationPoints;

}


template <typename T>
void Graph<T>::DFSForBridge(T u, std::unordered_map<T, int>& disc, std::unordered_map<T, int>& low, std::unordered_map<T, T>& parent, std::unordered_set<std::pair<T, T>>& bridges) {
    static int time = 0;
    disc[u] = time;
    low[u] = time;
    time++;

    for(auto [v, W]: adjList[u]) {
        if(disc.find(v) == disc.end()) {
            parent[v] = u;
            DFSForBridge(v, disc, low, parent, bridges);
            low[u] = min(low[u], low[v]);

            if(low[v] > disc[u]) {
                bridges.insert({u, v});
            }

        }
        else if(u != parent[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

template <typename T>
void Graph<T>::DFSForBridge(std::unordered_map<T, int>& ids, std::unordered_map<T, int>& low, std::unordered_set<T>& visited, std::vector<std::pair<T, T>>& b, int& id, T curr, T parent, bool hasParent) {
    visited.insert(curr);
    id++;
    low[curr] = id; ids[curr] = id;

    for(std::pair<T, int> p: adjList[curr]) {
        if(hasParent && (p.first == parent) ) {continue;}
        if(visited.find(p.first) == visited.end()) {
            DFSForBridge(ids, low, visited, b, id, p.first, curr, true);
            low[curr] = min(low[curr], low[p.first]);
            if(ids[curr] < low[p.first]) {
                b.push_back( {curr, p.first} );
            }
        }
        else {
            low[curr] = min(low[curr], ids[p.first]);
        }
    }
}

template <typename T>
std::vector<std::pair<T, T>> Graph<T>::getBridges() {
        std::unordered_map<T, int> ids;
        std::unordered_map<T, int> low;
        std::unordered_set<T> visited;
        std::vector<std::pair<T, T>> b;
        int id = 0;
        for(auto& [k, v]: adjList) {
            if(visited.find(k) == visited.end()) {
                DFSForBridge(ids, low, visited, b, id, k, k, false);
            }
        }

        std::cout << "BRIDGES\n";
        for(std::pair<T, T>& p: b) {
            std::cout << p.first << ' ' << p.second << '\n';
        }

        return b;
}


# endif