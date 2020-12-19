// RE

// NOTE: Experimented with pbds but something seems awful...

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Customizing pbds tree (cf. https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/ext/pb_ds/detail/tree_policy/order_statistics_imp.hpp)
#include <ext/pb_ds/assoc_container.hpp>

template<typename Const_Node_Iter, typename Node_Iter, typename Cmp_Fn, typename _Alloc>
struct CustomNodeUpdate {
  using metadata_type = ll;

  void operator()(Node_Iter it, Const_Node_Iter it_end) const {
    ll acc = (*it)->second;
    for (auto it_child : {it.get_l_child(), it.get_r_child()}) {
      acc += (it_child == it_end) ? 0 : it_child.get_metadata();
    }
    const_cast<metadata_type&>(it.get_metadata()) = acc;
  };
};

using Key = pair<int, ll>;
using CustomTree = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, less<Key>,
  __gnu_pbds::rb_tree_tag, CustomNodeUpdate>;


// Main
void mainCase() {
  int n, nq; // [1, 5 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  CustomTree tree;
  FOR(i, 0, n) { tree.insert({i, ls[i]}); }

  auto incr = [&](int i, int v) {
    tree.erase({i, ls[i]});
    tree.insert({i, ls[i] += v});
  };

  auto reduce = [&](int l, int r) -> ll {
    CustomTree t1, t2;
    tree.split({r, -1}, t1);
    tree.split({l, -1}, t2);
    auto res = t2.node_begin().get_metadata();
    tree.join(t2);
    tree.join(t1);
    return res;
  };

  for (auto [t, x, y] : qs) {
    if (t == 0) {
      incr(x, y);
    }
    if (t == 1) {
      auto res = reduce(x, y);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/point_add_range_sum/main.cpp

%%%% begin
5 5
1 2 3 4 5
1 0 5
1 2 4
0 3 10
1 0 5
1 0 3
%%%%
15
7
25
6
%%%% end
*/
