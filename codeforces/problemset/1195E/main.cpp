// TLE

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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, m, a, b; // [1, 3000]
  cin >> n >> m >> a >> b;
  ll g, x, y, z; // [0, 10^9]
  cin >> g >> x >> y >> z;

  vector<vector<ll>> ls(n, vector<ll>(m));
  ll acc = g;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      ls[i][j] = acc;
      acc = (acc * x + y) % z;
    }
  }
  dbg2(ls);

  int nn = n - a + 1;
  int mm = m - b + 1;

  // Compress horizontally
  vector<vector<ll>> ls1(n, vector<ll>(mm));
  FOR(i, 0, n) {
    multiset<ll> st;
    FOR(j, 0, m) {
      st.insert(ls[i][j]);
      if (j >= b) {
        st.erase(st.find(ls[i][j - b]));
      }
      if (j >= b - 1) {
        ls1[i][j - (b - 1)] = *st.begin();
      }
    }
  }

  // Compress vertically
  vector<vector<ll>> ls2(nn, vector<ll>(mm));
  FOR(j, 0, mm) {
    multiset<ll> st;
    FOR(i, 0, n) {
      st.insert(ls1[i][j]);
      if (i >= a) {
        st.erase(st.find(ls1[i - a][j]));
      }
      if (i >= a - 1) {
        ls2[i - (a - 1)][j] = *st.begin();
      }
    }
  }
  dbg2(ls2);

  // Take sum
  ll res = 0;
  FOR(i, 0, nn) {
    FOR(j, 0, mm) {
      res += ls2[i][j];
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1195E/main.cpp

%%%% begin
3 4 2 1
1 2 3 59
%%%%
111
%%%% end
*/
