// AFTER EDITORIAL, AC

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
  int n; // 2^k in [4, 2^16]
  cin >> n;

  auto ask = [&](string t, int i, int j) -> int {
    i++; j++;
    cout << t << " " << i << " " << j << endl;
    int resp;
    cin >> resp;
    assert(resp != -1);
    return resp;
  };

  // n - 1 queries for x ^ y
  vector<int> xors(n);
  FOR(i, 1, n) {
    xors[i] = ask("XOR", 0, i);
  }

  // Look for duplicate
  bool ok_dup = 0;
  int i_dup, j_dup;
  map<int, vector<int>> inv_xors;
  FOR(i, 0, n) {
    inv_xors[xors[i]].push_back(i);
  }
  for (auto& [k, v] : inv_xors) {
    if ((int)v.size() >= 2) {
      ok_dup = 1;
      i_dup = v[0];
      j_dup = v[1];
      break;
    }
  }

  int i_found = -1;
  int x_found;

  if (ok_dup) {
    // If duplicate is found, then "AND" gives its value
    x_found = ask("AND", i_dup, j_dup);
    i_found = i_dup;

  } else {
    // Otherwise (i.e. all distinct), we have disjoint pair.
    int i0 = 0;
    int i1 = -1;
    FOR(i, 1, n) {
      // Disjoint  \iff  all bits "1"
      if (xors[i] == n - 1) {
        i1 = i;
        break;
      }
    }
    assert(i1 != -1);
    int i2 = (i1 == 1) ? 2 : 1;

    // Same trick as e1/main.cpp
    int xy_and = 0; // but here "AND" for free since disjoint!!
    int yz_and = ask("AND", i1, i2);
    int zx_and = ask("AND", i2, i0);
    int xy_xor = xors[i0] ^ xors[i1];
    int yz_xor = xors[i1] ^ xors[i2];
    int zx_xor = xors[i2] ^ xors[i0];
    int xy = 2 * xy_and + xy_xor;
    int yz = 2 * yz_and + yz_xor;
    int zx = 2 * zx_and + zx_xor;
    int x2 = xy + zx - yz;
    assert(x2 % 2 == 0);

    x_found = x2 / 2;
    i_found = i0;
  }

  // Reconstruct
  vector<int> res(n);
  assert(i_found != -1);
  FOR(i, 0, n) {
    res[i] = x_found ^ xors[i_found] ^ xors[i];
  }

  cout << "!";
  for (auto r : res) {
    cout << " " << r;
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1451/e2/main.cpp

%%%% begin
4

0

2

3
%%%%
OR 1 2

OR 2 3

XOR 2 4

! 0 0 2 3
%%%% end
*/
