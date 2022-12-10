// WA

// https://atcoder.jp/contests/abc279/tasks/abc279_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^5
    let (n, q) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // encode DSU vertices as follows
    // 1, ..., n        n + 1, .., n + q      n + q + 1, ..., n + q + n
    // ^^^^^^^^^        ^^^^^^^^^^^^^^^^      ^^^^^^^^^^^^^^^^^^^^^^^^^
    // initial balls    new balls             boxes
    let mut dsu = Dsu::new(2 * n + q + 1);

    let to_box = |x: usize| -> usize { x + n + q };
    let from_box = |x: usize| -> usize { x - n - q };

    for x in 1..=n {
        dsu.merge(to_box(x), x);
    }

    let mut k = n;
    for _ in 0..q {
        let query = read_tokens::<String>()?;
        match query[0].as_str() {
            "1" => {
                let x = to_box(query[1].parse::<usize>().unwrap());
                let y = to_box(query[2].parse::<usize>().unwrap());

                // compress path to re-associate all X's children
                // TODO: not correct. path compression re-associates parents...
                dsu.find(x);

                // make X root
                dsu.parents[x] = x;

                // merge Y to X
                dsu.merge(x, y);
            }
            "2" => {
                let x = to_box(query[1].parse::<usize>().unwrap());
                k += 1;
                dsu.merge(x, k);
            }
            "3" => {
                let x = query[1].parse::<usize>().unwrap();
                let result = from_box(dsu.find(x));
                println!("{}", result);
            }
            _ => unreachable!(),
        }
    }

    Ok(())
}

//
// dsu
//

struct Dsu {
    parents: Vec<usize>,
}

impl Dsu {
    fn new(n: usize) -> Self {
        Self {
            parents: (0..n).collect(),
        }
    }

    fn find(&mut self, x: usize) -> usize {
        let mut p = self.parents[x];
        if p != x {
            p = self.find(p);
            self.parents[x] = p;
        }
        p
    }

    fn merge(&mut self, mut dst: usize, mut src: usize) {
        dst = self.find(dst);
        src = self.find(src);
        self.parents[src] = dst;
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc279/f/main.rs

%%%% begin
5 10
3 5
1 1 4
2 1
2 4
3 7
1 3 1
3 4
1 1 4
3 7
3 6
%%%%
5
4
3
1
3
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
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
