#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

struct SuffixArray {
	inline bool leq(int a1, int a2, int b1, int b2) {
		return (a1 < b1) || (a1 == b1 && a2 <= b2);
	}

	inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
		return a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3));
	}

	void radixPass(vector<int>& src, vector<int>& dst, vector<int>& v, int pos, int n, int size) {
		vector<int> cnt(size + 1, 0);

		for (int i = 0; i < n; i++) {
			cnt[v[pos + src[i]]]++;
		}

		for (int i = 0, sum = 0; i <= size; i++) {
			int t = cnt[i];
			cnt[i] = sum;
			sum += t;
		}

		for (int i = 0; i < n; i++) {
			dst[cnt[v[pos + src[i]]]++] = src[i];
		}
	}

	void dc3(vector<int>& v, vector<int>& SA, int n, int size) {
		int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
		vector<int> s12(n02 + 3, 0), SA12(n02 + 3, 0), s0(n0, 0), SA0(n0, 0);

		for (int i = 0, j = 0; i < n + (n0 - n1); i++) {
			if (i % 3) s12[j++] = i;
		}

		radixPass(s12, SA12, v, 2, n02, size);
		radixPass(SA12, s12, v, 1, n02, size);
		radixPass(s12, SA12, v, 0, n02, size);

		int name = 0, c[3] = {-1, -1, -1};
		for (int i = 0; i < n02; i++) {
			bool newName = false;
			for (int j = 0; j < 3; j++) {
				newName = newName || (v[SA12[i] + j] != c[j]);
			}

			if (newName) {
				name++;
				for (int j = 0; j < 3; j++) {
					c[j] = v[SA12[i] + j];
				}
			}

			if (SA12[i] % 3 == 1) {
				s12[SA12[i] / 3] = name;
			} else {
				s12[SA12[i] / 3 + n0] = name;
			}
		}

		if (name < n02) {
			dc3(s12, SA12, n02, name);
			for (int i = 0; i < n02; i++) {
				s12[SA12[i]] = i + 1;
			}
		} else {
			for (int i = 0; i < n02; i++) {
				SA12[s12[i] - 1] = i;
			}
		}

		for (int i = 0, j = 0; i < n02; i++) {
			if (SA12[i] < n0) s0[j++] = 3 * SA12[i];
		}

		radixPass(s0, SA0, v, 0, n0, size);

		for (int p = 0, t = n0 - n1, k = 0; k < n; k++) {
			int i = (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2);
			int j = SA0[p];

			if (SA12[t] < n0 ? leq(v[i], s12[SA12[t] + n0], v[j], s12[j / 3]) : leq(v[i], v[i + 1], s12[SA12[t] - n0 + 1], v[j], v[j + 1], s12[j / 3 + n0])) {
				SA[k] = i;
				t++;
				if (t == n02) {
					for (k++; p < n0; p++, k++) {
						SA[k] = SA0[p];
					}
				}
			} else {
				SA[k] = j;
				p++;
				if (p == n0) {
					for (k++; t < n02; t++, k++) {
						SA[k] = (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2);
					}
				}
			}
		}
	}

	vector<int> array, lcp;
	string s;

	int transformAlphabet(char c) {
		return c - 'a' + 1;
	}

	SuffixArray(string s) : s(s), array((int) s.size(), 0), lcp((int) s.size(), 0) {
		int size = (int) s.size();
		vector<int> input(size + 3, 0);

		for (int i = 0; i < size; i++) {
			input[i] = transformAlphabet(s[i]);
		}

		dc3(input, array, size, 26);
		kasai();
	}

	void kasai() {
		int n = s.size(), k = 0;
		vector<int> rank(n);

		for (int i = 0; i < n; i++) rank[array[i]] = i;

		for (int i = 0; i < n; i++, k ? k-- : 0) {
			if(rank[i] == n-1) {
				k = 0; continue;
			}
			if (rank[i] + 1 >= n) {
				lcp[rank[i]] = 0;
			} else {
				int j = array[rank[i]+1];
				while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
				lcp[rank[i]] = k;
			}
		}
	}
};

int main() {
	// Codeforces 271D
	// http://codeforces.com/contest/271/submission/28165052
	ios_base::sync_with_stdio(0);
	string s, good; int k, gd[200];
	cin >> s >> good >> k;

	for (char i = 'a'; i <= 'z'; i++) {
		gd[i] = good[i - 'a'] - '0';
	}

	int sz = (int) s.size();
	int prevans = 0;
	int ans = 0;
	SuffixArray sa(s);
	for (int i = 0; i < sz; i++) {
		if (i == 0) {
			bool masuk = false;
			int cnt = 0;
			for (int j = sa.array[i]; j < sz; j++) {
				if (!gd[s[j]]) cnt++;
				if (cnt > k) {
					masuk = true;
					prevans = (j-1) - sa.array[i] + 1;
					ans += prevans;
					break;
				}
			}
			if (!masuk) {
				prevans = sz - sa.array[i];
				ans += prevans;
			}
		} else {
			bool masuk = false;
			int lcp = sa.lcp[i-1];
			int cnt = 0;
			for (int j = sa.array[i]; j < sz; j++) {
				if (!gd[s[j]]) cnt++;
				if (cnt > k) {
					masuk = true;
					prevans = (j-1) - sa.array[i] + 1 - lcp;
					if (prevans < 0) prevans = 0;
					ans += prevans;
					break;
				}
			}
			if (!masuk) {
				prevans = sz - sa.array[i] - lcp;
				if (prevans < 0) prevans = 0;
				ans += prevans;
			}
		}
	}
	cout << ans << '\n';
}