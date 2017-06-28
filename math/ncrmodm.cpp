#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

bitset<100000> bs;
vector<ll> primes;

void sieve(ll sz) {
	bs[0] = bs[1] = 1;
	for (ll i = 2; i <= sz; i++) {
		if (!bs[i]) {
			for (ll j = i*i; j <= sz; j+=i) {
				bs[j] = 1;
			}
			primes.push_back(i);
		}
	}
}

ll fex(ll base, ll exp, ll mod = 1e18) {
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

ll invmod_ex(ll operand, ll mod) {
	ll b0 = mod, t, q;
	ll x0 = 0, x1 = 1;
	if (mod == 1) return 1;
	while (operand > 1) {
		q = operand / mod;
		t = mod, mod = operand % mod, operand = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

vector<ii> primeFactorialization(ll num) {
	vector<ii> ret;
	int p = 0;
	while (num > 1) {
		int cnt = 0;
		while (num % primes[p] == 0) {
			num /= primes[p];
			cnt++;
		}
		if (cnt) ret.emplace_back(primes[p], cnt);
		p++;
	}
	return ret;
}

ll chinese_remainder(vector<ll>& mods, vector<ll>& rems) {
	ll prod = 1, sum = 0;
	
	for (ll mod: mods) {
		prod *= mod;
	}
	for (int i = 0; i < (int) rems.size(); i++) {
		ll p = prod / mods[i];
		sum += rems[i] * invmod_ex(p, mods[i]) * p;
	}

	return sum % prod;
}

struct Lucas {
	ll m, sz;
	vector<ll> fact, ifact;
	const static ll maxSz = 100000;

	Lucas(ll m) : m(m), sz(min(m + 1, 100000ll)), fact(min(m + 1, 100000ll)), ifact(min(m + 1, 100000ll)) {
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

	ll calculate(ll n, ll r) {
		vector<ll> dn = decompose(n);
		vector<ll> dr = decompose(r);

		int size = (int) dr.size();
		ll ret = 1;
		for (int i = 0; i < size; i++) {
			ret *= ncr(dn[i], dr[i]);
			ret %= m;
		}
		return ret;
	}
};

struct LucasAux {
	int m;
	vector<ll> mods;
	vector<Lucas> lucases;

	LucasAux(int m) : m(m) {
		if (primes.size() == 0) sieve(100000);
		vector<ii> pfactors = primeFactorialization(m);

		for (ii pfactor: pfactors) {
			if (pfactor.second > 1) throw;
			mods.push_back(pfactor.first);
			lucases.emplace_back(pfactor.first);
		}
	}

	ll calculate(ll n, ll r) {
		vector<ll> rems;
		for (Lucas lucas: lucases) {
			rems.push_back(lucas.calculate(n, r));
		}
		return chinese_remainder(mods, rems);
	}
};

int main() {
	sieve(100000);

	// Sanity test
	cout << "Sanity test, mod 1e9+7\n";
	Lucas lucas(1e9+7);
	cout << "C(8,2) = 56 ----> " << lucas.calculate(8, 3) << '\n';
	cout << "C(6,3) = 20 ----> " << lucas.calculate(6, 3) << '\n';
	cout << "C(3,0) =  1 ----> " << lucas.calculate(3, 0) << '\n';
	cout << "C(3,1) =  3 ----> " << lucas.calculate(3, 1) << '\n';

	// Real test
	cout << "Real test, mod 3\n";
	Lucas lucas2(3);
	cout << "C(8,2) = 56 % 3 = 1 ----> " << lucas2.calculate(8, 3) << '\n';
	cout << "C(6,3) = 20 % 3 = 2 ----> " << lucas2.calculate(6, 3) << '\n';
	cout << "C(3,0) =  1 % 3 = 1 ----> " << lucas2.calculate(3, 0) << '\n';
	cout << "C(3,1) =  3 % 3 = 0 ----> " << lucas2.calculate(3, 1) << '\n';

	// Real test
	cout << "Real test, mod 15\n";
	LucasAux lucasAux(15);
	cout << "C(8,2) = 56 % 15 = 11 ----> " << lucasAux.calculate(8, 3) << '\n';
	cout << "C(6,3) = 20 % 15 =  5 ----> " << lucasAux.calculate(6, 3) << '\n';
	cout << "C(3,0) =  1 % 15 =  1 ----> " << lucasAux.calculate(3, 0) << '\n';
	cout << "C(3,1) =  3 % 15 =  3 ----> " << lucasAux.calculate(3, 1) << '\n';
}
