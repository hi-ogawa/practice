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

// Main
void mainCase() {
  string s;
  cin >> s;
  int n = s.size(); // <= 10^6

  const int k = 26; // A..Z
  vector<int> cnts(k);
  for (auto t : s) { cnts[t - 'A']++; }
  dbg(cnts);

  if (*max_element(ALL(cnts)) > (n + 1) / 2) {
    cout << -1 << endl;
    return;
  }

  //
  // PROP. by construction, this achieves minimum.
  //

  auto take = [&](int len, int t_prev) -> int {
    auto it = max_element(ALL(cnts));
    assert(*it <= (len + 1) / 2); // PROP: this invariance holds true
    int t_res = -1;
    if (2 * (*it) == len + 1) {
      t_res = distance(cnts.begin(), it);
      assert(t_res != t_prev);
    } else {
      FOR(t, 0, k) {
        if (t == t_prev) { continue; }
        if (cnts[t] > 0) {
          t_res = t;
          break;
        }
      }
    }
    dbgv(len, t_prev, t_res, cnts);
    assert(t_res != -1);
    assert(cnts[t_res] > 0);
    cnts[t_res]--;
    return t_res;
  };

  vector<int> res(n);
  res[0] = take(n, -1);
  FOR(i, 1, n) {
    res[i] = take(n - i, res[i - 1]);
  }

  string res2;
  for (auto t : res) { res2 += (t + 'A'); }

  cout << res2 << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1743/main.cpp --check

%%%% begin
HATTIVATTI
%%%%
AHATITITVT
%%%% end
*/
