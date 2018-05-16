#include <bits/stdc++.h>

using namespace std;

void dfs(int cur, int nomor, vector<vector<int>>& bug, vector<int>& compo) {
	compo[cur] = nomor;
	for (const int& next: bug[cur]) {
		if (!compo[next]) {
			dfs(next, nomor, bug, compo);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tt = 1; tt <= t; tt++) {
		int n, m;
		cin >> n >> m;

		vector<vector<int>> bug(2 * n, vector<int>());
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			int na = n + a;
			int nb = n + b;
			// find the actual boolean expression
			// this is for (a ^ ~b) v (~a ^ b)
			bug[na].push_back(b);
			bug[nb].push_back(a);
			bug[a].push_back(nb);
			bug[b].push_back(na);
		}

		vector<int> compo(2 * n, 0);
		int p = 1;
		for (int i = 0; i < 2 * n; i++) {
			if (!compo[i]) {
				dfs(i, p++, bug, compo);
			}
		}

		cout << "Scenario #" << tt << ":\n";
		bool sus = false;
		for (int i = 0; i < n; i++) {
			if (compo[i] == compo[i+n]) {
				sus = true; break;
			}
		}

		if (sus) {
			cout << "Suspicious bugs found!\n";
		} else {
			cout << "No suspicious bugs found!\n";
		}
	}
}