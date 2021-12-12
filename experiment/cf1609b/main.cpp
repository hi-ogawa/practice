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

const string kPattern = "abc";

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  string s;
  cin >> s;
  vector<tuple<int, char>> qs(nq);
  cin >> qs;

  // Count matching segment
  int count = 0;

  // Initial state
  for (int i = 0; i < n; i++) {
    if (s.substr(i, 3) == kPattern) {
      count++;
    }
  }

  // Incrementally update
  for (auto [i, c] : qs) {
    i--;

    // Check only three segments where possibly "abc" appeared or disappeared
    for (int j = max(i - 2, 0); j <= i; j++) {
      count -= (s.substr(j, 3) == kPattern);
    }

    s[i] = c;

    for (int j = max(i - 2, 0); j <= i; j++) {
      count += (s.substr(j, 3) == kPattern);
    }

    cout << count << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py experiment/cf1609b/main.cpp

%%%% begin
9 10
abcabcabc
1 a
1 b
2 c
3 a
4 b
5 c
8 a
9 b
1 c
4 a
%%%%
3
2
2
2
1
2
1
1
1
0
%%%% end
*/
