// AC

// https://atcoder.jp/contests/abc257/tasks/abc257_d

use std::{collections::BTreeSet, fmt::Debug, io, str::FromStr};

//
// ordered f64
//

#[derive(PartialEq, PartialOrd, Clone, Copy, Debug)]
struct F64ord(f64);

impl Eq for F64ord {}

impl Ord for F64ord {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.partial_cmp(other).unwrap()
    }
}

//
// main
//

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // ~ 200
    let mut ls: Vec<Vec<f64>> = vec![];
    for _ in 0..n {
        ls.push(read_tokens()?);
    }

    // asynmetric edge weights
    let mut edges: Vec<Vec<f64>> = vec![vec![0.0; n]; n];
    for i in 0..n {
        for j in 0..n {
            edges[i][j] = ((ls[j][0] - ls[i][0]).abs() + (ls[j][1] - ls[i][1]).abs()) / ls[i][2];
        }
    }

    //
    // dijkstra where distance(i, j) = min { max { weight(e) | e \in p } | p: path from i to j }
    //
    let solve_dijkstra = |start: usize| -> Vec<f64> {
        let mut result: Vec<f64> = vec![std::f64::MAX; n];
        let mut heap: BTreeSet<(F64ord, usize)> = BTreeSet::new(); // (distance, vertex)
        heap.insert((F64ord(0.0), start));

        while heap.len() > 0 {
            let &(d, i) = heap.iter().next().unwrap();
            result[i] = d.0;
            heap.remove(&(d, i));
            for j in 0..n {
                let candidate = result[i].max(edges[i][j]);
                if candidate < result[j] {
                    heap.remove(&(F64ord(result[j]), j));
                    result[j] = candidate;
                    heap.insert((F64ord(candidate), j));
                }
            }
        }

        result
    };

    // dbg!(&edges);
    // dbg!((0..n).map(solve_dijkstra).collect::<Vec<_>>());

    // min_i max_j distance(i, j)
    let result = (0..n)
        .map(|i| {
            solve_dijkstra(i)
                .iter()
                .map(|f| f.ceil() as isize)
                .max()
                .unwrap()
        })
        .min()
        .unwrap();
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc257/d/main.rs

%%%% begin
4
-10 0 1
0 0 5
10 0 1
11 0 1
%%%%
2
%%%% end

%%%% begin
7
20 31 1
13 4 3
-10 -15 2
34 26 5
-2 39 4
0 -50 1
5 -20 2
%%%%
18
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
