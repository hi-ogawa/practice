// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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

// glm
template<class T, size_t N>
struct vec : array<T, N> {
  vec& operator+=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] += y[i]; } return *this; }
  vec& operator-=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] -= y[i]; } return *this; }
  vec& operator*=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] *= y[i]; } return *this; }
  vec& operator/=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] /= y[i]; } return *this; }
  vec& operator+=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] += y; } return *this; }
  vec& operator-=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] -= y; } return *this; }
  vec& operator*=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] *= y; } return *this; }
  vec& operator/=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] /= y; } return *this; }
  friend vec operator+(const vec& x, const vec& y) { return vec(x) += y; }
  friend vec operator-(const vec& x, const vec& y) { return vec(x) -= y; }
  friend vec operator*(const vec& x, const vec& y) { return vec(x) *= y; }
  friend vec operator/(const vec& x, const vec& y) { return vec(x) /= y; }
  friend vec operator+(const vec& x, T y) { return vec(x) += y; }
  friend vec operator-(const vec& x, T y) { return vec(x) -= y; }
  friend vec operator*(const vec& x, T y) { return vec(x) *= y; }
  friend vec operator/(const vec& x, T y) { return vec(x) /= y; }
};

template<class T, size_t N>
T dot(const vec<T, N>& x, const vec<T, N>& y) {
  T z = 0;
  for (size_t i = 0; i < N; i++) z += x[i] * y[i];
  return z;
}

template<class T, size_t N>
T dot2(const vec<T, N>& x) { return dot(x, x); }

template<class T, size_t N>
T length(const vec<T, N>& x) { return sqrt(dot2(x)); }

// Floating point
using Real = double;
const Real kEps = 1e-10;

using vec2 = vec<Real, 2>;

// Main
int mainSolve(vector<vec2>& ls, int r) {
  int n = ls.size();

  // Brute force by circumcircle of two points
  auto getCenter = [&](vec2 p1, vec2 p2) -> vec2 {
    vec2 p = (p1 + p2) / 2;
    vec2 v = p2 - p1;
    Real l = length(v) / 2;
    vec2 vt = {v[1], -v[0]};
    vec2 c = p + vt * sqrt(r * r - l * l) / length(v);
    return c;
  };

  auto countDarts = [&](vec2 p1, vec2 p2) -> int {
    vec2 c = p1;
    if (p1 != p2) { c = getCenter(p1, p2); }
    int res = 0;
    for (auto p : ls) {
      if (length(p - c) <= r + kEps) {
        res++;
      }
    }
    return res;
  };

  int res = 0;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      int t = countDarts(ls[i], ls[j]);
      res = max(res, t);
    }
  }
  return res;
}

// Submission
class Solution {
public:
    int numPoints(vector<vector<int>>& points, int r) {
      vector<vec2> ls;
      for (auto& p : points) {
        ls.push_back({Real(p[0]), Real(p[1])});
      }
      return mainSolve(ls, r);
    }
};

// Testing
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  int r; // [1, 5000]
  cin >> r;
  vector<vec2> ls(n); // [-10^4, 10^4]
  cin >> ls;
  auto res = mainSolve(ls, r);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py leetcode/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/main.cpp

%%%% begin
6
2
1 2
3 5
1 -1
2 3
4 1
1 3
%%%%
4
%%%% end
*/
