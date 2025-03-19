class Solution {
private:
    int find(int node, vector<int>& parent) {
        if (parent[node] == node) return node;
        return parent[node] = find(parent[node], parent); // Path compression
    }

    void Union(int& ans, int u, int v, vector<int>& parent, vector<int>& rank) {
        int x = find(u, parent);
        int y = find(v, parent);  // Fixed: Use find(v, parent)

        if (x == y) {  // If they are in the same set, cycle detected
            ans++;
            return;
        }

        // Union by Rank
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else if (rank[x] < rank[y]) {  // Fixed condition
            parent[x] = y;
        } else {
            parent[x] = y;
            rank[y]++;
        }
    }

public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) return -1; // Not enough edges to connect all nodes

        vector<int> parent(n, 0);
        vector<int> rank(n, 0);

        for (int i = 0; i < n; i++) {  // Fixed initialization
            parent[i] = i;
        }

        int ans = 0;
        for (auto it : connections) {
            int from = it[0];
            int to = it[1];
            Union(ans, from, to, parent, rank);
        }

        // Count the number of connected components
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] == i) components++;
        }

        if(ans >= components -1 ){
            return components-1;
        }
        return -1;
    }
};

