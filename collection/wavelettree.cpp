#include <bits/stdc++.h>

using namespace std;

const int DEBUG = 1;

template<class T>
class wavelet_tree {
	private:
	T low, high;
	wavelet_tree *left, *right;
	vector<T> freq;

	public:
	wavelet_tree(auto from, auto to, T low, T high): low(low), high(high) {
		if (DEBUG) {
			for (auto it = from; it != to; it++) {
				cout << *it << ' ';
			}
			cout << endl;
		}
	
		if (from >= to) {
			return;
		}

		freq.reserve(to - from + 1);
		freq.push_back(0);

		if (high == low) {
			for (auto it = from; it != to; it++) {
				freq.push_back(freq.back() + 1);
			}
			return;
		}

		T mid = (low + high) / 2;
		auto lessThanMid = [mid](T x) {
			return x <= mid;
		};

		for (auto it = from; it != to; it++) {
			freq.push_back(freq.back() + lessThanMid(*it));
		}

		auto pivot = stable_partition(from, to, lessThanMid);
		
		left = new wavelet_tree(from, pivot, low, mid);
		right = new wavelet_tree(pivot, to, mid + 1, high);
	}

	int less_than_equal(int l, int r, T k) {
		l++; r++;
		if (l > r || k < low) return 0;
		if (high <= k) return r - l + 1;
		int lb = freq[l-1];
		int rb = freq[r];
		return this->left->less_than_equal(lb + 1, rb, k) + this->right->less_than_equal(l-lb, r-rb, k);
	}
};

template<class T>
class wavelet_tree_builder {
	public:
	static wavelet_tree<T> build_wavelet_tree(vector<T>& arr) {
		T low = arr[0];
		T high = arr[0];
		for (auto element: arr) {
			low = min(low, element);
			high = max(high, element);
		}

		return wavelet_tree<T>(arr.begin(), arr.end(), low, high);
	}
};

int main() {
	vector<int> arr = {0, 0, 9, 1, 2, 1, 7, 6, 4, 8, 9, 4, 3, 7, 5, 9, 2, 7, 0, 5, 1, 0};
	wavelet_tree<int> wt = wavelet_tree_builder<int>::build_wavelet_tree(arr);
	cout << wt.less_than_equal(0, 6, 5) << endl;


}