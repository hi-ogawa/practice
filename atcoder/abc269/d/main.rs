// AC

// https://atcoder.jp/contests/abc269/tasks/abc269_d

use std::{collections::HashMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];

    // coordinates to node index
    let mut nodes: HashMap<(isize, isize), usize> = HashMap::new();
    for i in 0..n {
        let v: Vec<isize> = read_tokens()?;
        nodes.insert((v[0], v[1]), i);
    }

    // merge by edges
    let mut dsu = Dsu::new(n);

    for (&(x, y), &i) in &nodes {
        for (dx, dy) in &[(1, 0), (0, 1), (-1, 0), (0, -1), (1, 1), (-1, -1)] {
            if let Some(&j) = nodes.get(&(x + dx, y + dy)) {
                dsu.merge(i, j);
            }
        }
    }

    // count component
    let result = (0..n).filter(|&i| dsu.parents[i] == i).count();
    println!("{}", result);

    Ok(())
}

//
// Dsu
//

struct Dsu {
    pub parents: Vec<usize>,
}

impl Dsu {
    fn new(n: usize) -> Self {
        Self {
            parents: (0..n).collect(),
        }
    }

    fn find(&mut self, i: usize) -> usize {
        let mut p = self.parents[i];
        if p != i {
            p = self.find(p);
            self.parents[i] = p;
        }
        p
    }

    fn merge(&mut self, src: usize, dest: usize) {
        let src = self.find(src);
        let dest = self.find(dest);
        self.parents[src] = dest;
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc269/d/main.rs

%%%% begin
6
-1 -1
0 1
0 2
1 0
1 2
2 0
%%%%
3
%%%% end

%%%% begin
4
5 0
4 1
-3 -4
-2 -5
%%%%
4
%%%% end

%%%% begin
5
2 1
2 -1
1 0
3 1
1 -1
%%%%
1
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
