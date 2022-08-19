// TLE

// https://atcoder.jp/contests/abc260/tasks/abc260_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (s, t, m) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?; // s ∈ [2, 3x 10^5], t ∈ [2, 3000]
    let n = s + t;

    // adj. list from T to S
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for _ in 0..m {
        let (x, y) = read_tokens::<usize>().map(|v| (v[0] - 1, v[1] - 1))?;
        adj[y].push(x);
    }

    //
    // brute force by O(t^2 + 2 m + t m)
    //

    // sort each list ahead of time to avoid quadratic travesal
    for conn in adj.iter_mut() {
        conn.sort();
    }

    for x in s..n {
        for y in s..x {
            let zs = get_sorted_intersection(&adj[x], &adj[y]);
            if zs.len() >= 2 {
                println!("{} {} {} {}", x + 1, zs[0] + 1, y + 1, zs[1] + 1);
                return Ok(());
            }
        }
    }

    println!("-1");
    Ok(())
}

fn get_sorted_intersection(v1: &Vec<usize>, v2: &Vec<usize>) -> Vec<usize> {
    let mut result: Vec<usize> = vec![];
    let mut i1 = 0;
    let mut i2 = 0;
    while i1 < v1.len() && i2 < v2.len() {
        if v1[i1] == v2[i2] {
            result.push(v1[i1]);
            i1 += 1;
            i2 += 1;
            continue;
        }
        match v1[i1].cmp(&v2[i2]) {
            std::cmp::Ordering::Equal => {
                result.push(v1[i1]);
                i1 += 1;
                i2 += 1;
            }
            std::cmp::Ordering::Less => {
                i1 += 1;
            }
            std::cmp::Ordering::Greater => {
                i2 += 1;
            }
        }
    }
    result
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc260/f/main.rs

%%%% begin
2 3 5
1 3
1 4
1 5
2 4
2 5
%%%%
1 2 4 5
%%%% end

%%%% begin
3 2 4
1 4
1 5
2 5
3 5
%%%%
-1
%%%% end

%%%% begin
4 5 9
3 5
1 8
3 7
1 9
4 6
2 7
4 8
1 7
2 9
%%%%
1 7 2 9
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
