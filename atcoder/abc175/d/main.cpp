// AFTER CONTEST, WA

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, k; // n <= 10^4, k <= 10^9
  cin >> n >> k;
  vector<int> ls(n, 0); // permutation
  cin >> ls;
  vector<ll> ps(n, 0); // |x| <= 10^9
  cin >> ps;
  for (auto& x : ls) { x--; }

  // Connected component by DFS
  vector<vector<int>> compos;
  {
    vector<bool> done(n, 0);
    function<void(int, vector<int>&)> dfs = [&](int v, vector<int>& co) {
      if (done[v]) { return; }
      done[v] = 1;
      co.push_back(v);
      dfs(ls[v], co);
    };
    FOR(v, 0, n) {
      if (!done[v]) {
        dfs(v, compos.emplace_back());
      }
    }
  }
  // DD(compos);

  // Max sum segement of bounded length (not used)
  auto boundedMaxSegment = [&](int w0, int w1, vector<int>& co) -> ll {
    int m = co.size();
    vector<ll> cumsum(m + 1, 0);
    FOR(i, 0, m) { cumsum[i + 1] = cumsum[i] + ps[co[i]]; }
    ll res = 0;
    set<ll> tmp; // active cumsum within window
    // DD(tie(w0, w1, co, cumsum));

    // Initial window
    FOR(i, w0, w1 + 1) { tmp.insert(cumsum[i]); }
    res = *tmp.rbegin();

    // Sliding window
    FOR(i, 1, m - w0 + 1) {
      tmp.erase(tmp.find(cumsum[i + w0 - 1]));
      if (i + w1 <= m) { tmp.insert(cumsum[i + w1]); }
      res = max(res, *tmp.rbegin() - cumsum[i]);
    }

    // DD(res);
    return res;
  };

  // Cyclic version is what we need
  auto boundedMaxSegmentCyclic = [&](int w0, int w1, vector<int>& co) -> ll {
    int m = co.size();
    vector<ll> cumsum(m + w1 + 1, 0);
    FOR(i, 0, m + w1) { cumsum[i + 1] = cumsum[i] + ps[co[i % m]]; }
    ll res = 0;
    set<ll> tmp; // active cumsum within window
    // DD(tie(w0, w1, co, cumsum));

    // Initial window
    FOR(i, w0, w1 + 1) { tmp.insert(cumsum[i]); }
    res = *tmp.rbegin();

    // Sliding window
    FOR(i, 1, m) {
      tmp.erase(tmp.find(cumsum[i + w0 - 1]));
      if (i + w1 <= m + w1) { tmp.insert(cumsum[i + w1]); }
      res = max(res, *tmp.rbegin() - cumsum[i]);
    }

    // DD(res);
    return res;
  };

  // Score for each component
  int l = compos.size();
  vector<ll> scores(l, 0);
  FOR(j, 0, l) {
    auto& co = compos[j];
    int m = co.size();
    ll co_sum = 0;
    for (auto x : co) { co_sum += ps[x]; }
    // DD(tie(m, co));

    // [ k <= m ]
    if (k <= m) {
      // (1, k)-bounded max segment
      scores[j] = boundedMaxSegmentCyclic(1, k, co);
    }

    // [ k > m ]
    if (k > m) {
      if (co_sum < 0) {
        // (1, m)-bounded max segment
        scores[j] = boundedMaxSegmentCyclic(1, m, co);
      }

      if (co_sum >= 0) {
        // (0, r)-bounded max segment
        int q = k / m, r = k % m;
        // DD(tie(co_sum, q));
        scores[j] = boundedMaxSegmentCyclic(0, r, co) + co_sum * q;
      }
    }
  }
  // DD(scores);

  ll res = *max_element(ALL(scores));
  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc175/d/main.cpp --check

%%%% begin
3 6
2 3 1
1 2 3
%%%%
%%%% end

%%%% begin
10 58
9 1 6 7 8 4 3 2 10 5
695279662 988782657 -119067776 382975538 -151885171 -177220596 -169777795 37619092 389386780 980092719
%%%%
29507023469
%%%% end

%%%% begin
5 2
2 4 5 1 3
3 4 -10 -8 8
%%%%
8
%%%% end
*/
