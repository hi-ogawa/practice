// WA

use std::{fmt::Debug, io, str::FromStr};

const M: usize = 1_000_000_000 + 7;

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];

    // x = ∏_i p_i ^ e_i
    let factors: Vec<(usize, usize)> = (0..n)
        .map(|_| read_tokens::<usize>().map(|v| (v[0], v[1])).unwrap())
        .collect();

    //
    // divisor count
    //
    // f(x) = ∑_i (e_i + 1)
    let f: usize = mod_prod(factors.iter().map(|(_, e)| e + 1), M);

    //
    // divisor sum
    //
    // g(x) = ∏_i (p_i ^ (e_i + 1) - 1) / (p_i - 1)
    let g: usize = mod_prod(
        factors
            .iter()
            .map(|&(p, e)| (mod_pow(p, e + 1, M) - 1) * mod_inv(p - 1, M) % M),
        M,
    );

    //
    // divisor product
    //
    // h(x) = ∏_i p_i ^ ((1 + ... + e_i) f(x / p_i ^ e_i))
    //      = ∏_i p_i ^ ((e_i (e_i + 1) / 2) ∑_(j ≠ i) (e_j + 1))
    //      = ∏_i p_i ^ ((e_i / 2) f(x))
    //      = (∏_i p_i ^ (e_i / 2)) ^ f(x)   // TODO: cannot distribute because the inner term is not necessarily quadratic residue??

    // use Lagrange's solution for the special case of m = 3 (mod 4) (TODO: prove https://en.wikipedia.org/wiki/Quadratic_residue#Prime_or_prime_power_modulus)
    fn mod_sqrt(x: usize) -> usize {
        mod_pow(x, (M + 1) / 4, M)
    }
    let y = mod_prod(factors.iter().map(|&(p, e)| mod_pow(mod_sqrt(p), e, M)), M);
    let fx_m = mod_prod(factors.iter().map(|(_, e)| e + 1), M - 1); // TODO: sketchy
    let h = mod_pow(y, fx_m, M);

    println!("{} {} {}", f, g, h);
    Ok(())
}

fn mod_prod<I: Iterator<Item = usize>>(iter: I, m: usize) -> usize {
    iter.fold(1, |acc, x| acc * x % m)
}

fn mod_inv(x: usize, m: usize) -> usize {
    mod_pow(x, m - 2, m)
}

fn mod_pow(mut x: usize, mut e: usize, m: usize) -> usize {
    let mut z = 1;
    while e > 0 {
        if e & 1 > 0 {
            z = z * x % m;
        }
        x = x * x % m;
        e >>= 1;
    }
    z
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py cses/mathematics/task2182-divisor-analysis/main.rs

%%%% begin
2
2 2
3 1
%%%%
6 28 1728
%%%% end
*/

//
// utils
//

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
