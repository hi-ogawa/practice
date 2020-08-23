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

// Main
void mainCase() {
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n, 0); // <= 10^9
  cin >> ls;

  // Find maximul width from each index (right-end and left-end)
  vector<int> rights(n, 0);
  {
    vector<int> st;
    FOR(i, 0, n) {
      while (!st.empty() && ls[st.back()] > ls[i]) {
        int j = st.back(); st.pop_back();
        rights[j] = i - j;
      }
      st.push_back(i);
    }
    while (!st.empty()) {
      int j = st.back(); st.pop_back();
      rights[j] = n - j;
    }
  }
  // DD(rights);

  vector<int> lefts(n, 0);
  {
    vector<int> st;
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && ls[st.back()] > ls[i]) {
        int j = st.back(); st.pop_back();
        lefts[j] = j - i;
      }
      st.push_back(i);
    }
    while (!st.empty()) {
      int j = st.back(); st.pop_back();
      lefts[j] = j + 1;
    }
  }
  // DD(lefts);

  ll res = 0;
  FOR(i, 0, n) {
    ll w = rights[i] + lefts[i] - 1;
    ll h = ls[i];
    res = max(res, w * h);
  }
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
python misc/run.py cses/additional_problems/task1142/main.cpp --check

%%%% begin
8
4 1 5 3 3 2 4 1
%%%%
10
%%%% end
*/
