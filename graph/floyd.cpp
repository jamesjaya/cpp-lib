#include <iostream>

using namespace std;

int main() {
  int a[100][100];
  int d[100][100];

  a = d;

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
}