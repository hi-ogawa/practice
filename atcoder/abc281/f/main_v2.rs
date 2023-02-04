// AC

// https://atcoder.jp/contests/abc281/tasks/abc281_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^5
    let n: usize = read_tokens()?[0];
    // [0, 2^30)
    let ls: Vec<usize> = read_tokens()?;

    let mut trie = Trie::new(n);

    for &a in &ls {
        trie.insert(a);
    }

    let result = trie.solve();
    println!("{}", result);

    Ok(())
}

//
// bounded size bit trie
//

const NUM_BITS: usize = 30;

struct Node {
    to: [usize; 2],
}

struct Trie {
    nodes: Vec<Node>, // empty node at 0, root node at 1
    next_node: usize,
}

impl Node {
    fn new() -> Self {
        Self { to: [0, 0] }
    }
}

impl Trie {
    fn new(num_insert: usize) -> Self {
        let n = (num_insert + 2) * NUM_BITS;
        Self {
            next_node: 2,
            nodes: (0..n).map(|_| Node::new()).collect(),
        }
    }

    fn insert(&mut self, a: usize) {
        let mut t = 1;
        for i in (0..NUM_BITS).rev() {
            let t_next = &mut self.nodes[t].to[(a >> i) & 1];
            if *t_next == 0 {
                *t_next = self.next_node;
                self.next_node += 1;
            }
            t = *t_next;
        }
    }

    fn solve(&self) -> usize {
        self.solve_rec(1, NUM_BITS)
    }

    fn solve_rec(&self, t: usize, depth: usize) -> usize {
        if depth == 0 {
            return 0;
        }
        assert!(t != 0);
        match self.nodes[t].to {
            [0, 0] => unreachable!(),
            [l, 0] => self.solve_rec(l, depth - 1),
            [0, r] => self.solve_rec(r, depth - 1),
            [l, r] => {
                let l_solve = self.solve_rec(l, depth - 1);
                let r_solve = self.solve_rec(r, depth - 1);
                (1 << (depth - 1)) | l_solve.min(r_solve)
            }
        }
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc281/f/main_v2.rs

%%%% begin
3
12 18 11
%%%%
16
%%%% end

%%%% begin
10
0 0 0 0 0 0 0 0 0 0
%%%%
0
%%%% end

%%%% begin
5
324097321 555675086 304655177 991244276 9980291
%%%%
805306368
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
