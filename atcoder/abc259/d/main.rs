// AC

// https://atcoder.jp/contests/abc259/tasks/abc259_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // n \in [1, 3000]
    let (sx, sy, tx, ty) = read_tokens::<isize>().map(|v| (v[0], v[1], v[2], v[3]))?; // x \in [-10^9, 10^9]

    let mut circles: Vec<(isize, isize, isize)> = vec![];
    for _ in 0..n {
        circles.push(read_tokens::<isize>().map(|v| (v[0], v[1], v[2]))?);
    }

    //
    // collect circles intersecting with the s / t
    //
    let mut s_ls: Vec<usize> = vec![];
    let mut t_ls: Vec<usize> = vec![];

    for i in 0..n {
        if isect_circle_point(circles[i], (sx, sy)) {
            s_ls.push(i);
        }
        if isect_circle_point(circles[i], (tx, ty)) {
            t_ls.push(i);
        }
    }

    //
    // adjacency of circles
    //
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];

    for i in 0..n {
        for j in (i + 1)..n {
            if isect_circle_circle(circles[i], circles[j]) {
                adj[i].push(j);
                adj[j].push(i);
            }
        }
    }

    // dbg!(&s_ls);
    // dbg!(&t_ls);
    // dbg!(&adj);

    //
    // reachability from s to t
    //

    if s_ls.len() > 0 && t_ls.len() > 0 {
        // WLOG, s_ls / t_ls are connected
        let s = s_ls[0];
        let t = t_ls[0];
        for &v in &s_ls[1..] {
            adj[s].push(v);
            adj[v].push(s);
        }
        for &v in &t_ls[1..] {
            adj[t].push(v);
            adj[v].push(t);
        }

        // dfs
        let mut visited: Vec<bool> = vec![false; n];
        let mut stack: Vec<usize> = vec![];

        stack.push(s);
        visited[s] = true;

        while let Some(v) = stack.pop() {
            if v == t {
                println!("Yes");
                return Ok(());
            }
            for &u in &adj[v] {
                if visited[u] {
                    continue;
                }
                visited[u] = true;
                stack.push(u);
            }
        }
    }

    println!("No");
    Ok(())
}

fn isect_circle_point(c: (isize, isize, isize), p: (isize, isize)) -> bool {
    let (x1, y1, r) = c;
    let (x2, y2) = p;
    (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) == r * r
}

fn isect_circle_circle(c1: (isize, isize, isize), c2: (isize, isize, isize)) -> bool {
    let (x1, y1, r1) = c1;
    let (x2, y2, r2) = c2;
    let b1 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) <= (r1 + r2) * (r1 + r2);
    let b2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) >= (r2 - r1) * (r2 - r1);
    b1 && b2
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc259/d/main.rs

%%%% begin
4
0 -2 3 3
0 0 2
2 0 2
2 3 1
-3 3 3
%%%%
Yes
%%%% end

%%%% begin
3
0 1 0 3
0 0 1
0 0 2
0 0 3
%%%%
No
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
