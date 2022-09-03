// AC

// https://atcoder.jp/contests/abc258/tasks/abc258_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, q, x): (usize, _, _) = read_tokens().map(|v| (v[0], v[1], v[2]))?; // n, q ~ 10^5, x ~ 10^9
    let ws: Vec<usize> = read_tokens()?; // w ~ 10^9

    let mut cumsum: Vec<usize> = vec![0; n + 1];
    for i in 0..n {
        cumsum[i + 1] = cumsum[i] + ws[i];
    }

    //
    // ls[x] = (the number of potates taken when start packing from x)
    //

    let bin_search_evaluate = |i: usize, count: usize| -> usize {
        let mut result = cumsum[n] * (count / n);
        let j = i + (count % n);
        if j <= n {
            result += cumsum[j] - cumsum[i]
        } else {
            result += (cumsum[n] - cumsum[i]) + cumsum[j % n]
        };
        return result;
    };

    let bin_search = |i: usize| -> usize {
        // (c0, c1]
        let mut c0 = 0;
        let mut c1 = x;
        while c0 + 1 < c1 {
            let c = (c0 + c1 + 1) / 2;
            if bin_search_evaluate(i, c) < x {
                c0 = c;
            } else {
                c1 = c;
            }
        }
        c1
    };

    let ls: Vec<usize> = (0..n).map(|i| bin_search(i)).collect();

    //
    // binary lifting
    //
    let b_lim = 50; // 2 ^ 50 > k
    let mut table: Vec<Vec<usize>> = vec![vec![0; n]; b_lim];

    table[0] = ls.iter().enumerate().map(|(i, c)| (i + c) % n).collect(); // table[0][x] = (next potato after finishing packing from x)
    for b in 1..b_lim {
        for i in 0..n {
            table[b][i] = table[b - 1][table[b - 1][i]];
        }
    }

    // dbg!(n, x);
    // dbg!(&ls);
    // dbg!(&table[0]);

    let lift = |mut i: usize, mut e: usize| -> usize {
        let mut b = 0;
        while e > 0 {
            if e & 1 > 0 {
                i = table[b][i];
            }
            e >>= 1;
            b += 1;
        }
        i
    };

    //
    // answer queries
    //

    // k ~ 10^12
    let answer_query = |k: usize| -> usize { ls[lift(0, k - 1)] };

    for _ in 0..q {
        let k: usize = read_tokens()?[0];
        let result = answer_query(k);
        println!("{}", result);
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc258/e/main.rs

%%%% begin
3 2 5
3 4 1
1
2
%%%%
2
3
%%%% end

%%%% begin
10 5 20
5 8 5 9 8 7 4 4 8 2
1
1000
1000000
1000000000
1000000000000
%%%%
4
5
5
5
5
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
