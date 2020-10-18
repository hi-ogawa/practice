// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, n]
  cin >> ls;

  int k = n + 2;
  vector<int> cnts(k);
  for (auto x : ls) { cnts[x]++; }
  dbg(cnts);

  auto solveMin = [&]() -> int {
    int res = 0;
    int i = 0;
    while (true) {
      while (i < k && cnts[i] == 0) { i++; }
      if (i >= k) { break; }
      res++;
      i += 3;
    }
    return res;
  };

  auto solveMax = [&]() -> int {
    vector<array<int, 2>> cnts2(k); // (stayed at "i", moved to "i")
    FOR(i, 0, k) {
      cnts2[i][0] = cnts[i];
    }
    int i = 0;
    while (true) {
      while (i < k && cnts[i] == 0) { i++; }
      if (i >= k) { break; }

      if (i > 0 && cnts2[i - 1][0] == 0 && cnts2[i - 1][1] == 0) {
        cnts2[i][0]--;
        cnts2[i - 1][1]++;
      }
      if (i + 1 < k && (cnts2[i][0] >= 2 || cnts2[i][1] >= 1)) {
        cnts2[i][0]--;
        cnts2[i + 1][1]++;
      }
      i++;
    }

    int res = 0;
    for (auto [x, y] : cnts2) {
      res += (x + y > 0);
    }
    return res;
  };

  cout << solveMin() << " " << solveMax() << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1283E/main.cpp

%%%% begin
4
1 2 4 4
%%%%
2 4
%%%% end

%%%% begin
9
1 1 8 8 8 4 4 4 4
%%%%
3 8
%%%% end

%%%% begin
7
4 3 7 1 4 3 3
%%%%
3 6
%%%% end
*/
