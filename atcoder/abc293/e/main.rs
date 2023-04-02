// AC

// https://atcoder.jp/contests/abc293/tasks/abc293_e

fn main() {
    // a, m ~ 10^9
    // x ~ 10^12
    let (a, x, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1], v[2])
    };
    let a = a % m;

    let add = |x: usize, y: usize| -> usize { (x + y) % m };

    let mul = |x: usize, y: usize| -> usize { (x * y) % m };

    // O(n)
    let pow = |x: usize, n: usize| -> usize {
        let mut z = 1;
        for _ in 0..n {
            z = mul(z, x);
        }
        z
    };

    // O(n)
    let f = |a: usize, n: usize| -> usize {
        let mut x = 1;
        let mut y = 0;
        for _ in 0..n {
            y = add(x, y);
            x = mul(x, a);
        }
        y
    };

    //
    // PROP.
    //   given
    //     x = q y + r
    //   then
    //     f(a, x) = f(a^y, q) * f(a, y) + a^q^y * f(a, r)
    //
    let y: usize = 1000_000;
    let q = x / y;
    let r = x % y;
    let result = add(
        mul(f(pow(a, y), q), f(a, y)),
        mul(pow(pow(a, q), y), f(a, r)),
    );
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc293/e/main.rs

%%%% begin
3 4 7
%%%%
5
%%%% end

%%%% begin
8 10 9
%%%%
0
%%%% end

%%%% begin
1000000000 1000000000000 998244353
%%%%
919667211
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
