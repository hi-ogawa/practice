// WIP

// https://atcoder.jp/contests/abc268/tasks/abc268_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^5
    let n: usize = read_tokens()?[0];
    // permutation {0, .., n-1}
    let ls: Vec<usize> = read_tokens()?;

    //
    // define
    //   f(i, x) = d(p_i, i + x)  where `d` represents "distance" in Zn
    //   g(x) = ∑_i f(i, x)
    //
    // then
    //   answer = min_x g(x)
    //
    // noting that f(i, x) is linear (+1/-1 slope) wrt `x` except two points,
    // we can incrementally compute g(x) for each x
    // by keeping track of counts of `i`s having +1/-1 slopes.
    // (though when n is odd, precisely speacking, there are two maximum points taking (n - 1) / 2)
    //

    // TOOD: might be simpler to do in f64? (to get away from slope +0)

    fn distance(mut i: usize, mut j: usize, n: usize) -> usize {
        if i > j {
            (i, j) = (j, i);
        }
        (j - i).min(i + n - j)
    }

    // TODO
    // precompute "non-linear" points of `f(i, x)` for each `i`
    //   changes(x, s0, s1) = (the number of `i`s having slope change from s0 to s1 at x)
    let mut changes: Vec<Vec<Vec<usize>>> = vec![vec![vec![0; 3]; 3]; n];

    for i in 0..n {
        // i + x
        if i <= ls[i] {
        } else {
        }
    }

    // compute intial case g(0)
    let mut g = 0;
    // TODO
    let mut slopes = [0, 0, 0]; // 0, 1, -1

    for i in 0..n {
        g += distance(i, ls[i], n);
        // if i <= ls[i]
        // -1
        // ls[i];
    }

    // compute g(x) incrementally
    let mut result = g;
    for x in 0..n {
        g += slopes[1] - slopes[2];
        for s0 in 0..3 {
            for s1 in 0..3 {
                if s0 == s1 {
                    continue;
                }
                slopes[s0] -= changes[x][s0][s1];
                slopes[s1] += changes[x][s0][s1];
            }
        }
        result = result.min(g);
    }

    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc268/e/main.rs

%%%% begin
4
1 2 0 3
%%%%
2
%%%% end

%%%% begin
3
0 1 2
%%%%
0
%%%% end

%%%% begin
10
3 9 6 1 7 2 8 0 5 4
%%%%
20
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
