#include <bits/stdc++.h>

using namespace std;

struct Fenwick {
	vector<int> data;
	int len;

	Fenwick(int l) {
		len = l;
		data.assign(l + 1, 0);
	}

	void update(int at, int by) {
		while (at < len) {
			data[at] += by;
			at |= (at + 1);
		}
	}

	int query(int at) {
		int res = 0;
		while (at >= 0) {
			res += data[at];
			at = (at & (at + 1)) - 1;
		}
		return res;
	}

	int queryRange(int l, int r) {
		return data[r] - data[l-1];
	}
};

int main() {
	
}