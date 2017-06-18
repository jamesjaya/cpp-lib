#include <bits/stdc++.h>

using namespace std;

class Fenwick {

private:
	vector<int> data;
	vector<int> dataMul;
	int len;
	bool range;

	void internalUpdate(int at, int mul, int add) {
		while (at < len) {
			dataMul[at] += mul;
			data[at] += add;
			at |= (at + 1);
		}
	}

	int queryStd(int at) {
		int res = 0;
		while (at >= 0) {
			res += data[at];
			at = (at & (at + 1)) - 1;
		}
		return res;
	}

	int queryIfRange(int at) {
		int mul = 0;
		int add = 0;
		int start = at;

		while (at >= 0) {
			mul += dataMul[at];
			add += data[at];
			at = (at & (at + 1)) - 1;
		}
		return mul * start + add;
	}

public:
	Fenwick(int len, bool range = false) {
		this->len = len;
		this->range = range;
		data.assign(len + 1, 0);
		if (range) dataMul.assign(len + 1, 0);
	}

	void update(int at, int by) {
		if (range) throw;
		while (at < len) {
			data[at] += by;
			at |= (at + 1);
		}
	}

	void updateRange(int left, int right, int by) {
		if (!range) throw;
		internalUpdate(left, by, -by * (left -1));
		internalUpdate(right, -by, by * right);
	}

	int query(int at) {
		return range ? queryIfRange(at) : queryStd(at);
	}

	int queryRange(int l, int r) {
		return query(r) - query(l-1);
	}
};

int main() {
	
}