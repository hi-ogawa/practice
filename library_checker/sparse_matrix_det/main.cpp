// WIP

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

// Modulo
template<ll Modulo>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = Modulo;
  uint32_t v;
  ModInt() : v{0} {}
  template<class T> ModInt(T x) {
    ll y = (ll)x % modulo;
    if (y < 0) { y += modulo; }
    v = y;
  }
  friend istream& operator>>(istream& istr,       mint& self) { return istr >> self.v; }
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }
  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = (ll)v * y.v % modulo; return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  friend bool operator==(const mint& x, const mint& y) { return x.v == y.v; }
  friend bool operator!=(const mint& x, const mint& y) { return x.v != y.v; }
  mint inv() const { return pow(modulo - 2); }
  mint pow(ll e) const {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }
};

using mint = ModInt<998244353>; // = 1 + 2^23 x 7 x 17

// Compressed sparse row format (see scipy.sparse.csr_matrix for the convention)
struct MatrixCSR {
  int n, nz;
  vector<int> indices, indptr;
  vector<mint> data;

  MatrixCSR(int _n, vector<array<int, 3>>& coo) {
    n = _n;
    nz = coo.size();
    indices.resize(n + 1);
    indptr.resize(nz);
    data.resize(nz);
    sort(ALL(coo));
    int i0 = 0, p = 0;
    for (auto [i, j, d] : coo) {
      while (i0 < i) { indices[++i0] = p; }
      indptr[p] = j;
      data[p] = d;
      p++;
    }
    while (i0 < n) { indices[++i0] = p; }
    dbg(indices, indptr, data);
  }

  // TOOD:
  //   - preprocess to reduce non-zero entry? (e.g. sort rows by non-zero count)
  //   - I feel worst case there can be n^2 non zero elements...
  mint determinant() {
    mint res = 1;
    vector<int> cnts(n); // Count processed elements for each row
    auto is_zero = [&](int i, int j) {
      data[cnts[i]]
      return cnts[i] == indices[i + 1] ||
    };

    FOR(i, 0, n) {
      // Find pivot
      if (cnts[i] == indices[i + 1]) { // i.e. m[i][i] == 0
        int p = -1;
        FOR(k, i + 1, n) {
          // ps[k]
          // if ()
        }
        if (p == -1) { res = 0; break; } // Singular
        if (p != )
        // ps[k]
      }
      // Clear rows
      FOR(k, i + 1, n) {
        if (cnts[i] < indices[i + 1]) { // i.e. m[k][i] != 0
          // mint c =
        }
      }
    }
    return res;
  }
};

// Main
void mainCase() {
  int n, nz;
  cin >> n >> nz;
  vector<array<int, 3>> coo(nz); // Coordinate format
  cin >> coo;

  auto csr = MatrixCSR(n, coo);
  // mint res = csr.determinant();
  // cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/sparse_matrix_det/main.cpp --check

%%%% begin
3 3
0 0 1
1 1 2
2 2 3
%%%%
6
%%%% end

%%%% begin
3 1
0 0 1
%%%%
0
%%%% end
*/
