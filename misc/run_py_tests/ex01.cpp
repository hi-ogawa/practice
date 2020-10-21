// Testing memory usage
// NOTE:
//   It doesn't seem to be working.
//   run.py always reports "memory: 5680 kB".
//

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> buffer(n, 1);
  int res = 0;
  for (auto x : buffer) {
    res += x;
  }
  cout << res << "\n";
  return 0;
}

/*
python misc/run.py misc/run_py_tests/ex01.cpp

%%%% begin
100000000
%%%%
100000000
%%%% end
*/
