// VC

#include <bits/stdc++.h>

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl
namespace std { template<class ...Ts> ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "{"; apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

// Main
using namespace std;

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, int> counts;
    for (auto c : s) {
      counts[c]++;
    }
    bool ok = true;
    for (auto [_c, count] : counts) {
      if (count % 2 == 1) {
        ok = false;
        break;
      }
    }
    cout << (ok ? "YES" : "NO") << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/COOK120/EVENTUAL/main.cpp --check

%%%% begin
4
6
cabbac
7
acabbad
18
fbedfcbdaebaaceeba
21
yourcrushlovesyouback
%%%%
YES
NO
YES
NO
%%%% end
*/
