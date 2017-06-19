#include <bits/stdc++.h>

using namespace std;

template <class T>
class RMQ {
private:
  vector<T> a;
  vector<vector<int>> t;
  int n;

  void build() {
    for (int j = 1; (1<<j) <= n; j++) {
      for (int i = 0; i + (1<<j) - 1 < n; i++) {
        if (a[t[i][j-1]] < a[t[i+(1<<(j-1))][j-1]]) {
          t[i][j] = t[i][j-1];
        } else {
          t[i][j] = t[i+(1<<(j-1))][j-1];
        }
      }
    }
  }

public:
  RMQ() {}
  RMQ(int num, T A[]) {
    n = num;
    a.assign(n, 0);
    t.assign(n, vector<int>());

    int lg2 = (32 - __builtin_clz(n));
    for (int i = 0; i < n; i++) {
      a[i] = A[i];
      t[i].assign(lg2, 0);
      t[i][0] = i;
    }
    
    build();
  }

  RMQ(int num, const vector<T>& A) {
    n = num;
    a.assign(n, 0);
    t.assign(n, vector<int>());

    int lg2 = (32 - __builtin_clz(n));
    for (int i = 0; i < n; i++) {
      a[i] = A[i];
      t[i].assign(lg2, 0);
      t[i][0] = i;
    }
    
    build();
  }

  int query(int i, int j) {
    int k = (int)floor(log((double)j-i+1) / log(2.0));
    if (a[t[i][k]] <= a[t[j-(1<<k)+1][k]]) {
      return t[i][k];
    } else {
      return t[j-(1<<k)+1][k];
    }
  }
};

int main() {
  int n = 7, A[] = {18, 17, 13, 19, 15, 11, 20};
  RMQ<int> rmq(n, A);
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      printf("RMQ(%d, %d) = %d\n", i, j, rmq.query(i, j));

  return 0;
}
