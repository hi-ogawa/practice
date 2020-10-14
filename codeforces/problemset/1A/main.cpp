#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
int main() {
  ll n, m, a;
  cin >> n >> m >> a;
  ll res = ((n + a - 1) / a) * ((m + a - 1) / a);
  cout << res << "\n";
  return 0;
}
