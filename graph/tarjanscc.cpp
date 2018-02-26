#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

class TarjanSCC {
private:
    vector<int> dfs_num, dfs_low, visited;
    stack<int> currentScc;
    int dfsNumberCounter;
    bool needMember;

    void dfs(const int& u, const vector<vector<int>>& graph) {
        dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
        currentScc.push(u);
        visited[u] = 1;

        for (const int& v: graph[u]) {
            if (dfs_num[v] == -1) dfs(v, graph);
            if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }

        if (dfs_low[u] == dfs_num[u]) {
            int sccid = sccs.size(), v;
            sccs.emplace_back();

            do {
                v = currentScc.top(); currentScc.pop(); visited[v] = 0;
                sccId[v] = sccid;
                if (needMember) sccs.back().emplace_back(v);
            } while (u != v);
        }
    }

public:
    vector<int> sccId;
    vector<vector<int>> sccs;

    int numSCC() {
        return (int) sccs.size();
    }

    TarjanSCC(const int& size, const vector<vector<int>>& graph, const bool& needMember = true) : dfs_num(size, -1), dfs_low(size, 0), visited(size, 0), sccId(size, -1), needMember(needMember) {
        dfsNumberCounter = 0;
        for (int i = 0; i < size; i++) {
            if (dfs_num[i] == -1) {
                dfs(i, graph);
            }
        }
    }

    TarjanSCC(const vector<vector<int>>& graph, const bool& needMember = true) : TarjanSCC((int) graph.size(), graph, needMember) {}
};

int main() {
    vector<vector<int>> adj(6);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[2].push_back(3);
    adj[3].push_back(4);
    adj[4].push_back(5);
    TarjanSCC scc(adj);
    cout << scc.numSCC() << endl;
    for (int i = 0; i < 6; i++){
        cout << i << ": " << scc.sccId[i] << endl;
    }
}