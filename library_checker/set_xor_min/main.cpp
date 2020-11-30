// AC

// NOTE: Directly search through std::set (cf. codeforces/problemset/706D/main_v2.cpp)

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int nq; // [1, 5 x 10^5]
  cin >> nq;
  vector<array<int, 2>> qs(nq); // x \in [0, 2^30)
  cin >> qs;

  set<int> ls;

  const int b_lim = 30;

  // min { y ^ x | y \in ls }
  auto solve = [&](int x) -> int {
    int res = 0;
    int query = 0;
    auto itl = ls.begin(), itr = ls.end(); // [l, r)
    for (int b = b_lim - 1; b >= 0; b--) {
      int query_sep = query | (1 << b);
      auto it = ls.lower_bound(query_sep);
      if ((x >> b) & 1) {
        if (it == itr) { // [q, r) is empty
          res |= (1 << b);
        } else {
          itl = it;
          query = query_sep;
        }
      } else {
        if (it == itl) { // [l, q) is empty
          res |= (1 << b);
          query = query_sep;
        } else {
          itr = it;
        }
      }
    }
    return res;
  };

  for (auto [t, x] : qs) {
    if (t == 0) {
      ls.insert(x);
    }
    if (t == 1) {
      ls.erase(x);
    }
    if (t == 2) {
      auto res = solve(x);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/set_xor_min/main.cpp

%%%% begin
2
0 6
2 7
%%%%
1
%%%% end

%%%% begin
6
0 6
0 7
2 5
1 7
1 10
2 7
%%%%
2
1
%%%% end
*/
