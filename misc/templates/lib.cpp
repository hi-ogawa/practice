// TODO:
// - DSU
// - Segment tree
// - Suffix array
// - ...

// Fenwick tree for sum
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

// Z function
vector<int> makeZ(const string& s) {
  int n = s.size();
  vector<int> z(n);
  int l = 1, r = 1; // [l, r)
  FOR(i, 1, n) {
    if (i < r) { z[i] = min(z[i - l], r - i); }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) { z[i]++; }
    if (i + z[i] > r) { l = i; r = i + z[i]; }
  }
  return z;
}

// 64bit hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
ull hash64(ull x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
};
