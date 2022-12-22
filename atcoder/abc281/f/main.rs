// WIP

// https://atcoder.jp/contests/abc281/tasks/abc281_f

use std::{cell::RefCell, fmt::Debug, io, rc::Rc, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^5
    let n: usize = read_tokens()?[0];
    // [0, 2^30)
    let ls: Vec<usize> = read_tokens()?;

    // binary tree (TODO: trie)
    const DEPTH: usize = 30;
    let tree = Rc::new(Node::new());

    // insert
    for &a in &ls {
        let node = tree.clone();
        for i in (0..DEPTH).rev() {
            // node = &mut node.child((a >> i) & 1);
            // node = node.child((a >> i) & 1);
            // node =
            // match node.children[(a >> i) & 1] {
            //     None
            //     _ => {}
            // }
            // let dir = (a >> i) & 1;
            // &node.children[(a >> i) & 1];
            // node = node;
        }
    }

    // solve DP
    let result = tree.solve(DEPTH);
    println!("{}", result);

    Ok(())
}

struct Node {
    children: [Option<Rc<RefCell<Node>>>; 2],
}

impl Node {
    fn new() -> Self {
        Self {
            children: [None, None],
        }
    }

    fn child(&mut self, dir: usize) -> Rc<RefCell<Node>> {
        match &self.children[dir] {
            Some(node) => node.clone(),
            None => {
                let child = Rc::new(RefCell::new(Node::new()));
                self.children[dir] = Some(child.clone());
                child
            }
        }
    }

    fn solve(&self, depth: usize) -> usize {
        if depth == 0 {
            return 0;
        }
        match &self.children {
            [Some(l), Some(r)] => {
                let l_solve = l.borrow().solve(depth - 1);
                let r_solve = r.borrow().solve(depth - 1);
                (1 << (depth - 1)) | l_solve.min(r_solve)
            }
            [Some(l), None] => l.borrow().solve(depth - 1),
            [None, Some(r)] => r.borrow().solve(depth - 1),
            _ => unreachable!(),
        }
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc281/f/main.rs

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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
