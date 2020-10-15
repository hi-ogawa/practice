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
  int n; // [1, 3 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;

  // For each index "i", find first left/right non divisible index "j"
  vector<int> rights(n, n);
  vector<array<int, 2>> st;
  FOR(i, 0, n) {
    while (!st.empty() && (ls[i] % st.back()[1] != 0)) {
      auto [j, _x] = st.back(); st.pop_back();
      rights[j] = i;
    }
    st.push_back({i, ls[i]});
  }

  vector<int> lefts(n, -1);
  st.clear();
  for (int i = n - 1; i >= 0; i--) {
    while (!st.empty() && (ls[i] % st.back()[1] != 0)) {
      auto [j, _x] = st.back(); st.pop_back();
      lefts[j] = i;
    }
    st.push_back({i, ls[i]});
  }

  map<int, set<array<int, 2>>> res;
  FOR(i, 0, n) {
    int l = lefts[i], r = rights[i];
    res[r - l].insert({l, r});
  }

  auto [res1, res2] = *res.rbegin();
  int k = res2.size();
  vector<array<int, 2>> res3(ALL(res2));
  cout << k << " " << (res1 - 2) << "\n";
  FOR(i, 0, k) {
    cout << (res3[i][0] + 2) << " \n"[i == k - 1];
  }
}


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/359D/main_v2.cpp

%%%% begin
5
4 6 9 3 6
%%%%
1 3
2
%%%% end

%%%% begin
5
1 3 5 7 9
%%%%
1 4
1
%%%% end

%%%% begin
5
2 3 5 7 11
%%%%
5 0
1 2 3 4 5
%%%% end
*/
