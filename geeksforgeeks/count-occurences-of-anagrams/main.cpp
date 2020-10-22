// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
int mainSolve(const string& s1, const string& s2) {
  int n1 = s1.size(); // \in [1, 10^5]
  int n2 = s2.size();

  const int k = 1 << 8;

  vector<int> cnts1(k);
  for (auto x : s1) { cnts1[x]++; }

  vector<int> cnts2(k);
  int res = 0;
  FOR(i, 0, n2) {
    cnts2[s2[i]]++;
    if (i >= n1) {
      cnts2[s2[i - n1]]--;
    }
    res += (cnts1 == cnts2);
  }
  return res;
}

// For submission
class Solution{
public:
  int search(const string& s1, const string& s2) {
    return mainSolve(s1, s2);
  }
};

// For local testing
int main() {
  string s1, s2;
  cin >> s1 >> s2;
  cout << mainSolve(s1, s2) << "\n";
  return 0;
}

/*
python misc/run.py geeksforgeeks/count-occurences-of-anagrams/main.cpp

%%%% begin
aaba
aabaabaa
%%%%
4
%%%% end
*/
