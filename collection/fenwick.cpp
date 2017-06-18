#include <bits/stdc++.h>

using namespace std;

template <class T>
class Fenwick {

private:
	vector<T> data;
	vector<T> dataMul;
	int len;
	bool range;

	void internalUpdate(int at, T mul, T add) {
		while (at < len) {
			dataMul[at] += mul;
			data[at] += add;
			at |= (at + 1);
		}
	}

	T queryStd(int at) {
		T res = 0;
		while (at >= 0) {
			res += data[at];
			at = (at & (at + 1)) - 1;
		}
		return res;
	}

	T queryIfRange(int at) {
		T mul = 0;
		T add = 0;
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

	void update(int at, T by) {
		if (range) throw;
		while (at < len) {
			data[at] += by;
			at |= (at + 1);
		}
	}

	void updateRange(int left, int right, T by) {
		if (!range) throw;
		internalUpdate(left, by, -by * (left - 1));
		internalUpdate(right, -by, by * right);
	}

	T query(int at) {
		return range ? queryIfRange(at) : queryStd(at);
	}

	T queryRange(int left, int right) {
		return query(right) - query(left - 1);
	}
};

int main() {
	Fenwick<int> fen(10);
}