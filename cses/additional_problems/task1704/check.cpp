#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Check
int check(istream& inp, istream& outp) {
  int n;
  inp >> n;
  vector<tuple<int, int>> edges(n - 1, {0, 0});
  inp >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  int m;
  outp >> m;
  vector<tuple<int, int>> new_edges(m, {0, 0});
  outp >> new_edges;
  for (auto& [x, y] : new_edges) { x--; y--; }

  //
  // Bridge check by brute-force
  //
  edges.insert(edges.end(), ALL(new_edges));

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y); swap(x, y);
    adj[x].push_back(y);
  }

  // Check if connected without edge (v0, v1)
  auto dfs = [&](int v0, int v1) -> bool {
    vector<int> done(n, 0);
    vector<int> st;
    st.push_back(0);
    while (!st.empty()) {
      int v = st.back(); st.pop_back();
      for (auto u : adj[v]) {
        if ((v == v0 && u == v1) || (v == v1 && u == v0)) { continue; }
        if (done[u]) { continue; }
        done[u] = 1;
        st.push_back(u);
      }
    }
    return accumulate(ALL(done), 0) == n;
  };

  for (auto [x, y] : edges) {
    bool tmp = dfs(x, y);
    if (!tmp) {
      printf("Found bridge: (%d, %d)\n", x + 1, y + 1);
      return -1;
    }
  }
  return 0;
}

int main(int argc, const char* argv[]) {
  assert(argc >= 3);
  ifstream inp(argv[1]);
  ifstream outp(argv[2]);
  assert(inp);
  assert(outp);
  return check(inp, outp);
}
