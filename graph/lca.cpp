#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

template <class T>
class RMQ {
private:
	vector<T> a;
	vector<vector<int>> t;
	int n;

	void build() {
		for (int j = 1; (1<<j) <= n; j++) {
			for (int i = 0; i + (1<<j) - 1 < n; i++) {
				if (a[t[i][j-1]] < a[t[i+(1<<(j-1))][j-1]]) {
					t[i][j] = t[i][j-1];
				} else {
					t[i][j] = t[i+(1<<(j-1))][j-1];
				}
			}
		}
	}

public:
	RMQ() {}
	RMQ(int num, T A[]) : a(num, 0), t(num, vector<int>((32 - __builtin_clz(n)), 0)) {
		n = num;

		for (int i = 0; i < n; i++) {
			a[i] = A[i];
			t[i][0] = i;
		}
		
		build();
	}

	RMQ(int num, const vector<T>& A) : a(num, 0), t(num, vector<int>((32 - __builtin_clz(n)), 0)) {
		n = num;

		for (int i = 0; i < n; i++) {
			a[i] = A[i];
			t[i][0] = i;
		}

		build();
	}

	int query(int i, int j) {
		int k = (int)floor(log((double)j-i+1) / log(2.0));
		if (a[t[i][k]] <= a[t[j-(1<<k)+1][k]]) {
			return t[i][k];
		} else {
			return t[j-(1<<k)+1][k];
		}
	}
};

class LCA {
private:
	int n;
	int idx;
	vector<vector<int>> g;
	vector<int> l, e, h;
	RMQ<int> tl;

	void dfs(int cur, int prev, int depth) {
		h[cur] = idx;
		e[idx] = cur;
		l[idx++] = depth;

		for (int next: g[cur]) {
			if (next != prev) {
				dfs(next, cur, depth + 1);
				e[idx] = cur;
				l[idx++] = depth;
			}
		}
	}

public:
	LCA(int numNodes, vector<vector<int>>& adj) : l(2 * numNodes), e(2 * numNodes), h(numNodes) {
		n = numNodes;
		g = adj;
		idx = 0;

		dfs(0, -1, 0);
		tl = RMQ<int>(2 * n, l);
	}

	int query(int a, int b) {
		if (h[b] < h[a]) swap(a, b);
		return e[tl.query(h[a], h[b])];
	}
};

int main() {
	vector<vector<int>> tree(10);
	tree[0].push_back(1);
	tree[0].push_back(2);
	tree[1].push_back(3);
	tree[3].push_back(4);
	tree[3].push_back(5);
	tree[2].push_back(6);
	tree[2].push_back(7);
	tree[6].push_back(8);
	tree[8].push_back(9);

	LCA lca(10, tree);
	cout << lca.query(5, 9) << '\n';
	cout << lca.query(3, 4) << '\n';
	cout << lca.query(1, 2) << '\n';
	cout << lca.query(0, 9) << '\n';
	cout << lca.query(7, 2) << '\n';
	cout << lca.query(2, 7) << '\n';
}