#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <unsigned int N>
class Prime {
	private:
	vector<int> primes;
	vector<int> minimum_prime_factor;
	bitset<N+1> prime_flag;

	void get_next_prime_factor(int number, vector<int>& prime_factors) {
		if (number <= 1) {
			return;
		}

		prime_factors.push_back(minimum_prime_factor[number]);
		get_next_prime_factor(number / minimum_prime_factor[number], prime_factors);
	}

	public:
	Prime(): minimum_prime_factor(N + 1, 0) {
		primes.reserve(N / log(N));

		for(int i = 2; i <= N; i++) {
			if (minimum_prime_factor[i] == 0) {
				minimum_prime_factor[i] = i;
				primes.push_back(i);
				prime_flag[i] = 1;
			}

			for (int j = 0; j < primes.size() && primes[j] <= minimum_prime_factor[i] && i * primes[j] <= N; j++) {
				minimum_prime_factor[i * primes[j]] = primes[j];
			}
		}
	}

	bool is_prime(int x) {
		return prime_flag[x];
	}

	vector<int> get_prime_factorialization(int x) {
		vector<int> prime_factors;
		get_next_prime_factor(x, prime_factors);
		return prime_factors;
	}


};

int main() {
	Prime<10000000> primes;
	cout << primes.is_prime(13) << endl;
	cout << primes.is_prime(15) << endl;
	
	cout << "Prime factorialization of 36 are:" << endl;
	vector<int> prime_factors_of_thirty_six = primes.get_prime_factorialization(36);
	for (const int& prime_factor: prime_factors_of_thirty_six) {
		cout << prime_factor << endl;
	}

	cout << "Prime factorialization of 123456 are:" << endl;
	vector<int> prime_factors_of_123456 = primes.get_prime_factorialization(123456);
	for (const int& prime_factor: prime_factors_of_123456) {
		cout << prime_factor << endl;
	}
}