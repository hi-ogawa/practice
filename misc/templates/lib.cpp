// TODO:
// - DSU
// - Segment tree
// - Suffix array
// - ...

struct FenwickTree {
  int n_;
  vector<int> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int qi, int qv) {
    while (qi < n_) {
      data_[qi] += qv;
      qi = (qi | (qi + 1));
    }
  }
  int reduce(int qi) { // [0, qi)
    qi--;
    ll res = 0;
    while (qi >= 0) {
      res += data_[qi];
      qi = (qi & (qi + 1)) - 1;
    }
    return res;
  }
  int reduce(int l, int r) { // [l, r)
    return reduce(r) - reduce(l);
  }
};
