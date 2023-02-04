// AC

// https://atcoder.jp/contests/abc266/tasks/abc266_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n = read_tokens::<usize>()?[0]; // [3, 2 x 10^5]

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..n {
        let e: Vec<usize> = read_tokens()?;
        let (x, y) = (e[0] - 1, e[1] - 1);
        adj[x].push(y);
        adj[y].push(x);
    }

    //
    // dfs to find unique back edge
    //

    let mut visited = vec![false; n];
    let mut parents = vec![n; n];
    let mut back_edges: Vec<(usize, usize)> = vec![];

    let mut dfs = recursive_closure!(dfs, |x: usize| -> () {
        visited[x] = true;
        for &y in &adj[x] {
            if visited[y] {
                if y != parents[x] {
                    back_edges.push((x, y));
                }
            } else {
                parents[y] = x;
                dfs(y);
            }
        }
    });
    dfs(0);

    //
    // find loop paths
    //
    assert!(back_edges.len() == 2);
    let (c, p) = back_edges[0];
    let mut in_loop: Vec<bool> = vec![false; n]; // path([c, p])
    {
        let mut x = c;
        while x != p {
            in_loop[x] = true;
            x = parents[x];
        }
        in_loop[p] = true;
    }

    //
    // find components in the graph when all loop edges are removed
    //
    let mut visited = vec![false; n];
    let mut components = vec![0; n];
    let mut dfs = recursive_closure!(dfs, |x: usize, root: usize| -> () {
        if visited[x] {
            return;
        }
        visited[x] = true;
        components[x] = root;
        for &y in &adj[x] {
            if in_loop[x] && in_loop[y] {
                continue;
            }
            if visited[y] {
                continue;
            }
            dfs(y, root);
        }
    });
    for x in 0..n {
        dfs(x, x);
    }

    //
    // answer queries
    //
    let nq = read_tokens::<usize>()?[0];
    for _ in 0..nq {
        let e: Vec<usize> = read_tokens()?;
        // no loop in the simple path if two belong to the same component
        if components[e[0] - 1] == components[e[1] - 1] {
            println!("Yes");
        } else {
            println!("No");
        }
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc266/f/main_v2.rs

%%%% begin
5
1 2
2 3
1 3
1 4
2 5
3
1 2
1 4
1 5
%%%%
No
Yes
No
%%%% end

%%%% begin
10
3 5
5 7
4 8
2 9
1 2
7 9
1 6
4 10
2 5
2 10
10
1 8
6 9
8 10
6 8
3 10
3 9
1 10
5 8
1 10
7 8
%%%%
Yes
No
Yes
Yes
No
No
Yes
No
Yes
No
%%%% end
*/

//
// recursive mutable closure macro
//

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
