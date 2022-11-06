// AC

// https://atcoder.jp/contests/abc273/tasks/abc273_d

use std::{collections::HashMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // h, w ~ 10^9
    let (h, w, r_init, c_init) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2], v[3]))?;

    // n ~ 10^5
    let n: usize = read_tokens()?[0];
    // make it sparse since cannot allocate h + w vectors
    let mut holes_cols: HashMap<usize, Vec<usize>> = HashMap::new();
    let mut holes_rows: HashMap<usize, Vec<usize>> = HashMap::new();
    for _ in 0..n {
        let (r, c) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
        holes_cols.entry(r).or_default().push(c);
        holes_rows.entry(c).or_default().push(r);
    }
    for (_, holes) in &mut holes_cols {
        holes.push(0);
        holes.push(w + 1);
        holes.sort();
    }
    for (_, holes) in &mut holes_rows {
        holes.push(0);
        holes.push(h + 1);
        holes.sort();
    }
    let holes_col_default: Vec<usize> = vec![0, w + 1];
    let holes_row_default: Vec<usize> = vec![0, h + 1];

    // q ~ 10^5
    let q: usize = read_tokens()?[0];
    let mut insts: Vec<(char, usize)> = vec![];
    for _ in 0..q {
        // l ~ 10^9
        insts
            .push(read_tokens::<String>().map(|v| (v[0].parse().unwrap(), v[1].parse().unwrap()))?);
    }

    let mut r_cur = r_init;
    let mut c_cur = c_init;
    for (d, l) in insts {
        // stop before the closest hole
        let holes_col = holes_cols.get(&r_cur).unwrap_or(&holes_col_default);
        let holes_row = holes_rows.get(&c_cur).unwrap_or(&holes_row_default);
        match d {
            'R' => {
                let found = binary_search(0, holes_col.len(), |i| holes_col[i] <= c_cur) + 1;
                c_cur = (c_cur + l).min(holes_col[found] - 1);
            }
            'L' => {
                let found = binary_search(0, holes_col.len(), |i| holes_col[i] < c_cur);
                c_cur = safe_sub(c_cur, l).max(holes_col[found] + 1);
            }
            'D' => {
                let found = binary_search(0, holes_row.len(), |i| holes_row[i] <= r_cur) + 1;
                r_cur = (r_cur + l).min(holes_row[found] - 1);
            }
            'U' => {
                let found = binary_search(0, holes_row.len(), |i| holes_row[i] < r_cur);
                r_cur = safe_sub(r_cur, l).max(holes_row[found] + 1);
            }
            _ => unreachable!(),
        }
        println!("{} {}", r_cur, c_cur);
    }

    Ok(())
}

fn safe_sub(x: usize, y: usize) -> usize {
    if x <= y {
        0
    } else {
        x - y
    }
}

// find max { x | f(x) = true and x \in [x0, x1) }
fn binary_search<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    while x0 + 1 < x1 {
        let x = (x0 + x1) / 2;
        if f(x) {
            x0 = x;
        } else {
            x1 = x;
        }
    }
    return x0;
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc273/d/main.rs

%%%% begin
5 5 4 4
3
5 3
2 2
1 4
4
L 2
U 3
L 2
R 4
%%%%
4 2
3 2
3 1
3 5
%%%% end

%%%% begin
6 6 6 3
7
3 1
4 3
2 6
3 4
5 5
1 1
3 2
10
D 3
U 3
L 2
D 2
U 3
D 3
U 3
R 3
L 3
D 1
%%%%
6 3
5 3
5 1
6 1
4 1
6 1
4 1
4 2
4 1
5 1
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
