// AC

// https://atcoder.jp/contests/abc306/tasks/abc306_f

fn main() {
    // n ~ 10^4, m ~ 10^2
    let v: Vec<usize> = read_tokens();
    let (n, m) = (v[0], v[1]);

    // a ~ 10^9
    // sort everything while tracking group index
    let mut ls: Vec<(usize, usize)> = vec![];
    for i in 0..n {
        for x in read_tokens::<usize>() {
            ls.push((x, i));
        }
    }
    ls.sort();

    // count elements with group index j > i (complexity = O(n.m log(n.m)))
    let mut group_counts = FenwickTree::new(n);
    let mut result = 0;
    for (k, &(_x, i)) in ls.iter().enumerate() {
        result += k - group_counts.sum(i + 1);
        group_counts.incr(i, 1);
    }

    // add fixed contribution within same group
    result += ((1 + m) * m / 2) * (n * (n - 1) / 2);

    println!("{}", result);
}

//
// range sum
//

struct FenwickTree {
    n: usize,
    data: Vec<usize>,
}

impl FenwickTree {
    fn new(n: usize) -> Self {
        Self {
            n,
            data: vec![0; n + 1],
        }
    }

    fn incr(&mut self, i: usize, x: usize) {
        let mut k = i + 1;
        while k <= self.n {
            self.data[k] += x;
            k = (k | (k - 1)) + 1;
        }
    }

    fn sum(&self, mut i: usize) -> usize {
        let mut result = 0;
        while i > 0 {
            result += self.data[i];
            i = i & (i - 1);
        }
        result
    }
}

/*
python misc/run.py atcoder/abc306/f/main.rs

%%%% begin
3 2
1 3
2 8
4 6
%%%%
12
%%%% end

%%%% begin
1 1
306
%%%%
0
%%%% end

%%%% begin
4 4
155374934 164163676 576823355 954291757
797829355 404011431 353195922 138996221
191890310 782177068 818008580 384836991
160449218 545531545 840594328 501899080
%%%%
102
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<T: std::str::FromStr>() -> Vec<T>
where
    <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}
