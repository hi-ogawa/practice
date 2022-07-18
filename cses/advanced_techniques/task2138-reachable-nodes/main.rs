// WA

use std::{fmt::Debug, io, str::FromStr};

fn main() -> io::Result<()> {
    let n_m: Vec<usize> = read_tokens()?; // ≤ 10^5
    let n = n_m[0];
    let m = n_m[1];

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let x_y: Vec<usize> = read_tokens()?;
        let x = x_y[0] - 1;
        let y = x_y[1] - 1;
        adj[x].push(y);
    }
    println!("{:?}", adj);

    // topological sort
    let mut top_order: Vec<usize> = vec![0; 0];
    {
        let mut visited = vec![false; n];
        struct Env<'a> {
            top_order: &'a mut Vec<usize>,
            visited: &'a mut Vec<bool>,
            adj: &'a Vec<Vec<usize>>,
        }
        fn dfs(x: usize, env: &mut Env) -> () {
            for &y in env.adj[x].iter() {
                if env.visited[y] {
                    continue;
                }
                env.visited[y] = true;
                dfs(y, env);
            }
            env.top_order.push(x);
        }
        for x in 0..n {
            if visited[x] {
                continue;
            }
            visited[x] = true;
            dfs(
                x,
                &mut Env {
                    top_order: &mut top_order,
                    visited: &mut visited,
                    adj: &adj,
                },
            );
        }
    }
    println!("{:?}", top_order);

    // accumulate reachability counts from the tips of DAG
    // TODO: of course, there are enormous double counts
    let mut res: Vec<usize> = vec![1; n];
    for &x in top_order.iter() {
        for &y in adj[x].iter() {
            res[x] += res[y];
        }
    }

    for (i, x) in res.iter().enumerate() {
        if i > 0 {
            print!(" ")
        }
        print!("{}", x);
    }
    Ok(())
}

/*
python misc/run.py cses/advanced_techniques/task2138-reachable-nodes/main.rs

%%%% begin
5 6
1 2
1 3
1 4
2 3
3 5
4 5
%%%%
5 3 2 2 1
%%%% end
*/

//
// io
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
