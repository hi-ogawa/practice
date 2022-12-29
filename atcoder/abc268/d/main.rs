// AFTER EDITORIAL, AC

// https://atcoder.jp/contests/abc268/tasks/abc268_d

use std::{collections::BTreeSet, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 8
    // m ~ 10^5
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    const K: usize = 16;

    let mut parts: Vec<String> = vec![];
    let mut blacklist: BTreeSet<String> = BTreeSet::new();
    for _ in 0..n {
        parts.push(read_tokens::<String>()?[0].clone());
    }
    for _ in 0..m {
        blacklist.insert(read_tokens::<String>()?[0].clone());
    }

    let len_sum: usize = parts.iter().map(|s| s.len()).sum();
    let l = K - (len_sum + n - 1); // number of free underscores

    // brute-force (at most m trials by pigeon-hole principle)

    // 1. permutations(n)
    for perm in permutations((0..n).collect()) {
        // 2. combinations(l + n - 1, n - 1) which represents
        //
        //      o .. o | .. | .. o | o .. o
        //      ~~~~~~
        //      number of underscores after S0
        //
        //     where
        //      "o" x l
        //      "|" x (n - 1)
        //
        for comb in combinations((0..(l + n - 1)).collect(), n - 1) {
            let mut s: Vec<String> = vec![];
            for i in 0..n {
                if i > 0 {
                    let sep_len = 1 + comb[i - 1] - comb.get(i - 2).map_or(0, |j| j + 1);
                    s.push("_".repeat(sep_len).to_string());
                }
                s.push(parts[perm[i]].clone());
            }

            let s = s.join("");
            if s.len() < 3 {
                // happens only when n = 1 and |S0| = 1
                continue;
            }
            assert!(s.len() <= K);
            if !blacklist.contains(&s) {
                println!("{}", s);
                return Ok(());
            }
        }
    }

    println!("-1");
    Ok(())
}

fn permutations(values: Vec<usize>) -> Vec<Vec<usize>> {
    if values.len() == 0 {
        return vec![vec![]];
    }
    let mut results: Vec<Vec<usize>> = vec![];
    for i in 0..values.len() {
        for inner in permutations(
            values[..i]
                .iter()
                .copied()
                .chain(values[(i + 1)..].iter().copied())
                .collect(),
        ) {
            results.push(
                values[i..=i]
                    .iter()
                    .copied()
                    .chain(inner.into_iter())
                    .collect(),
            );
        }
    }
    results
}

fn combinations(values: Vec<usize>, k: usize) -> Vec<Vec<usize>> {
    if values.len() < k {
        return vec![];
    }
    if k == 0 {
        return vec![vec![]];
    }
    let mut results: Vec<Vec<usize>> = vec![];
    for i in 0..values.len() {
        for inner in combinations(values[(i + 1)..].iter().copied().collect(), k - 1) {
            results.push(
                values[i..=i]
                    .iter()
                    .copied()
                    .chain(inner.into_iter())
                    .collect(),
            );
        }
    }
    results
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc268/d/main.rs

%%%% begin
1 1
chokudai
chokudai
%%%%
-1
%%%% end

%%%% begin
2 2
choku
dai
chokudai
choku_dai
%%%%
choku__dai
%%%% end

%%%% begin
2 2
chokudai
atcoder
chokudai_atcoder
atcoder_chokudai
%%%%
-1
%%%% end

%%%% begin
4 4
ab
cd
ef
gh
hoge
fuga
____
_ab_cd_ef_gh_
%%%%
ab_cd_ef_gh
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
