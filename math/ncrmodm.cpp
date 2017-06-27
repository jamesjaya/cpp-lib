#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

ll fex(ll base, ll exp, ll mod) {
	if (exp == 1) return base;
	if (exp == 0) return 1ll;
	ll ret = fex(base, exp / 2, mod);
	ret *= ret;
	ret %= mod;
	if (exp % 2) {
		ret *= base;
		ret %= mod;
	}
	return ret;
}

ll invmod(ll operand, ll mod) {
	return fex(operand, mod - 2, mod);
}

struct Lucas {
	ll m, sz;
	vector<ll> fact, ifact;

	Lucas(ll m, ll sz) : m(m), sz(sz), fact(sz), ifact(sz) {
		generateFact();
	}

	void generateFact() {
		fact[0] = ifact[0] = 1;
		for (int i = 1; i < sz; i++) {
			fact[i] = (fact[i-1] * i) % m;
			ifact[i] = invmod(fact[i], m);
		}
	}

	ll ncr(int n, int r) {
		if (r > n) {
			return 0;
		}
		return ((fact[n] * ifact[n-r]) % m * ifact[r]) % m;
	}

	vector<ll> decompose(ll num) {
		vector<ll> ret;
		while (num > 0) {
			ret.push_back(num % m);
			num /= m;
		}
		return ret;
	}

	ll calculate(ll n, ll c) {
		vector<ll> dn = decompose(n);
		vector<ll> dc = decompose(c);

		int size = (int) dc.size();
		ll ret = 1;
		for (int i = 0; i < size; i++) {
			ret *= ncr(dn[i], dc[i]);
			ret %= m;
		}

		return ret;
	}
};

int main() {
	// Sanity test
	cout << "Sanity test, mod 1e9+7\n";
	Lucas lucas(1e9+7, 10);
	cout << "C(5,2) = 10 ----> " << lucas.calculate(5, 2) << '\n';
	cout << "C(6,3) = 20 ----> " << lucas.calculate(6, 3) << '\n';
	cout << "C(3,0) =  1 ----> " << lucas.calculate(3, 0) << '\n';
	cout << "C(3,1) =  3 ----> " << lucas.calculate(3, 1) << '\n';

	// Real test
	cout << "Real test, mod 3\n";
	Lucas lucas2(3, 10);
	cout << "C(5,2) = 10 % 3 = 1 ----> " << lucas2.calculate(5, 2) << '\n';
	cout << "C(6,3) = 20 % 3 = 2 ----> " << lucas2.calculate(6, 3) << '\n';
	cout << "C(3,0) =  1 % 3 = 1 ----> " << lucas2.calculate(3, 0) << '\n';
	cout << "C(3,1) =  3 % 3 = 0 ----> " << lucas2.calculate(3, 1) << '\n';
}