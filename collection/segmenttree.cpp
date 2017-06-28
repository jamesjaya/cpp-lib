#include <bits/stdc++.h>

using namespace std;

template <class T>
struct SegmentTree {
	inline int m(int left, int right) { return (left + right) >> 1; }
	inline int l(int current) { return 2 * current + 1; }
	inline int r(int current) { return 2 * current + 2; }

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
		return old + change;
	}

	T queryOperation(T leftValue, T rightValue) {
		return leftValue + rightValue;
	}

	T deltaEffectOnSegment(T delta, int segmentLength) {
		if (delta == getNeutralDelta()) return getNeutralDelta();
		return delta * segmentLength;
	}

	T getNeutralDelta() {
		return 0;
	}
};

int main() {
	SegmentTree<int> tree(10);
	for (int i = 0; i < 5; i++) {
		int len = rand() % 3 + 2;
		cout << "modify " << i << ' ' << i+len << ' ' << 1 << endl;
		tree.modify(i, i + len, 1);
	}
	for (int i = 0; i < 10; i++) {
		cout << "query " << i << ',' << i << " " << tree.query(i, i) << endl;
	}
}