// WIP

// https://atcoder.jp/contests/abc300/tasks/abc300_d

fn main() {
    // n ~ 10^12
    let n: usize = read_tokens()[0];

    let k = 1000000; // k^3 ~ n
    let primes: Vec<usize> = prime_sieve(k)
        .iter()
        .enumerate()
        .filter(|(_i, &p)| p)
        .map(|(i, _p)| i)
        .collect();

    let f = |a: usize, b: usize, c: usize| -> usize { a * a * b * c * c };

    let mut res: Vec<usize> = vec![];

    let l = primes.len();
    for i0 in 0..l {
        let a = primes[i0];
        if f(a, a + 1, a + 2) > n {
            break;
        }
        for i1 in (i0 + 1)..l {
            let b = primes[i1];
            if f(a, b, b + 1) > n {
                break;
            }
            for i2 in (i1 + 1)..l {
                let c = primes[i2];
                if f(a, b, c) > n {
                    break;
                }
                res.push(f(a, b, c));
            }
        }
    }

    res.sort();
    res.dedup();
    println!("{}", res.len());
}

fn prime_sieve(n: usize) -> Vec<bool> {
    let mut v = vec![true; n + 1];
    v[0] = false;
    v[1] = false;
    for x in 2.. {
        if x * x > n {
            break;
        }
        if !v[x] {
            continue;
        }
        for y in (x * x..=n).step_by(x) {
            v[y] = false;
        }
    }
    v
}

/*
python misc/run.py atcoder/abc300/d/main.rs

%%%% begin
1000
%%%%
3
%%%% end

%%%% begin
1000000000000
%%%%
2817785
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
