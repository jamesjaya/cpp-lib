//#include <bits/stdc++.h>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iostream>

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
        sum += rems[i] * invmod(p, mods[i]) * p;
    }

    return sum % prod;
}

struct Lucas {
	ll m, k, sz, pw;
	vector<ll> fact, ifact;
    const static ll maxSz = 100000;

	Lucas(ll m, ll k) : m(m), k(k), sz(min(m, 100000ll)), fact(min(m, 100000ll)), ifact(min(m, 100000ll)) {
		generateFact();
        if (m == 2) {
            pw = k / 2;
        } else if (m == 3) {
            pw = (k - 1) / 2;
        } else {
            pw = (k - 1) / 3;
        }
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
        bool first = true;
        while (num > 0) {
            ret.push_back((num % m) * fex(m, pw, 1e9+7));
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

struct LucasAux {
    static ll process(ll n, ll r, ll m) {
        vector<ii> pfactors = primeFactorialization(m);

        vector<ll> mods, rems;
        for (ii pfactor: pfactors) {
            mods.push_back(fex(pfactor.first, pfactor.second, m));

            Lucas lucas(pfactor.first, pfactor.second);
            rems.push_back(lucas.calculate(n, r));
        }

        return chinese_remainder(mods, rems);
    }
};

int main() {
    sieve(100000);

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

    cout << LucasAux::process(5, 2, 30) << '\n';
}
