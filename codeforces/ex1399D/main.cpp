// AFTER CONTEST, AC

//
// Claim.
//   Appending to the most recent subsequence doesn't decrease score.
//   Thus, such strategy gives one of optimal solutions.
//

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<class T> T pop(std::vector<T>& xs) { auto x = xs.back(); xs.pop_back(); return x; }

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts> ostream&        operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T> ostream&            operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
tuple<int, vector<int>> solve(const string& ls) {
  int n = ls.size();
  array<vector<int>, 2> queues({vector<int>(0, 0), vector<int>(0, 0)});
  vector<int> result(n, 0);
  int count = 0;
  RANGE(i, 0, n) {
    auto& p = queues[ls[i] == '1'];
    auto& q = queues[!(ls[i] == '1')];
    if (p.empty()) {
      p.push_back(++count);
    }
    int k = pop(p);
    result[i] = k;
    q.push_back(k);
  }
  return {count, result};
}

void main_case() {
  int n;
  cin >> n;
  string ls;
  cin >> ls;
  auto [count, result] = solve(ls);
  cout << count << endl;
  RANGE(i, 0, n) {
    if (i) { cout << " "; }
    cout << result[i];
  }
  cout << endl;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    main_case();
  }
  return 0;
}

/*
python misc/run.py codeforces/ex1399D/main.cpp --check

%%%% begin
1
8
01010000
%%%%
4
1 1 1 1 1 2 3 4
%%%% end

%%%% begin
4
4
0011
6
111111
5
10101
8
01010000
%%%%
2
1 2 2 1
6
1 2 3 4 5 6
1
1 1 1 1 1
4
1 1 1 1 1 2 3 4
%%%% end
*/
