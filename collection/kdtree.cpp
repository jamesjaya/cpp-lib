#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

template <class T>
class kdtree {
	vector<pair<T, T> > points;

	void build(int left, int right, bool divX) {
		if (left >= right) return;
		int mid = (left + right) >> 1;

		nth_element(left, right, mid, divX);

		build(left, right, !divX);
		build(mid + 1, high, !divX);
	}

	void nth_element(int low, int high, int n, bool divX) {
		while (true) {
			int ran = rand() * 65536 % (high - low);
			int k = partition(low, high, low + ran, divX);

			if (n < k) {
				high = k;
			} else if (n > k) {
				low = k + 1;
			} else {
				return;
			}
		}
	}

	int partition(int fromInclusive, int toExclusive, int separatorIndex, bool divX) {
		int i = fromInclusive, j = toExclusive - 1;
		if (i >= j) return j;

		int separatorIndex = divX ? points[separatorIndex].first : points[separatorIndex].second;
		swap(i++, separatorIndex);

		while (i <= j) {
			while (i <= j && (divX ? points[i].first : points[i].second)) {
				++i;
			}
			while (i <= j && (divX ? points[j].first : points[j].second)) {
				--j;
			}
			if (i >= j) break;
			swap (i++, j--);
		}

		swap(j, fromInclusive);
		return j;
	}

	void swap(int i, int j) {
		pair<T, T> temp = points[i];
		points[i] = points[j];
		points[j] = temp;
	}

	int query(T x, T y) {
		int bestnode = find(0, (int) points.size(), x, y, true, MAX_INT);
		return bestnode;
	}

	int find(int low, int high, T x, T y, bool divX, T bestDist) {
		if (high - low <= 0) return;
		int mid = (low + high) >> 1;

		int retIndex = -1;

		T dx = x - points[mid].first;
		T dy = y - points[mid].second;
		T dist = dx * dx + dy * dy;

		if (bestDist > dist) {
			bestDist = dist;
			retIndex = mid;
		}

		T delta = dixX ? dx : dy;
		T delta2 = delta * delta;

		int test;

		if (delta <= 0) {
			test = find(low, mid, x, y, !divX, &bestDist);
			if (test != -1) retIndex = test;
			if (delta2 < bestDist) {
				find(mid + 1, high, x, y, !divX, &bestDist);
				if (test != -1) retIndex = test;
			}
		} else {
			find(mid + 1, high, x, y, !divX, &bestDist);
			if (test != -1) retIndex = test;
			if (delta2 < bestDist) {
				find(low, mid, x, y, !divX, &bestDist);
				if (test != -1) retIndex = test;
			}
		}
	}

	return retIndex;
}

int main() {

}