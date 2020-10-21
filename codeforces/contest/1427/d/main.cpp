// WIP

// TODO: I believe my construction is correct, but cannot find simple implementation.

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n; // [1, 52]
  cin >> n;
  vector<int> ls(n); // {1, .., n}
  cin >> ls;

  // Handle small cases
  if (n == 1) { cout << 0 << "\n"; return; }

  if (n == 2) {
    if (ls[0] == 1) { cout << 0 << "\n"; return; }
    cout << 1 << "\n";
    cout << "2 1 1" << "\n";
    return;
  }

  vector<vector<int>> res;

  // Apply shuffle
  auto update = [&](const vector<int>& s) {
    dbg(s);
    return;
    res.push_back(s);
    int k = s.size();
    vector<vector<int>> segs(k);
    int p = 0;
    FOR(i, 0, k - 1) {
      segs[i] = vector<int>(ls.begin() + p, ls.begin() + p + s[i]);
    }
    reverse(ALL(segs));
    ls.clear();
    for (auto& seg : segs) {
      ls.insert(ls.end(), ALL(seg));
    }
  };

  // Given (1..i) or (i..1), construct (1..i) (i+1) (i+2) or (i+2) (i+2) (i..1)
  auto solve1 = [&](int i) {
  };

  auto solve2 = [&](int i) {
  };

  // Given (1..i) or (i..1), construct (1..i) (i+1) (i+2) or (i+2) (i+2) (i..1)
  // TODO: handle even case
  for (int i = 1; i <= n - 2; i += 2) {
    int p = distance(ls.begin(), find(ALL(ls), 1));
    int p0 = distance(ls.begin(), find(ALL(ls), i));
    int p1 = distance(ls.begin(), find(ALL(ls), i + 1));
    int p2 = distance(ls.begin(), find(ALL(ls), i + 2));
    assert(p <= p0);
    dbg(p, p0, p1, p2);

    // Handle 12 patterns manually
    if (p <= p0) {
      if (p0 < p1 && p1 < p2) { // (1..i) (i+1) (i+2)
        vector<int> s1 = {{p, p1 - p, 1, p2 - p1, n - 1 - p2}};
        vector<int> s2 = {{p1 - 1, 1, 1, i, n - 1 - (p1 + i)}};
        update(s1);
        update(s2);
      }
      if (p0 < p2 && p2 < p1) { // (1..i) (i+2) (i+1)
        vector<int> s1 = {{p, p2 - p, 1, p1 - p2, n - 1 - p1}};
        vector<int> s2 = {{p2 - 1, 2, i, n - 1 - (p2 + i)}};
        update(s1);
        update(s2);
      }
      if (p1 < p0 && p0 < p2) { // (i+1) (1..i) (i+2)
        vector<int> s1 = {{p1, p - p1, i, p2 - p0, n - 1 - p2}};
        vector<int> s2 = {{p - 1, 1, i + 1, n - 1 - (p + i + 1)}};
        update(s1);
        update(s2);
      }
      if (p1 < p2 && p2 < p0) { // (i+1) (i+2) (1..i)
        vector<int> s1 = {{p1, p2 - p1, 1, p0 - p2, n - 1 - p0}};
        vector<int> s2;
        s2.push_back(p2 - 1);
        FOR(_, 0, i) { s2.push_back(1); }
        s2.push_back(2);
        s2.push_back(n - 1 - (p2 + 1));
        update(s1);
        update(s2);
      }
      if (p2 < p0 && p0 < p1) { // (i+2) (1..i) (i+1)
        vector<int> s1;
        vector<int> s2;
      }
      if (p2 < p1 && p1 < p0) { // (i+2) (i+1) (1..i)
      }
    } else {
      if (p0 < p1 && p1 < p2) { // (i..1) (i+1) (i+2)
      }
      if (p0 < p2 && p2 < p1) { // (i..1) (i+2) (i+1)
      }
      if (p1 < p0 && p0 < p2) { // (i+1) (i..1) (i+2)
      }
      if (p1 < p2 && p2 < p0) { // (i+1) (i+2) (i..1)
      }
      if (p2 < p0 && p0 < p1) { // (i+2) (i..1) (i+1)
      }
      if (p2 < p1 && p1 < p0) { // (i+2) (i+1) (i..1)
      }
    }

    dbg(ls);
  }
  dbg(res);
  // assert((int)res.size() == n - 2);

  if (ls.front() == n) {
    res.push_back(vector<int>(n, 1));
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest-global-round-11/d/main.cpp

%%%% begin
4
3 1 2 4
%%%%
2
3 1 2 1
2 1 3
%%%% end

%%%% begin
6
6 5 4 3 2 1
%%%%
1
6 1 1 1 1 1 1
%%%% end

%%%% begin
1
1
%%%%
0
%%%% end
*/
