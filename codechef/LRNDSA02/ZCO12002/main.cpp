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
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

void mainCase() {
  int n, m1, m2;
  cin >> n >> m1 >> m2;

  vector<int> ls1(n, 0);
  vector<int> ls2(n, 0);
  vector<int> vs(m1, 0);
  vector<int> ws(m2, 0);
  RANGE(i, 0, n) {
    cin >> ls1[i] >> ls2[i];
  }
  cin >> vs;
  cin >> ws;
  sort(ALL(vs));
  sort(ALL(ws));

  // argsort
  vector<int> ls1_arg(n, 0);
  vector<int> ls2_arg(n, 0);
  iota(ALL(ls1_arg), 0);
  iota(ALL(ls2_arg), 0);
  sort(ALL(ls1_arg), [&](auto x, auto y) { return ls1[x] < ls1[y]; });
  sort(ALL(ls2_arg), [&](auto x, auto y) { return ls2[x] < ls2[y]; });

  #ifdef DEBUG
    DD(ls1);
    DD(ls2);
    DD(ls1_arg);
    DD(ls2_arg);
    DD(vs);
    DD(ws);
  #endif

  // For each contest (ai, bi) ∈ ls1 x ls2, find the closest [vj, wk] ⊇ [ai, bi]
  vector<int> lefts(n, -1);
  {
    int j = 0;
    RANGE(i, 0, n) {
      while (j < m1 && vs[j] <= ls1[ls1_arg[i]]) {
        lefts[ls1_arg[i]] = j++;
      }
      j = max(j - 1, 0); // retry
    }
    #ifdef DEBUG
      DD(lefts);
    #endif
  }

  vector<int> rights(n, -1);
  {
    int j = m2 - 1;
    for (int i = n - 1; i >= 0; i--) {
      while (0 <= j && ws[j] >= ls2[ls2_arg[i]]) {
        rights[ls2_arg[i]] = j--;
      }
      j = min(j + 1, m2 - 1); // retry
    }
    #ifdef DEBUG
      DD(rights);
    #endif
  }

  // Find minimal closest pair [vj, wk]
  int mini = 1e9;
  RANGE(i, 0, n) {
    int j = lefts[i];
    int k = rights[i];
    if (j == -1 || k == -1) { continue; }
    mini = min(mini, ws[k] - vs[j] + 1);
  }
  cout << mini << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA02/ZCO12002/main.cpp --check

%%%% begin
3 4 2
15 21
5 10
7 25
4 14 25 2
13 21
%%%%
8
%%%% end
*/
