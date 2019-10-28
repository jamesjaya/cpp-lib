#include <iostream>

using namespace std;

int main() {
  int n = 4;
  int a[n][n];
  int d[n][n];
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      d[i][j] = a[i][j];
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << d[i][j] << ' ';
    }
    cout << endl;
  }
}