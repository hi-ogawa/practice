// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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
  ll n, k; // [1, 2×10^5]
  cin >> n >> k;
  vector<ll> ps(n); // {1, ..., n}
  cin >> ps;

  // use {0, .., n-1} for simplicity
  for (auto& p: ps) {
    p--;
  }

  vector<ll> result(n, -1);
  map<ll, shared_ptr<vector<ll>>> stacks; // on-the-table stacks ordered by the top card

  for (ll i = 0; i < n; i++) {
    ll x = ps[i];
    auto it = stacks.lower_bound(x);
    if (it != stacks.end()) {
      auto [y, stack] = *it;
      stacks.erase(it);
      stack->push_back(x);
      if ((ll)stack->size() == k) {
        for (auto z: *stack) {
          result[z] = i + 1;
        }
        continue;
      }
      stacks[x] = stack;
    } else {
      if (k == 1) {
        result[x] = i + 1;
        continue;
      }
      stacks[x] = make_shared<vector<ll>>(vector{x});
    }
  }

  for (auto i: result) {
    cout << i << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc260/d/main.cpp

%%%% begin
5 2
3 5 2 1 4
%%%%
4
3
3
-1
4
%%%% end

%%%% begin
5 1
1 2 3 4 5
%%%%
1
2
3
4
5
%%%% end

%%%% begin
15 3
3 14 15 9 2 6 5 13 1 7 10 11 8 12 4
%%%%
9
9
9
15
15
6
-1
-1
6
-1
-1
-1
-1
6
15
%%%% end
*/
