#include <bits/stdc++.h>

using namespace std;

void rcounting_sort(vector<int>::iterator begin, vector<int>::iterator end, const int& radix, const int& xp) {
	vector<int> cnt(radix, 0);
	for (vector<int>::iterator i = begin; i < end; i++) {
		cnt[*i / xp % 10]++;
	}

	for (int i = 1; i <= 9; i++) {
		cnt[i] += cnt[i-1];
	}

	vector<int> tmp(end-begin);
	for (vector<int>::iterator i = end-1; i >= begin; i--) {
		tmp[--cnt[*i / xp % 10]] = *i;
	}

	int p = 0;
	for (vector<int>::iterator i = begin; i < end; i++) {
		*i = tmp[p++];
	}
}

void radix_sort(vector<int>::iterator begin, vector<int>::iterator end) {
	int maxElement = *max_element(begin, end);
	int radix = 10;
	for (int xp = 1; maxElement / xp > 0; xp *= 10) {
		rcounting_sort(begin, end, radix, xp);
	}
}

int main() {
	vector<int> v = {3,1,9,5,2,10,155,3000,9898,9999,7575,5690};
	vector<int> w = {1,32,199,95,5333,2222,2210,1552,3000,9898,9999,7575,5690};
	radix_sort(v.begin(), v.end());
	radix_sort(w.begin(), w.end());
	for (const int& a: v) {
		cout << a << ' ';
	}
	cout << endl;
	for (const int& a: w) {
		cout << a << ' ';
	}
	cout << endl;
}