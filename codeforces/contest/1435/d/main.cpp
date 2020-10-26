// CONTEST, AC

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
  int n; // [1, 10^5]
  cin >> n;
  int nq = 2 * n;
  vector<pair<char, int>> qs(nq);
  FOR(i, 0, nq) {
    auto& [t, x] = qs[i];
    cin >> t;
    if (t == '-') {  cin >> x; }
  }

  // Stock >= 0
  bool ok_stock = 1;
  vector<int> cs(nq + 1);
  FOR(i, 0, nq) {
    cs[i + 1] = cs[i] + (qs[i].first == '+' ? 1 : -1);
    if (cs[i + 1] < 0) {
      ok_stock = 0;
    }
  }
  if (!ok_stock) { cout << "NO" << "\n"; return; }

  // Segments of '+...+' and '-...-'
  vector<array<int, 2>> segs;
  FOR(i, 0, nq) {
    if (i == 0 || qs[i].first != qs[i - 1].first) { segs.push_back({i, -1}); }
    segs.back()[1] = i + 1;
  }

  // Each '-...-' is increasing
  bool ok_incr = 1;
  for (auto [l, r] : segs) {
    if (qs[l].first == '+') { continue; }
    FOR(i, l, r - 1) {
      if (qs[i].second > qs[i + 1].second) {
        ok_incr = 0;
        break;
      }
    }
  }
  if (!ok_incr) { cout << "NO" << "\n"; return; }

  // Solve from tail
  int k = segs.size();
  vector<int> res;
  bool ok_rem = 1;
  set<int> rem; // remaining
  for (int j = k - 1; j >= 0; j--) {
    auto [l, r] = segs[j];
    if (qs[l].first == '+') {
      // Pick smaller ones
      int s = r - l;
      assert((int)rem.size() >= s);
      FOR(i, 0, s) {
        int x = *rem.begin(); rem.erase(rem.begin());
        res.push_back(x);
      }
    }
    if (qs[l].first == '-') {
      // Remaining ones has to be larger
      if (!rem.empty()) {
        int x1 = *rem.begin();
        int x0 = 0;
        FOR(i, l, r) {
          x0 = max(x0, qs[i].second);
        }
        if (x0 > x1) {
          ok_rem = 0;
          break;
        }
      }
      // Update remainings
      FOR(i, l, r) {
        rem.insert(qs[i].second);
      }
    }
  }
  dbg(res);
  if (!ok_rem) { cout << "NO" << "\n"; return; }

  reverse(ALL(res));

  cout << "YES" << "\n";
  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1435/d/main.cpp

%%%% begin
4
+
+
- 2
+
- 3
+
- 1
- 4
%%%%
YES
4 2 3 1
%%%% end

%%%% begin
1
- 1
+
%%%%
NO
%%%% end

%%%% begin
3
+
+
+
- 2
- 1
- 3
%%%%
NO
%%%% end
*/
