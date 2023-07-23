// AC

// https://atcoder.jp/contests/abc305/tasks/abc305_f

fn main() {
    // n \in [2, 100]
    let v: Vec<usize> = read_tokens();
    let (n, _m) = (v[0], v[1]);

    //
    // dfs while querying adjacency and ensures each edge taken at most twice
    //
    //

    fn read_adj() -> Vec<usize> {
        let mut v: Vec<usize> = read_tokens();
        v.remove(0);
        v
    }

    fn visit_adj(v: usize) {
        println!("{}", v);
    }

    let mut v = 1;
    let mut visited: Vec<bool> = vec![false; n + 1];
    let mut parents: Vec<usize> = vec![0; n + 1];

    for _ in 0..(2 * n) {
        visited[v] = true;

        if v == n {
            break;
        }

        let mut is_leaf = true;
        for u in read_adj() {
            if !visited[u] {
                parents[u] = v;
                v = u;
                visit_adj(v);
                is_leaf = false;
                break;
            }
        }

        // backtrack on (dfs-tree) leaf
        if is_leaf {
            v = parents[v];
            assert!(v != 0);
            visit_adj(v);
        }
    }

    assert!(v == n);
    assert!(read_tokens::<String>()[0] == "OK");
}

/*
python misc/run.py atcoder/abc305/f/main.rs

%%%% begin
4 5
2 2 3
3 1 3 4
3 1 2 4
OK
%%%%
2
3
4
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
