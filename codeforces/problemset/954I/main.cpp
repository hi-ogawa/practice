// WIP

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

using cd = complex<double>;

uint32_t reverse32(uint32_t x) {
  x = ((x & 0x55555555U) <<  1) | ((x & 0xaaaaaaaaU) >>  1); // 0101 = 0x5, 1010 = 0xa
  x = ((x & 0x33333333U) <<  2) | ((x & 0xccccccccU) >>  2); // 0011 = 0x3, 1100 = 0xc
  x = ((x & 0x0f0f0f0fU) <<  4) | ((x & 0xf0f0f0f0U) >>  4);
  x = ((x & 0x00ff00ffU) <<  8) | ((x & 0xff00ff00U) >>  8);
  x = ((x & 0x0000ffffU) << 16) | ((x & 0xffff0000U) >> 16);
  return x;
}

void dft(vector<cd>& f, bool inv) {
  int n = f.size();
  int m = 0;
  while ((1 << m) < n) { m++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - m);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int l = 2; l <= n; l *= 2) {
    cd u = exp((inv ? 2i : -2i) * M_PI / (cd)l);
    for (int i = 0; i < n; i += l) {
      cd z = 1.0;
      for (int k = 0; k < l / 2; k++) {
        cd& x = f[i + k];
        cd& y = f[i + k + l / 2];
        tie(x, y) = make_tuple(x + z * y, x - z * y);
        z *= u;
      }
    }
  }
  if (inv) { for (auto& x : f) { x /= n; }}
}

void polymul(vector<cd>& p, vector<cd>& q, vector<cd>& r) {
  dft(p, 0); dft(q, 0);
  FOR(i, 0, (int)p.size()) { r[i] = p[i] * q[i]; }
  dft(r, 1);
}

// Main
void mainCase() {
  string s1, s2; // a..f x 125000
  cin >> s1 >> s2;
  int n1 = s1.size(), n2 = s2.size();

  vector<int> ls1(n1); // 0..5
  vector<int> ls2(n2);
  FOR(i, 0, n1) { ls1[i] = s1[i] - 'a'; }
  FOR(i, 0, n2) { ls2[i] = s2[i] - 'a'; }

  int k = 1;
  while (k < n1 + n2) { k *= 2; }
  vector<cd> p(k), q(k);

  const int lim = 6;
  FOR(i, 0, n1) {
    p[i] = exp(2i * M_PI * (cd)ls1[i] / (cd)lim);
  }
  FOR(i, 0, n2) {
    q[i] = exp(-2i * M_PI * (cd)ls2[n2 - i - 1] / (cd)lim);
  }

  // TODO: this doesn't really give us enough information for the distance
  vector<cd> pp(k), qq(k), r(k);
  auto matchWithMask = [&](int mask, vector<bool>& res) {
    fill(ALL(pp), 0);
    fill(ALL(qq), 0);
    FOR(i, 0, n1) {
      if ((1 << ls1[i]) & mask) {
        pp[i] = p[i];
      }
    }
    int cnt_active = 0;
    FOR(i, 0, n2) {
      if ((1 << ls2[n2 - i - 1]) & mask) {
        qq[i] = q[i];
        cnt_active++;
      }
    }
    polymul(pp, qq, r);
    FOR(i, 0, n1 - n2 + 1) {
      res[i] = round(r[i + n2 - 1].real()) == cnt_active;
    }
  };

  FOR(mask, 0, 1 << lim) {
    matchWithMask(mask, matches[mask]);
  }
  dbg2(matches);

  vector<int> res(n1 - n2 + 1, lim);
  FOR(i, 0, n1 - n2 + 1) {
    FOR(mask, 0, 1 << lim) {
      int t = 6;
      FOR(b, 0, lim) { t -= bool((1 << b) & mask); }
      if (matches[mask][i]) {
        res[i] = min(res[i], t);
      }
    }
  }
  dbg(res);
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
python misc/run.py codeforces/problemset/954I/main.cpp --check

%%%% begin
abcdefa
ddcb
%%%%
2 3 3 3
%%%% end
*/
