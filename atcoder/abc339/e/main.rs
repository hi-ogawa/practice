// AC

// https://atcoder.jp/contests/abc339/tasks/abc339_e

fn main() {
    // 10^5
    let [_n, d]: [usize; 2] = read_array();
    let ls: Vec<usize> = read_vec();
    let k = ls.iter().max().unwrap() + 1;

    // take range max vertically
    let mut tree = SegmentTree::new(k);
    for i in ls {
        let v = tree.range_max(i.saturating_sub(d), (i + d + 1).min(k));
        tree.set(i, v + 1);
    }
    let result = tree.range_max(0, k);
    println!("{}", result);
}

struct SegmentTree {
    n: usize,
    data: Vec<usize>,
}

impl SegmentTree {
    fn new(n: usize) -> Self {
        let n = 2f64.powf((n as f64).log2().ceil()) as usize;
        Self {
            n,
            data: vec![0; 2 * n],
        }
    }

    fn set(&mut self, i: usize, v: usize) {
        let mut i = i + self.n;
        self.data[i] = v;
        while i > 1 {
            i /= 2;
            self.data[i] = self.data[2 * i].max(self.data[2 * i + 1]);
        }
    }

    fn range_max(&self, mut l: usize, mut r: usize) -> usize {
        l += self.n;
        r += self.n;
        let mut res = 0;
        while l < r {
            if l & 1 > 0 {
                res = res.max(self.data[l]);
                l += 1;
            }
            if r & 1 > 0 {
                r -= 1;
                res = res.max(self.data[r]);
            }
            l /= 2;
            r /= 2;
        }
        res
    }
}

/*
python misc/run.py atcoder/abc339/e/main.rs

%%%% begin
4 2
3 5 1 2
%%%%
3
%%%% end

%%%% begin
5 10
10 20 100 110 120
%%%%
3
%%%% end

%%%% begin
11 7
21 10 3 19 28 12 11 3 3 15 16
%%%%
6
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
