// CONTEST

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts> istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T>     istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n;
  cin >> n;

  vector<int> ls(n, 0);
  cin >> ls;

  ll nq;
  cin >> nq;

  vector<tuple<char, int>> qs(nq, {0, 0});
  cin >> qs;

  // count
  map<int, ll> data1; // (type, amount)
  RANGE(i, 0, n) {
    data1[ls[i]]++;
  }

  // max heap
  set<tuple<ll, int>, greater<tuple<ll, int>>> data2; // (amount, type)
  for (auto [x, num_x] : data1) {
    data2.insert({num_x, x});
  }

  // DD(ls);
  // DD(qs);
  // DD(tie(data1, data2));

  vector<bool> res(nq, 0);
  RANGE(iq, 0, nq) {
    // Apply change
    auto [c, x] = qs[iq];
    auto delta = c == '+' ? 1 : -1;
    auto prev = data1[x];
    data2.erase({prev, x});
    data2.insert({prev + delta, x});
    data1[x] += delta;
    // DD(tie(data1, data2));

    // Answer query
    if (data2.empty()) {
      res[iq] = 0;
      continue;
    }

    // 8
    if (data2.size() >= 1) {
      auto [k1, x1] = *data2.begin();
      if (k1 >= 8) {
        res[iq] = 1;
        continue;
      }
    }

    // 6 2 or 4 4
    if (data2.size() >= 2) {
      auto it = data2.begin();
      auto [k1, x1] = *it++;
      auto [k2, x2] = *it++;
      if (k1 >= 6 && k2 >= 2) {
        res[iq] = 1;
        continue;
      }
      if (k1 >= 4 && k2 >= 4) {
        res[iq] = 1;
        continue;
      }
    }

    // 4 2 2
    if (data2.size() >= 3) {
      auto it = data2.begin();
      auto [k1, x1] = *it++;
      auto [k2, x2] = *it++;
      auto [k3, x3] = *it++;
      if (k1 >= 4 && k2 >= 2 && k3 >= 2) {
        res[iq] = 1;
        continue;
      }
    }

    res[iq] = 0;
  }
  // DD(res);

  for (auto r : res) {
    cout << (r ? "YES" : "NO") << endl;
  }
}

int main() {
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/ex1393B/main.cpp --check

%%%% begin
6
1 1 1 2 1 1
6
+ 2
+ 1
- 1
+ 2
- 1
+ 2
%%%%
NO
YES
NO
NO
NO
YES
%%%% end
*/
