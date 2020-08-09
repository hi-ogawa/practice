// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
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
  int n, nq;
  cin >> n >> nq;

  vector<ll> ls1(n, 0);
  vector<ll> ls2(n, 0);
  cin >> ls1 >> ls2;

  vector<int> qs(nq, 0); // q <= 10^4, nq <= 500
  cin >> qs;

  sort(ALL(ls1));
  sort(ALL(ls2));

  auto getCount = [&](ll s) {
    ll res = 0;
    int i = 0;
    int j = n - 1;
    // i up and j down
    while (i < n && j >= 0) {
      while (ls1[i] + ls2[j] > s && j >= 0) {
        j--;
      }
      res += j + 1;
      i++;
    }
    return res;
  };

  // min(s | q <= getCount(s) )
  auto search = [&](ll q) {
    // Half open (s0, s1]
    ll s0 = 0;
    ll s1 = ls1.back() + ls2.back();
    while (s0 + 1 < s1) {
      ll s = (s0 + s1 + 1) / 2;
      ll c = getCount(s);
      if (q <= c) {
        s1 = s;
      } else {
        s0 = s + 1;
      }
    }
    return s1;
  };

  // [ Without precomputation ]
  // for (auto q : qs) {
  //   cout << search(q) << endl;
  // }

  // [ With precomputation ]
  // Precompute up to query's bound
  ll q_max = 10000;
  ll s = search(q_max);
  vector<ll> data;
  {
    int i = 0;
    int j = n - 1;
    // i up and j down
    while (i < n && j >= 0) {
      while (ls1[i] + ls2[j] > s && j >= 0) {
        j--;
      }
      RANGE(jj, 0, j + 1) {
        data.push_back(ls1[i] + ls2[jj]);
      }
      i++;
    }
  }
  sort(ALL(data));
  // DD(data);

  for (auto q : qs) {
    cout << data[q - 1] << endl; // one-based index
  }
}

int main() {
  // [ Single case ]
  // mainCase()

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA04/LOWSUM/main.cpp --check

%%%% begin
1
3 1
1 2 3
4 5 6
4
%%%%
7
%%%% end
*/
