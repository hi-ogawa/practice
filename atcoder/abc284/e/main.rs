// AFTER EDITORIAL, AC

// https://atcoder.jp/contests/abc284/tasks/abc284_e

fn main_case() {
    // ~ 10^6
    let (n, m) = {
        let v = read_tokens::<usize>();
        (v[0], v[1])
    };

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let e: Vec<usize> = read_tokens();
        adj[e[0] - 1].push(e[1] - 1);
        adj[e[1] - 1].push(e[0] - 1);
    }

    // Prop.
    //   correctness:
    //   - enumerate only simple path
    //   - enumerate all simple path
    //   - no double count
    //   - finite

    const LIMIT: usize = 1e6 as usize;

    fn dfs(
        v: usize,
        adj: &Vec<Vec<usize>>,
        path: &mut Vec<bool>,
        result: &mut usize,
    ) -> Option<()> {
        path[v] = true;
        *result += 1;
        if *result >= LIMIT {
            return None;
        }

        for &u in &adj[v] {
            if !path[u] {
                dfs(u, adj, path, result)?;
            }
        }

        path[v] = false;
        Some(())
    }

    let mut result = 0;
    dfs(0, &adj, &mut vec![false; n], &mut result);
    println!("{}", result);
}

fn main() {
    main_case();
}

/*
python misc/run.py atcoder/abc284/e/main.rs

%%%% begin
4 2
1 2
2 3
%%%%
3
%%%% end

%%%% begin
4 6
1 2
1 3
1 4
2 3
2 4
3 4
%%%%
16
%%%% end

%%%% begin
8 21
2 6
1 3
5 6
3 8
3 6
4 7
4 6
3 4
1 5
2 4
1 2
2 7
1 4
3 5
2 5
2 3
4 5
3 7
6 7
5 7
2 8
%%%%
2023
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<T: std::str::FromStr>() -> Vec<T>
where
    <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}
