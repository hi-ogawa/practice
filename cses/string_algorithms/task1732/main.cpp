// AC

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

void printSA(const string& s, const vector<int>& a) {
  for (auto i : a) cout << s.substr(i) << endl;
}

// cf. task1753
vector<int> makeSA(const string& s) {
  assert(++min_element(ALL(s)) == s.end()); // smallest at the end

  int n = s.size();
  vector<int> a(n, 0); // suffix array
  vector<int> b(n, 0); // prefix class

  // Initialize [0, 1)-prefix
  iota(ALL(a), 0);
  sort(ALL(a), [&](auto x, auto y) { return s[x] < s[y]; });
  FOR(i, 0, n - 1) { b[a[i + 1]] = b[a[i]] + (s[a[i + 1]] != s[a[i]]); }
  // printSA(s, a);

  // Update [0, m)-prefix to [0, 2m)-prefix
  auto a_tmp = a;
  auto b_tmp = b;
  vector<int> c(n, 0); // for counting sort
  for (int m = 1; m < n - 1; m <<= 1) {
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

    // DD(m); DD(b); printSA(s, a);

    // Done if totally ordered
    if (b[a[n - 1]] == n - 1) { break; }
  }
  return a;
}

// cf. codeforces/edu/ex269119A/main.js
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
  string s; // <= 10^6
  cin >> s;

  // Make suffix array
  s += "$";
  auto a = makeSA(s);
  // printSA(s, a);

  // Make longest common prefix
  auto lcp = makeLCP(s, a);
  // DD(lcp);

  // Find common prefix with s
  vector<int> res;
  int i0 = distance(a.begin(), find(ALL(a), 0));
  int n = s.size();

  // Cumulative minimum
  int cm = n;
  for (int i = i0 - 1; i >= 0; i--) {
    if (lcp[i] == 0) { break; }
    if (lcp[i] < cm) { cm = min(cm, lcp[i]); }
    // suffix-length = common-length
    if (n - 1 - a[i] == cm) { res.push_back(cm); }
  }
  reverse(ALL(res));
  res.erase(unique(ALL(res)), res.end());
  // DD(res);

  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << res[i];
  }
  cout << endl;
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
python misc/run.py cses/string_algorithms/task1732/main.cpp --check

%%%% begin
abababaa
%%%%
1
%%%% end

%%%% begin
abcababcab
%%%%
2 5
%%%% end
*/
