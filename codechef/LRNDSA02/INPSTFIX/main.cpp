// AFTER EDITORIAL, AC

//
// Cf. shunting-yard algorithm
//
// NOTE:
//  Intution is
//    - WLOG, we deal with "flat" expression without parentheses (if there are parentheses, we can treat them as different "flat" layer).
//    - Imagine stack machine evaluating expression. (i.e. keep LHS and RHS evaluated before evaluating OPRATOR)
//    - As stack machine finds "same-or-lower" precedance operation, it evaluates LHS to single value.
//    - What's left on the stack has always "strictly" increasing precedance (o1 < o2 < o3)
//      thus, when we pop, we can just pop as much as possible in the order.
//
// TODO:
//   - Formalize the intuition into formal proposision and prove it.
//

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

void mainCase() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  map<char, int> ops({
      {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2}});

  string res = "";
  vector<char> ts(0, 0);
  RANGE(i, 0, n) {
    char c = s[i];

    // Parenthesis
    if (c == '(') {
      ts.push_back('(');
      continue;
    }
    if (c == ')') {
      while (ts.back() != '(') {  // assert(!ts.empty());
        res += ts.back();
        ts.pop_back();
      }
      ts.pop_back();  // pop '('
      continue;
    }

    // Symbol
    if (isalpha(c)) {
      res += c;
      continue;
    }

    // Operator
    assert(ops.count(c));
    while (!ts.empty() && ops.count(ts.back()) && ops[ts.back()] >= ops[c]) { // skip if back = '('
      res += ts.back();
      ts.pop_back();
    }
    ts.push_back(c);
  }

  // Pop what's left
  while (!ts.empty()) {
    assert(ops.count(ts.back()));
    res += ts.back();
    ts.pop_back();
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
python misc/run.py codechef/LRNDSA02/INPSTFIX/main.cpp --check

%%%% begin
1
9
A+B*C/D^E
%%%%
ABC*DE^/+
%%%% end

%%%% begin
1
5
(A+B)
%%%%
AB+
%%%% end

%%%% begin
1
11
(A+(B+(C)))
%%%%
ABC++
%%%% end

%%%% begin
2
15
((A+B)*D)^(E-F)
19
A+(B*C-(D/E^F)*G)*H
%%%%
AB+D*EF-^
ABC*DEF^/G*-H*+
%%%% end
*/
