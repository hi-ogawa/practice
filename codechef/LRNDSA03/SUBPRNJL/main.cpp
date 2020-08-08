// AFTER CONTEST, TLE, WIP

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
  int n, k;
  cin >> n >> k;
  vector<int> ls(n, 0);
  cin >> ls;
  // DD(ls);

  int res = 0;
  RANGE(i0, 0, n) {
    map<int, int> freqs;
    RANGE(i1, i0, n) {
      // Segment ls[i0:i1]
      freqs[ls[i1]]++;
      // DD(freqs);
      int t = i1 - i0 + 1;
      int m = (k + t - 1) / t;
      int r = m * t - k + 1;
      // DD(tie(k, t, m, r));

      // TODO: need better searching
      auto it = --freqs.end();
      int y = it->second;
      while (r > m * y) {
        it--;
        y += it->second;
      }
      int x = it->first;
      if (freqs.count(x) && freqs.count(freqs[x])) {
        res++;
      }
    }
  }

  cout << res << endl;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA03/SUBPRNJL/main.cpp --check

%%%% begin
1
3 3
1 2 3
%%%%
3
%%%% end
*/
