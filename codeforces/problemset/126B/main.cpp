// TLE

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Suffix array (cf. cses/string_algorithms/task1732/main.cpp)
void printSA(const string& s, const vector<int>& a) {
  for (auto i : a) cout << s.substr(i) << endl;
}

vector<int> makeSA(const string& s) {
  int n = s.size();
  vector<int> a(n, 0); // suffix array
  vector<int> b(n, 0); // prefix class

  // Initialize [0, 1)-prefix
  iota(ALL(a), 0);
  sort(ALL(a), [&](auto x, auto y) { return s[x] < s[y]; });
  FOR(i, 0, n - 1) { b[a[i + 1]] = b[a[i]] + (s[a[i + 1]] != s[a[i]]); }

  // Update [0, m)-prefix to [0, 2m)-prefix
  auto a_tmp = a;
  auto b_tmp = b;
  vector<int> c(n, 0); // for counting sort
  for (int m = 1; m < n - 1; m <<= 1) {
    // Done if totally ordered
    if (b[a[n - 1]] == n - 1) { break; }

    // Counting sort [0, 2m)-prefix
    fill(ALL(c), 0);
    FOR(i, 0, n) { c[b[i]]++; } // count [0, m)-prefix class
    FOR(i, 1, n) { c[i] += c[i - 1]; } // cumsum
    for (int i = n - 1; i >= 0; i--) { // For stable sort with "--c[b[p]]" below
      int p = (a[i] - m + n) % n;
      a_tmp[--c[b[p]]] = p;
    }
    swap(a, a_tmp);

    // Update class
    b_tmp[a[0]] = 0;
    FOR(i, 0, n - 1) {
      int p1 = a[i], q1 = (a[i] + m) % n;
      int p2 = a[i + 1], q2 = (a[i + 1] + m) % n;
      b_tmp[p2] = b_tmp[p1] + !(b[p1] == b[p2] && b[q1] == b[q2]);
    }
    swap(b, b_tmp);
  }
  return a;
}

vector<int> makeLCP(const string& s, const vector<int>& a) {
  int n = s.size();
  vector<int> lcp(n - 1, 0);

  vector<int> a_inv(n, 0);
  FOR(i, 0, n) { a_inv[a[i]] = i; }

  int k = 0;
  for (int ai = 0; ai < n - 1; ai++) {
    int i = a_inv[ai];
    int kk = k; // Already known common length for s[a[i]:] and s[a[i-1]:]
    while (s[ai + kk] == s[a[i - 1] + kk]) { kk++; }
    lcp[i - 1] = kk;
    k = max(0, kk - 1);
  }
  return lcp;
}

// Main
void mainCase() {
  string s;
  cin >> s;

  s += '$';
  int n = s.size();

  auto sa = makeSA(s);
  auto lcp = makeLCP(s, sa);
  if (DEBUG) { printSA(s, sa); }

  vector<int> sa_inv(n);
  FOR(i, 0, n) { sa_inv[sa[i]] = i; }

  int i0 = sa_inv[0];
  dbg(i0);

  vector<int> lcp0(n, -1);
  if (i0 != n - 1) {
    lcp0[i0 + 1] = lcp[i0];
    for (int i = i0 + 2; i < n; i++) {
      lcp0[i] = min(lcp0[i - 1], lcp[i - 1]);
    }
  }
  lcp0[i0 - 1] = lcp[i0 - 1];
  for (int i = i0 - 2; i >= 0; i--) {
    lcp0[i] = min(lcp0[i + 1], lcp[i]);
  }
  dbg(lcp0);

  set<int> suffixes;
  set<int> infixes;
  FOR(i, 0, n) {
    if (i == i0) { continue; }
    if (lcp0[i] == 0) { continue; }
    int l = n - sa[i] - 1;
    if (l == lcp0[i]) {
      suffixes.insert(lcp0[i]);
      infixes.insert(lcp0[i] - 1);
    }
    if (l > lcp0[i]) {
      infixes.insert(lcp0[i]);
    }
  }
  dbg(suffixes);
  dbg(infixes);

  int res = -1;
  for (auto l : suffixes) {
    auto it = infixes.lower_bound(l); // l <= *it
    if (it != infixes.end()) {
      res = max(res, l);
    }
  }

  if (res == -1) { cout << "Just a legend" << endl; return; }
  cout << s.substr(n - res - 1, res) << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/problemset/126B/main.cpp --check

%%%% begin
aaabaabaaaaab
%%%%
aaab
%%%% end

%%%% begin
aaa
%%%%
a
%%%% end

%%%% begin
fixprefixsuffix
%%%%
fix
%%%% end

%%%% begin
abcdabc
%%%%
Just a legend
%%%% end
*/
