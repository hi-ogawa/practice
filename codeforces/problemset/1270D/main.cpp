// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  int n, k; // 1 <= k < n <= 500
  cin >> n >> k;

  auto ask = [](auto& query) -> array<int, 2> {
    cout << "?";
    for (auto i : query) {
      cout << " " << (i + 1);
    }
    cout << endl;
    int x, y;
    cin >> x >> y;
    return {(x - 1), y};
  };

  set<int> query;
  FOR(i, 0, k) { query.insert(i); }

  // {0, 1, .., k-1}
  auto [i0, x0] = ask(query);

  // {0, 1, .. del(i0), .., k-1, k}
  query.erase(i0);
  query.insert(k);
  auto [i1, x1] = ask(query);

  assert(x0 != x1);

  int res = -1;

  // {0, 1, ..., k-1, k}
  query.insert(i0);

  if (x1 < x0) {
    // count smaller than x0 from index {0, 1, ..., k-1}
    int cnt = 0;
    FOR(i, 0, k) {
      if (i == i0) { continue; }
      // {0, 1, ..., del(i), ..., k-1, k}
      query.erase(i);
      auto [j, x] = ask(query);
      query.insert(i);
      cnt += (x == x0); // result doesn't change  \iff  ls[i] is on the same side as ls[k] (i.e. ls[i], x1 < x0)
    }
    res = cnt + 1;
  }

  if (x1 > x0) {
    // count larger than x0 from index {0, 1, ..., k-1}
    int cnt = 0;
    FOR(i, 0, k) {
      if (i == i0) { continue; }
      // {0, 1, ..., del(i), ..., k-1, k}
      query.erase(i);
      auto [j, x] = ask(query);
      query.insert(i);
      cnt += (x == x0);
    }
    res = k - cnt;
  }

  cout << "! " << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1270D/main.cpp

%%%% begin
4 3
4 9
4 9
4 9
1 2
%%%%
? 2 3 4
? 1 3 4
? 1 2 4
? 1 2 3
! 3
%%%% end
*/
