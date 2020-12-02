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

// Suffix array in O(n log(n))
vector<int> makeSA(const string& s) {
  int n = s.size();

  vector<int> f(n);
  vector<array<int, 2>> f2(n);
  FOR(i, 0, n) { f2[i][0] = s[i]; }

  vector<int> sa(n), sa_next(n);
  iota(ALL(sa), 0);
  sort(ALL(sa), [&](auto i, auto j) { return f2[i] < f2[j]; });

  vector<int> cnts(n), cum_cnts(n + 1);

  for (int k = 1; k < n; k *= 2) {
    FOR(i, 1, n) {
      f[sa[i]] = f[sa[i - 1]] + (f2[sa[i]] != f2[sa[i - 1]]);
    }
    FOR(i, 0, n) {
      f2[sa[i]] = {f[sa[i]], f[(sa[i] + k) % n]};
    }
    // --- Counting sort (begin) ---
    // (Mostly equivalent to "sort(ALL(sa), [&](auto i, auto j) { return f[sa[i] - k] < f[sa[j] - k]; })")
    cum_cnts[0] = 0;
    FOR(i, 0, n) { cnts[f[i]]++; }
    FOR(i, 0, n) { cum_cnts[i + 1] = cum_cnts[i] + cnts[i]; cnts[i] = 0; }
    FOR(i, 0, n) {
      int j = (sa[i] - k + n) % n;
      sa_next[cum_cnts[f[j]]++] = j;
    }
    sa = sa_next;
    // --- Counting sort (end) ---
  }
  return sa;
}

// Main
void mainCase() {
  string s; // lowercase, length \in [1, 5 x 10^5]
  cin >> s;

  s += '$';
  auto sa = makeSA(s);
  dbg(sa);

  // Debug
  int n = sa.size();
  FOR(i, 0, n) { dbg(i, sa[i], s.substr(sa[i])); }

  FOR(i, 1, n) {
    cout << sa[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/suffixarray/main_v2.cpp

%%%% begin
abcbcba
%%%%
6 0 5 3 1 4 2
%%%% end

%%%% begin
mississippi
%%%%
10 7 4 1 0 9 8 6 3 5 2
%%%% end

%%%% begin
ababacaca
%%%%
8 0 2 6 4 1 3 7 5
%%%% end

%%%% begin
aaaaa
%%%%
4 3 2 1 0
%%%% end
*/
