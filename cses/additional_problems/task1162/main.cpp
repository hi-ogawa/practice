// AC

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

// Order statistics tree (cf. https://codeforces.com/blog/entry/11080 by adamant)
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Compare = less<Key>>
using ordered_set = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, Compare,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, n]
  cin >> ls;

  // For convenience
  for (auto& x : ls) { x--; } // [0, n)

  auto solve1 = [&](auto ls) -> ll {
    // Count inversions
    ll res = 0;
    ordered_set<int> st;
    FOR(i, 0, n) {
      int x = ls[i];
      st.insert(x);
      res += i - st.order_of_key(x);
    }
    return res;
  };

  auto solve2 = [&](auto ls) -> ll {
    // Simulate directly (fixing from smalls)
    vector<int> ls_inv(n);
    FOR(i, 0, n) { ls_inv[ls[i]] = i; }

    ll res = 0;
    FOR(i, 0, n) {
      if (ls_inv[i] == i) { continue; }
      int j = ls_inv[i];
      assert(ls[j] == i && ls[i] > i);
      swap(ls[i], ls[j]);
      ls_inv[ls[i]] = i;
      ls_inv[ls[j]] = j;
      res++;
    }
    return res;
  };

  auto solve3 = [&](auto ls) -> ll {
    // Find LIS
    vector<int> dp;
    FOR(i, 0, n) {
      int x = ls[i];
      auto it = upper_bound(ALL(dp), x);
      if (it == dp.end()) {
        dp.push_back(x);
      } else {
        *it = x;
      }
    }
    ll res = n - (int)dp.size();
    return res;
  };

  auto solve4 = [&](auto ls) -> ll {
    // Find longest subseq {k, k+1, .., n-1}
    vector<int> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
      int x = ls[i];
      dp[x] = dp[x + 1];
    }
    ll res = 0;
    FOR(i, 0, n + 1) {
      if (dp[i]) {
        res = i;
        break;
      }
    }
    return res;
  };

  array<ll, 4> res = {solve1(ls), solve2(ls), solve3(ls), solve4(ls)};
  FOR(i, 0, 4) {
    cout << res[i] << " \n"[i == 3];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1162/main.cpp

%%%% begin
8
7 8 2 6 5 1 3 4
%%%%
20 6 5 6
%%%% end
*/
