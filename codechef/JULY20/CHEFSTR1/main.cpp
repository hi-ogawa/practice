// VC, AC

#include <bits/stdc++.h>

// Macros
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
#define PP(X) std::cout << #X ": " << (X) << std::endl
#define PPP(X) std::cout << #X ": {"; for (auto it = std::begin(X); it != std::end(X); it++) { if (it != std::begin(X)) {std::cout << ", ";} std::cout << *it; } std::cout << "}" << std::endl;

using namespace std;
using ll = int64_t;

int main() {
  int t, n;
  cin >> t;
  RANGE(i, 0, t) {
    cin >> n;
    vector<int> ls(n, 0);
    RANGE(j, 0, n) {
      cin >> ls[j];
    }
    ll result = 0;
    RANGE(j, 0, n - 1) {
      result += abs(ls[j + 1] - ls[j]) - 1;
    }
    cout << result << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/JULY20/CHEFSTR1/main.cpp --check

%%%% begin
2
6
1 6 11 6 10 11
4
1 3 5 7
%%%%
15
3
%%%% end
*/
