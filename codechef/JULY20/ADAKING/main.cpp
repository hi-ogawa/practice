// VC, AC

#include <bits/stdc++.h>

#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
#define PP(X) std::cout << #X ": " << (X) << std::endl
#define PPP(X) std::cout << #X ": {"; for (auto x : X) { std::cout << x << ", "; } std::cout << "}" << std::endl;

using namespace std;
using ll = int64_t;

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int k;
    cin >> k;
    k--;
    int r = k / 8;
    int c = k % 8;
    RANGE(j1, 0, 8) {
      RANGE(j2, 0, 8) {
        if (j1 == 0 && j2 == 0) {
          cout << "O";
          continue;
        }
        cout << ((tie(j1, j2) <= tie(r, c)) ? "." : "X");
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/JULY20/ADAKING/main.cpp --check

%%%% begin
4
1
5
9
64
%%%%
........
........
........
.XXX....
.XOX....
.XXX....
........
........

........
........
........
........
........
XXX.....
..XX....
O..X....

........
.XXXXXXX
.X.O...X
.X...XXX
.XXX.X..
...XXX..
........
........

........
........
........
...O....
........
........
........
........
%%%% end
*/
