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

vector<int> makePrimes(int n) {
  vector<bool> sieve(n + 1, 1);
  for (int p = 2; p <= sqrt(n); p++) {
    if (!sieve[p]) { continue; }
    for (int x = p * p; x <= n; x += p) {
      sieve[x] = 0;
    }
  }
  vector<int> res;
  for (int x = 2; x <= n; x++) {
    if (sieve[x]) { res.push_back(x); }
  }
  return res;
}

// Main
void mainCase() {
  ll n; // [1, 10^5]  (p_9592 = 99991)
  cin >> n;

  auto ps = makePrimes(n);
  auto ps_part = partition(ALL(ps), [&](auto x) { return x <= sqrt(n); });

  vector<int> ps1(ps.begin(), ps_part);
  vector<int> ps2(ps_part, ps.end());
  // dbg(ps1); dbg(ps2);
  dbgv(ps1.size(), ps2.size());

  ll res = 1;
  set<ll> ls;
  FOR(i, 1, n + 1) { ls.insert(i); }

  auto ask = [](char t, ll x) -> ll {
    cout << t << " " << x << endl;
    ll k;
    cin >> k;
    return k;
  };

  // Check small primes
  for (auto p : ps1) {
    ask('B', p);
    for (int x = p; x <= n; x += p) { ls.erase(x); }

    if (ask('A', p) == 0) {
      continue;
    }

    ll pe = p;
    while (true) {
      if (pe * p > n) {
        res *= pe;
        break;
      }
      if (ask('B', pe * p) == 0) {
        res *= pe;
        break;
      }
      pe *= p;
    }
  }

  // At most single big prime factor
  if (res > 1) {
    // x = res  or  x = res * p
    for (auto p : ps2) {
      if (res * p > n) { break; }

      ll k = ask('A', p);
      assert(k == 1 || k == 2); // prime only or prime with x
      if (k == 2) {
        res *= p;
        break;
      }
    }
  } else {

    // x = p > sqrt(n)  or  x = 1
    int m = ps2.size();
    int m_blk = sqrt(m);
    vector<vector<int>> blks(1);
    for (auto p : ps2) {
      if ((int)blks.back().size() > m_blk) {
        blks.emplace_back();
      }
      blks.back().push_back(p);
    }
    dbg(blks);

    bool found = 0;
    for (auto& blk : blks) {
      // Delete this block of primes
      for (auto p : blk) {
        ll kp = ask('B', p);
        assert(kp == 1); // hit prime only
        for (int x = p; x <= n; x += p) { ls.erase(x); }
      }

      ll k = ask('A', 1);
      if (k == (int)ls.size()) { continue; } // x not in this block

      assert(k == (int)ls.size() + 1); // x in this block
      for (auto p : blk) {
        int kp = ask('A', p);
        assert(kp == 1 || kp == 0); // x = p or not
        if (kp == 1) {
          res = p;
          found = 1;
          break;
        }
      }
      if (found) { break; }
    }
  }
  cout << "C " << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest670/e/main_v2.cpp --check
*/
