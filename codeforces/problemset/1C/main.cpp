// AC

// TODO: follow up cool formula from editorial

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

// NOTE: matrix is row major, contrary to OpenGL convention.
namespace glm {

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
struct mat : array<array<T, N>, N> {
  mat() : mat(vec<T, N * N>()) { }
  mat(const vec<T, N * N>& x) {
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        (*this)[i][j] = x[i * N + j];
  }
  friend vec<T, N> operator*(const mat& x, const vec<T, N>& y) {
    vec<T, N> z = {};
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        z[i] += x[i][j] * y[j];
    return z;
  }
  friend mat operator*(const mat& x, const mat& y) {
    mat z;
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        for (size_t k = 0; k < N; k++)
          z[i][j] += x[i][k] * y[k][j];
    return z;
  }
};

template<class T>
mat<T, 2> inverse(const mat<T, 2> x) {
  auto a = x[0][0], b = x[0][1], c = x[1][0], d = x[1][1];
  auto det = a * d - b * c;
  return mat<T, 2>(vec<T, 4>({d, -b, -c, a}) / det);
}

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

template<class T, size_t N>
vec<T, 2> normalize(const vec<T, N> x) { return x / length(x); }

} // namespace glm

using namespace glm;
using Real = double;
using vec2 = vec<Real, 2>;
using mat2 = mat<Real, 2>;
const Real pi = acos(-1);

// Main
void mainCase() {
  array<vec2, 3> ps;
  cin >> ps;
  dbg(ps);

  // Find center of circumcircle
  vec2 center = {};
  {
    // Solve v0 + t0 u0 = v1 + t1 u1
    mat2 rot90({0, -1, 1, 0});
    vec2 v0 = (ps[0] + ps[1]) / 2;
    vec2 u0 = rot90 * (ps[1] - ps[0]);
    vec2 v1 = (ps[0] + ps[2]) / 2;
    vec2 u1 = rot90 * (ps[2] - ps[0]);
    mat2 a({u0[0], -u1[0], u0[1], -u1[1]});
    vec2 t = inverse(a) * (v1 - v0);
    center = v0 + u0 * t[0];
  }
  dbg(center);
  FOR(i, 0, 3) { dbg(i, length(ps[i] - center)); }

  // Noramlize
  Real r = length(ps[0] - center);
  array<vec2, 3> vs;
  FOR(i, 0, 3) { vs[i] = normalize(ps[i] - center); }
  dbg(r, vs);

  // Find two inner angles
  auto clamp = [](Real x) { return min(Real(1), max(Real(-1), x)); };
  Real t1 = acos(clamp(dot(vs[0], vs[1])));
  Real t2 = acos(clamp(dot(vs[0], vs[2])));
  dbg(t1, t2);

  // Find minimal p s.t. p.t1, p,t2 \in 2pi.Z
  auto isInteger = [](Real x, Real eps = 1e-3) { return abs(x - round(x)) < eps; };
  const int p_lim = 100; // at most 100-gon
  int p = -1, q1, q2;
  FOR(i, 3, p_lim + 1) {
    dbg(i, i * t1 / (2 * pi), i * t2 / (2 * pi));
    if (isInteger(i * t1 / (2 * pi)) && isInteger(i * t2 / (2 * pi))) {
      p = i;
      q1 = round(p * t1 / (2 * pi));
      q2 = round(p * t2 / (2 * pi));
      break;
    }
  }
  assert(p != -1);
  dbg(p, q1, q2);

  // Recular p-gon
  Real res = r * r * p * sin(2 * pi / p) / 2;
  cout << setprecision(numeric_limits<Real>::digits10 + 1) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1C/main.cpp --check

%%%% begin
88.653021 18.024220
51.942488 -2.527850
76.164701 24.553012
%%%%
1452.52866331
%%%% end

%%%% begin
-46.482632 -31.161247
19.689679 -70.646972
-17.902656 -58.455808
%%%%
23949.55216407458
%%%% end

%%%% begin
0.000000 0.000000
1.000000 1.000000
0.000000 1.000000
%%%%
1.00000000
%%%% end

%%%% begin
71.756151 7.532275
-48.634784 100.159986
91.778633 158.107739
%%%%
9991.278787608771
%%%% end
*/
