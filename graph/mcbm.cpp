/* MCBM
   https://codejam.withgoogle.com/2018/challenges/0000000000007706/dashboard/0000000000045875
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int aug(int cur, const vector<vector<int>>& graph, vector<int>& match, vector<int>& visited) {
	if (visited[cur]) return 0;
	visited[cur] = 1;

	for (const int& next: graph[cur]) {
		if (match[next] == -1 || aug(match[next], graph, match, visited)) {
			match[next] = cur; return 1;
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int tt = 1; tt <= t; tt++) {
		int n;
		cin >> n;

		vector<vector<int>> arr(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> arr[i][j];
			}
		}

		int ans = 0;
		for (int num = -n; num <= n; num++) {
			vector<vector<int>> graph(n, vector<int>());
			int mcbm = 0;
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (arr[i][j] == num) {
						graph[i].push_back(j);
						cnt++;
					}
				}
			}

			vector<int> match(n, -1);
			for (int i = 0; i < n; i++) {
				vector<int> visited(n, 0);
				mcbm += aug(i, graph, match, visited);
			}

			ans += cnt - mcbm;
		}
		
		cout << "Case #" << tt << ": " << ans << "\n";
	}
}