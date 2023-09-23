// AC

// https://atcoder.jp/contests/abc287/tasks/abc287_c

fn main_solve() -> bool {
    // ~ 10^5
    // 2 <= n
    let (n, m) = {
        let v = read_tokens::<usize>();
        (v[0], v[1])
    };

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let mut v = read_tokens::<usize>();
        v[0] -= 1;
        v[1] -= 1;
        adj[v[0]].push(v[1]);
        adj[v[1]].push(v[0]);
    }

    // check tree
    if m != n - 1 {
        return false;
    }

    // check degree 1 or 2
    if !adj.iter().all(|edges| edges.len() <= 2) {
        return false;
    }

    // check connected
    let mut visited = vec![false; n];
    recursive_closure!(dfs, |x: usize| -> () {
        visited[x] = true;
        for &y in &adj[x] {
            if !visited[y] {
                dfs(y);
            }
        }
    })(0);
    visited.iter().all(|&v| v)
}

fn main() {
    println!("{}", if main_solve() { "Yes" } else { "No" });
}

#[macro_export]
macro_rules! recursive_closure {
    ($ID_RECURSE:ident, |$( $ID_ARGS:ident: $TYPE_ARGS:ty ),+| -> $TYPE_RETURN:ty $EXPR_BODY:block) => {
        |$( $ID_ARGS: $TYPE_ARGS ),*| {
            use std::cell::RefCell;

            struct __Recurser<'a> {
                __run: RefCell<&'a mut dyn FnMut(&__Recurser, $( $TYPE_ARGS ),*) -> $TYPE_RETURN>,
            }

            let mut __recurser_impl = |__recurser: &__Recurser, $( $ID_ARGS: $TYPE_ARGS ),*| {
                let $ID_RECURSE = |$( $ID_ARGS: $TYPE_ARGS ),*| {
                    (unsafe { &mut *__recurser.__run.as_ptr() })(__recurser, $( $ID_ARGS ),*)
                };
                $EXPR_BODY
            };

            let __recurser = __Recurser {
                __run: RefCell::new(&mut __recurser_impl),
            };

            (unsafe { &mut *__recurser.__run.as_ptr() })(&__recurser, $( $ID_ARGS ),*)
        }
    };
}

/*
python misc/run.py atcoder/abc287/c/main.rs

%%%% begin
4 3
1 3
4 2
3 2
%%%%
Yes
%%%% end

%%%% begin
2 0
%%%%
No
%%%% end

%%%% begin
5 5
1 2
2 3
3 4
4 5
5 1
%%%%
No
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
