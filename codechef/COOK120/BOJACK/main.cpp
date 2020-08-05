// AFTER EDITORIAL

#include <bits/stdc++.h>

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std { template<class ...Ts> ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "{"; apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

// Main
using namespace std;

string solve(int d) {
  string s;
  RANGE(i, 0, d) s += "a";
  RANGE(i, 0, d) s += "b";
  return s;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int d;
    cin >> d;
    auto s = solve(d);
    cout << s.size() << endl;
    cout << s << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/COOK120/BOJACK/main.cpp --check

%%%% begin
4
4
10
15
60
%%%%
4
todd
5
diane
6
bojack
12
peanutbutter
%%%% end
*/
