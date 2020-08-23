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

// Main
void mainCase() {
  string s; // <= 10^6
  cin >> s;

  // Make suffix array (by default cyclic)
  auto a = makeSA(s);
  // printSA(s, a);

  int a0 = a[0];
  string res = s.substr(a0) + s.substr(0, a0);
  cout << res << endl;
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
python misc/run.py cses/string_algorithms/task1110/main.cpp --check

%%%% begin
acab
%%%%
abac
%%%% end
*/
