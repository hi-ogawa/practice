// AFTER EDIORIAL, AC

//
// PROP. (invariance property)
//   There's a strategy to keep "at most one person is zero"
//

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
  ll n, a, b, c; // n <= 10^6
  cin >> n >> a >> b >> c;
  vector<string> ls(n);
  cin >> ls;

  int i = 0;
  vector<string> res(n);
  {
    bool ok = 1;
    FOR(_, 0, 1) {
      int cnt = (a > 0) + (b > 0) + (c > 0);
      if (cnt >= 2) { break; }
      if (cnt == 0) { ok = 0; break; }

      // [ cnt = 1 ]
      i++;
      if (ls[0] == "AB") {
        if (a == 0 && b == 0) { ok = 0; break; }
        if (a == 0) { a++; b--; res[0] = "A"; break; }
        if (b == 0) { a--; b++; res[0] = "B"; break; }
      }
      if (ls[0] == "BC") {
        if (b == 0 && c == 0) { ok = 0; break; }
        if (b == 0) { b++; c--; res[0] = "B"; break; }
        if (c == 0) { b--; c++; res[0] = "C"; break; }
      }
      if (ls[0] == "AC") {
        if (c == 0 && a == 0) { ok = 0; break; }
        if (c == 0) { c++; a--; res[0] = "C"; break; }
        if (a == 0) { c--; a++; res[0] = "A"; break; }
      }
    }

    if (!ok) {
      cout << "No" << endl;
      return;
    }
  }

  if (((a > 0) + (b > 0) + (c > 0)) == 1) {
    // Try single possible strategy
    bool ok = 1;
    while (i < n) {
      if (ls[i] == "AB") {
        if (a == 0 && b == 0) { ok = 0; break; }
        if (a == 0) { a++; b--; res[i++] = "A"; continue; }
        a--; b++; res[i++] = "B"; continue;
      }
      if (ls[i] == "BC") {
        if (b == 0 && c == 0) { ok = 0; break; }
        if (b == 0) { b++; c--; res[i++] = "B"; continue; }
        b--; c++; res[i++] = "C"; continue;
      }
      if (ls[i] == "AC") {
        if (c == 0 && a == 0) { ok = 0; break; }
        if (c == 0) { c++; a--; res[i++] = "C"; continue; }
        c--; a++; res[i++] = "A"; continue;
      }
    }
    if (!ok) {
      cout << "No" << endl;
      return;
    }

  } else {

    // We have "at most one person is zero" invariant strategy.
    // WLOG, {a, b, c} = {1, 1, 0}
    if (a == 0) { b = 1; c = 1; }
    if (b == 0) { c = 1; a = 1; }
    if (c == 0) { a = 1; b = 1; }
    if (a > 0 && b > 0 && c > 0) { a = 1; b = 1; c = 0; }

    while (i < n) {
      dbgv(i, a, b, c);
      assert(((a > 0) + (b > 0) + (c > 0)) >= 2);

      // last step if any
      if (i == n - 1) {
        if (ls[i] == "AB") { res[i] = a == 0 ? "A" : "B"; break; }
        if (ls[i] == "BC") { res[i] = b == 0 ? "B" : "C"; break; }
        if (ls[i] == "AC") { res[i] = c == 0 ? "C" : "A"; break; }
      }

      // not last step
      if (ls[i] == "AB") {
        if (a == 0) { a++; b--; res[i++] = "A"; continue; } // (1, 0, 1)
        if (b == 0) { a--; b++; res[i++] = "B"; continue; } // (0, 1, 1)

        // [ (a, b, c) = (1, 1, 0) ]
        if (ls[i + 1] == "AB") { // (1, 1, 0)
          res[i++] = "A"; res[i++] = "B"; continue; // whichever since no-op
        }
        if (ls[i + 1] == "BC") { // (0, 1, 1)
          a--; c++;
          res[i++] = "B"; res[i++] = "C"; continue;
        }
        if (ls[i + 1] == "AC") { // (1, 0, 1)
          b--; c++;
          res[i++] = "A"; res[i++] = "C"; continue;
        }
      }

      // (the rest follows by symmetry)
      if (ls[i] == "BC") {
        if (b == 0) { b++; c--; res[i++] = "B"; continue; }
        if (c == 0) { b--; c++; res[i++] = "C"; continue; }

        if (ls[i + 1] == "BC") {
          res[i++] = "B"; res[i++] = "C"; continue;
        }
        if (ls[i + 1] == "AC") {
          b--; a++;
          res[i++] = "C"; res[i++] = "A"; continue;
        }
        if (ls[i + 1] == "AB") {
          c--; a++;
          res[i++] = "B"; res[i++] = "A"; continue;
        }
      }

      if (ls[i] == "AC") {
        if (c == 0) { c++; a--; res[i++] = "C"; continue; }
        if (a == 0) { c--; a++; res[i++] = "A"; continue; }

        if (ls[i + 1] == "AC") {
          res[i++] = "C"; res[i++] = "A"; continue;
        }
        if (ls[i + 1] == "AB") {
          c--; b++;
          res[i++] = "A"; res[i++] = "B"; continue;
        }
        if (ls[i + 1] == "BC") {
          a--; b++;
          res[i++] = "C"; res[i++] = "B"; continue;
        }
      }
    }
  }
  dbg(res);

  cout << "Yes" << endl;
  for (auto x : res) {
    cout << x << endl;
  }
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
python misc/run.py atcoder/abc166/f/main.cpp --check

%%%% begin
2 1 3 0
AB
AC
%%%%
%%%% end

%%%% begin
8 6 9 1
AC
BC
AB
BC
AC
BC
AB
AB
%%%%
%%%% end
*/
