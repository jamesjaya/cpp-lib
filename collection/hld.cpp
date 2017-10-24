#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

template <class T>
struct SegmentTree {
	inline int m(int left, int right) { return (left + right) >> 1; }
	inline int l(int current) { return 2 * current + 1; }
	inline int r(int current) { return 2 * current + 2; }

	SegmentTree() {}

	SegmentTree(int size) : size(size), value(4 * size, 0), delta(4 * size, getNeutralDelta()) {
		init(0, 0, size - 1);
	}

	void init(int root, int left, int right) {
		if (left == right) {
			value[root] = 0;
			delta[root] = getNeutralDelta();
		} else {
			int mid = m(left, right);
			init(l(root), left, mid);
			init(r(root), mid + 1, right);
			value[root] = queryOperation(value[l(root)], value[r(root)]);
			delta[root] = getNeutralDelta();
		}
	}

	void modify(int from, int to, T delta) {
		modify(from, to, delta, 0, 0, size - 1);
	}

	void modify(int from, int to, T delta, int root, int left, int right) {
		if (from == left && to == right) {
			this->delta[root] = joinDeltas(this->delta[root], delta);
			return;
		}
		pushDelta(root, left, right);
		int mid = m(left, right);
		if (from <= mid)
			modify(from, min(to, mid), delta, l(root), left, mid);
		if (to > mid)
			modify(max(from, mid + 1), to, delta, r(root), mid + 1, right);
		value[root] = queryOperation(
			joinValueWithDelta(value[l(root)], deltaEffectOnSegment(this->delta[l(root)], mid - left + 1)),
			joinValueWithDelta(value[r(root)], deltaEffectOnSegment(this->delta[r(root)], right - mid)));
	}

	T query(int from, int to) {
		return query(from, to, 0, 0, size - 1);
	}

	T query(int from, int to, int root, int left, int right) {
		if (from == left && to == right)
			return joinValueWithDelta(value[root], deltaEffectOnSegment(delta[root], right - left + 1));
		pushDelta(root, left, right);
		int mid = m(left, right);
		if (from <= mid && to > mid)
			return queryOperation(query(from, min(to, mid), l(root), left, mid), query(max(from, mid + 1), to, r(root), mid + 1, right));
		else if (from <= mid)
			return query(from, min(to, mid), l(root), left, mid);
		else if (to > mid)
			return query(max(from, mid + 1), to, r(root), mid + 1, right);
	}

	T joinValueWithDelta(T value, T delta) {
		if (delta == getNeutralDelta()) return value;
		return modifyOperation(value, delta);
	}

	T joinDeltas(T delta1, T delta2) {
		if (delta1 == getNeutralDelta()) return delta2;
		if (delta2 == getNeutralDelta()) return delta1;
		return modifyOperation(delta1, delta2);
	}

	void pushDelta(int root, int left, int right) {
		value[root] = joinValueWithDelta(value[root], deltaEffectOnSegment(delta[root], right - left + 1));
		delta[l(root)] = joinDeltas(delta[l(root)], delta[root]);
		delta[r(root)] = joinDeltas(delta[r(root)], delta[root]);
		delta[root] = getNeutralDelta();
	}

	int size;
	vector<T> value;
	vector<T> delta;

	T modifyOperation(T old, T change) {
		return change;
	}

	T queryOperation(T leftValue, T rightValue) {
		return leftValue ^ rightValue;
	}

	T deltaEffectOnSegment(T delta, int segmentLength) {
		if (delta == getNeutralDelta()) return getNeutralDelta();
		return delta;
	}

	T getNeutralDelta() {
		return 0;
	}
};

template <class T, int V>
class HeavyLight {
  int parent[V], heavy[V], depth[V];
  int root[V], treePos[V];
  SegmentTree<T> tree;

  int dfs(const vector<vector<int>>& graph, int v) {
    int size = 1, maxSubtree = 0;
    for (int u : graph[v]) if (u != parent[v]) {
      parent[u] = v;
      depth[u] = depth[v] + 1;
      int subtree = dfs(graph, u);
      if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
      size += subtree;
    }
    return size;
  }

  template <class BinaryOperation>
  void processPath(int u, int v, BinaryOperation op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v);
      op(treePos[root[v]], treePos[v]);
    }
    if (u == v) return;
    op(min(treePos[v], treePos[u]) + 1, max(treePos[u], treePos[v]));
    // op(min(treePos[v], treePos[u]), max(treePos[u], treePos[v])); // Values at vertices
  }

public:
	void debug() {
		cout << "Parent: ";
		for (int i = 0; i < V; i++) {
			cout << parent[i] << ' ';
		}
		cout << endl;

		cout << "Heavy: ";
		for (int i = 0; i < V; i++) {
			cout << heavy[i] << ' ';
		}
		cout << endl;

		cout << "Depth: ";
		for (int i = 0; i < V; i++) {
			cout << depth[i] << ' ';
		}
		cout << endl;

		cout << "Root: ";
		for (int i = 0; i < V; i++) {
			cout << root[i] << ' ';
		}
		cout << endl;

		cout << "Treepos: ";
		for (int i = 0; i < V; i++) {
			cout << treePos[i] << ' ';
		}
		cout << endl;
	}

  void init(const vector<vector<int>>& graph) {
    int n = graph.size();
    fill_n(heavy, n, -1);
    parent[0] = -1;
    depth[0] = 0;
    dfs(graph, 0);
    for (int i = 0, currentPos = 0; i < n; ++i)
      if (parent[i] == -1 || heavy[parent[i]] != i)
        for (int j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          treePos[j] = currentPos++;
        }
    tree = SegmentTree<T>(n);
  }

  void set(int v, const T& value) {
    tree.modify(treePos[v], treePos[v], value);
  }

  void modifyPath(int u, int v, const T& value) {
    processPath(u, v, [this, &value](int l, int r) { 
    	tree.modify(l, r, value); });
  }

  T queryPath(int u, int v) {
    T res = 0;
    processPath(u, v, [this, &res](int l, int r) { 
    	res ^= tree.query(l, r); });
    return res;
  }
};

int main() {
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<vector<int>> g(n);
		priority_queue<ii> pq;
		int a[n], b[n];
		for (int i = 0; i < n-1; i++) {
			int cost;
			cin >> a[i] >> b[i] >> cost;
			a[i]--; b[i]--;
			g[a[i]].push_back(b[i]);
			g[b[i]].push_back(a[i]);
			pq.push(ii(-cost, i));
		}

		HeavyLight<int, 100000> hld;
		hld.init(g);

		int q;
		cin >> q;

		priority_queue<pair<ii, ii>> qq;

		for (int i = 0; i < q; i++) {
			int a, b, k;
			cin >> a >> b >> k;
			a--; b--;
			qq.push(make_pair(ii(-k, i), ii(a, b)));
		}

		int ans[q];

		while (!qq.empty()) {
			while (!pq.empty() && -pq.top().first <= -qq.top().first.first) {
				hld.modifyPath(a[pq.top().second], b[pq.top().second], -pq.top().first);
				pq.pop();
			}
			ans[qq.top().first.second] = hld.queryPath(qq.top().second.first, qq.top().second.second);

			qq.pop();
		}

		for (int i = 0; i < q; i++) {
			cout << ans[i] << '\n';
		}
	}
}