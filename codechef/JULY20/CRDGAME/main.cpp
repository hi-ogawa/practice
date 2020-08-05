#include <bits/stdc++.h>

#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
#define PP(X) std::cout << #X ": " << (X) << std::endl
#define PPP(X) std::cout << #X ": {"; for (auto x : X) { std::cout << x << ", "; } std::cout << "}" << std::endl;

using namespace std;
using ll = int64_t;

int sumDigits(int x) {
  string s = to_string(x);
  transform(ALL(s), s.begin(), [](auto c){ return c - '0'; });
  return accumulate(ALL(s), (int)0);
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n;
    cin >> n;
    int a, b;
    int aa = 0;
    int bb = 0;
    RANGE(j, 0, n) {
      cin >> a >> b;
      int da = sumDigits(a);
      int db = sumDigits(b);
      if (da > db) {
        aa++;
      }
      if (da < db) {
        bb++;
      }
      if (da == db) {
        aa++;
        bb++;
      }
    }
    int x = aa > bb ? 0 : aa < bb ? 1 : 2;
    int y = max(aa, bb);
    cout << x << " " << y << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/JULY20/CRDGAME/main.cpp --check

%%%% begin
2
3
10 4
8 12
7 6
2
5 10
3 4
%%%%
0 2
2 1
%%%% end
*/
