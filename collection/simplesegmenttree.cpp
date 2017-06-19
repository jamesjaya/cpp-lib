#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

// Zero based
template <class T>
class SimpleSegmentTree {
private:
	vector<T> t;
	int n;

	void build() {
		for (int i = n - 1; i > 0; --i) {
			t[i] = min(t[i<<1], t[i<<1|1]);
		}
	}

public:
	SimpleSegmentTree() {}
	SimpleSegmentTree(int num, T* a) {
		n = num;
		t.assign(2 * n, 0);
		for (int i = 0; i < n; i++) {
			t[i + n] = a[i];
		}
		build();
	}

	SimpleSegmentTree(int num, const vector<T>& a) {
		n = num;
		t.assign(2 * n, 0);
		for (int i = 0; i < n; i++) {
			t[i + n] = a[i];
		}
		build();
	}

	void modify(int p, T value) {
		for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
	}

	// Zero based, [l, r]
	T query(int l, int r) {
		r++;
		T res = INT_MAX; // Adjust accordingly: INT_MAX, LLONG_MAX
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res = min(res, t[l++]);
			if (r&1) res = min(res, t[--r]);
		}
		return res;
	}
};

int main() {
	ll a[5] = {2,3,4,1,5};
	SimpleSegmentTree<ll> segmentTree(5, a);
	cout << segmentTree.query(1, 2) << endl;
	cout << segmentTree.query(0, 4) << endl;
	cout << segmentTree.query(2, 4) << endl;
}