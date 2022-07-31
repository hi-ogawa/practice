// WIP

// combine v2 and v3 optimizations

use std::{fmt::Debug, io, str::FromStr};

const BASE: usize = 17;
const MODULO: usize = 7 + 1e9 as usize;

static mut BASE_POWERS: Vec<usize> = Vec::new();

fn precompute_base_powers() -> () {
    unsafe {
        let n = 2 * 100_000;
        BASE_POWERS = vec![0; n + 1];
        BASE_POWERS[0] = 1;
        for i in 0..n {
            BASE_POWERS[i + 1] = BASE_POWERS[i] * BASE % MODULO;
        }
    }
}

#[derive(Debug)]
struct SegmentTree {
    n: usize,
    data: Vec<(usize, usize, usize)>, // (hash left-to-right, hash right-to-left, length)
}

fn multiply(l: (usize, usize, usize), r: (usize, usize, usize)) -> (usize, usize, usize) {
    let c0 = unsafe { BASE_POWERS[l.2] };
    let c1 = unsafe { BASE_POWERS[r.2] };
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
        let mut l = self.n + ql;
        let mut r = self.n + qr;
        let mut result_l = (0, 0, 0);
        let mut result_r = (0, 0, 0);
        while l < r {
            if l & 1 > 0 {
                result_l = multiply(result_l, self.data[l]);
                l += 1;
            }
            if r & 1 > 0 {
                r -= 1;
                result_r = multiply(self.data[r], result_r);
            }
            l /= 2;
            r /= 2;
        }
        multiply(result_l, result_r)
    }
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
    precompute_base_powers();
    main_case()
}

/*
python misc/run.py cses/string_algorithms/task2420-palindrome-queries/main_v4.rs
python misc/run.py cses/string_algorithms/task2420-palindrome-queries/main_v4.rs --check --test 'file:cses/string_algorithms/task2420-palindrome-queries/data/in-1.txt:cses/string_algorithms/task2420-palindrome-queries/data/out-1.txt'

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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
