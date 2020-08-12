// AFTER CONTEST, AC

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
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  string ss; // len(s) <= 10^5
  cin >> ss;

  ll n = ss.size();
  vector<int> s(n, 0);
  RANGE(i, 0, n) { s[i] = ss[i] - '0'; }

  vector<vector<ll>> positions(10, vector<ll>(0, 0));
  RANGE(i, 0, n) {
    positions[s[i]].push_back(i);
  }
  // DD(positions);

  // BFS
  deque<int> q;
  vector<ll> dists(n, -1);
  vector<bool> digits_done(10, 0);
  q.push_back(n - 1);
  dists[n - 1] = 0;
  while (true) {
    assert(!q.empty());
    int i = q.front(); q.pop_front();
    if (i == 0) { break; }

    int d = dists[i] + 1;
    if (i - 1 >= 0 && dists[i - 1] == -1) {
      dists[i - 1] = d;
      q.push_back(i - 1);
    }
    if (i + 1 < n && dists[i + 1] == -1) {
      dists[i + 1] = d;
      q.push_back(i + 1);
    }
    if (!digits_done[s[i]]) {
      for (auto j : positions[s[i]]) {
        if (dists[j] == -1) {
          dists[j] = d;
          q.push_back(j);
        }
      }
      digits_done[s[i]] = 1;
    }
  }
  cout << dists[0] << endl;
}

int main() {
  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  // return 0;
}

/*
python misc/run.py codechef/LRNDSA08/DIGJUMP/main.cpp --check

%%%% begin
0000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111
%%%%
3
%%%% end

%%%% begin
01234567890
%%%%
1
%%%% end

%%%% begin
012134444444443
%%%%
4
%%%% end
*/
