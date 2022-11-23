// AC

// https://atcoder.jp/contests/abc276/tasks/abc276_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // h x w ~ 10^6
    let (h, w) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let mut grid: Vec<Vec<char>> = vec![];
    for _ in 0..h {
        grid.push(read_tokens::<String>()?[0].chars().collect());
    }

    // compute connected components while hypothetically assuming "S" is "#"
    let idx = |i: usize, j: usize| -> usize { i * w + j };
    let mut dsu = Dsu::new(idx(h, 0));
    let mut start = (h, w);

    for i in 0..h {
        for j in 0..w {
            match grid[i][j] {
                '.' => {
                    if i + 1 < h && grid[i + 1][j] == '.' {
                        dsu.merge(idx(i, j), idx(i + 1, j));
                    }
                    if j + 1 < w && grid[i][j + 1] == '.' {
                        dsu.merge(idx(i, j), idx(i, j + 1));
                    }
                }
                'S' => {
                    start = (i, j);
                }
                '#' => {}
                _ => unreachable!(),
            }
        }
    }

    // "S" can loop if if there are some "S"'s neighbors connected
    let mut neighbors: Vec<usize> = vec![];
    let (i, j) = start;
    if 0 < i {
        neighbors.push(dsu.find(idx(i - 1, j)));
    }
    if i + 1 < h {
        neighbors.push(dsu.find(idx(i + 1, j)));
    }
    if 0 < j {
        neighbors.push(dsu.find(idx(i, j - 1)));
    }
    if j + 1 < w {
        neighbors.push(dsu.find(idx(i, j + 1)));
    }
    let mut neighbors_dedup = neighbors.clone();
    neighbors_dedup.sort();
    neighbors_dedup.dedup();

    // check duplicate by size
    if neighbors_dedup.len() < neighbors.len() {
        println!("Yes");
    } else {
        println!("No");
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc276/e/main.rs

%%%% begin
4 4
....
#.#.
.S..
.##.
%%%%
Yes
%%%% end

%%%% begin
2 2
S.
.#
%%%%
No
%%%% end

%%%% begin
5 7
.#...#.
..#.#..
...S...
..#.#..
.#...#.
%%%%
No
%%%% end
*/

//
// Dsu
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
