// TLE

/*
it takes about 0.5 sec on local machine

$ time ./build/main < cses/string_algorithms/task2420-palindrome-queries/data/in-1.txt > /dev/null

real    0m0.442s
user    0m0.414s
sys     0m0.028s
*/

use std::{fmt::Debug, io, str::FromStr};

const BASE: usize = 17;
const MODULO: usize = 7 + 1e9 as usize;

#[derive(Debug)]
struct SegmentTree {
    n: usize,
    data: Vec<(usize, usize, usize)>, // (hash left-to-right, hash right-to-left, length)
}

fn multiply(l: (usize, usize, usize), r: (usize, usize, usize)) -> (usize, usize, usize) {
    let c0 = pow(BASE, l.2, MODULO);
    let c1 = pow(BASE, r.2, MODULO);
    (
        (l.0 + c0 * r.0) % MODULO,
        (c1 * l.1 + r.1) % MODULO,
        l.2 + r.2,
    )
}

impl SegmentTree {
    fn new(n_orig: usize) -> Self {
        let mut n = 1;
        while n < n_orig {
            n *= 2;
        }
        SegmentTree {
            n,
            data: vec![(0, 0, 1); 2 * n],
        }
    }

    fn set(&mut self, qi: usize, qv: usize) -> () {
        let mut k = self.n + qi;
        self.data[k] = (qv, qv, 1);
        while k > 1 {
            k /= 2;
            self.data[k] = multiply(self.data[2 * k], self.data[2 * k + 1]);
        }
    }

    fn reduce(&self, ql: usize, qr: usize) -> (usize, usize, usize) {
        self.reduce_impl(ql, qr, 0, self.n, 1)
    }

    fn reduce_impl(
        &self,
        ql: usize,
        qr: usize,
        l: usize,
        r: usize,
        k: usize,
    ) -> (usize, usize, usize) {
        if r <= ql {
            return (0, 0, 0);
        }
        if qr <= l {
            return (0, 0, 0);
        }
        if ql <= l && r <= qr {
            return self.data[k];
        }
        let mid = (l + r) / 2;
        let result_l = self.reduce_impl(ql, qr, l, mid, 2 * k);
        let result_r = self.reduce_impl(ql, qr, mid, r, 2 * k + 1);
        multiply(result_l, result_r)
    }
}

fn pow(x: usize, mut p: usize, m: usize) -> usize {
    let mut y = x;
    let mut result = 1;
    while p > 0 {
        if p & 1 > 0 {
            result = result * y % m;
        }
        y = y * y % m;
        p >>= 1;
    }
    result
}

fn main_case() -> io::Result<()> {
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let s = read_tokens::<String>()?[0].clone();

    let mut seg_tree = SegmentTree::new(n);

    for (i, c) in s.bytes().enumerate() {
        seg_tree.set(i, c as usize);
    }

    for _ in 0..m {
        let vec = read_tokens::<String>()?;
        match &vec[0][..] {
            "1" => {
                let k: usize = vec[1].parse().unwrap();
                let v = vec[2].bytes().next().unwrap() as usize;
                seg_tree.set(k - 1, v);
            }
            "2" => {
                let l: usize = vec[1].parse().unwrap();
                let r: usize = vec[2].parse().unwrap();
                let (h0, h1, _) = seg_tree.reduce(l - 1, r);
                println!("{}", if h0 == h1 { "YES" } else { "NO" });
            }
            _ => unreachable!(),
        }
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py cses/string_algorithms/task2420-palindrome-queries/main.rs
python misc/run.py cses/string_algorithms/task2420-palindrome-queries/main.rs --check --test 'file:cses/string_algorithms/task2420-palindrome-queries/data/in-1.txt:cses/string_algorithms/task2420-palindrome-queries/data/out-1.txt'

%%%% begin
7 5
aybabtu
2 3 5
1 3 x
2 3 5
1 5 x
2 3 5
%%%%
YES
NO
YES
%%%% end
*/

//
// utils
//

fn read_tokens<F: FromStr>() -> io::Result<Vec<F>>
where
    <F as FromStr>::Err: Debug,
{
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let mut result: Vec<F> = Vec::new();
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
