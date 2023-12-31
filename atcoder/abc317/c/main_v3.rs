// AC

// https://atcoder.jp/contests/abc317/tasks/abc317_c

// callback-style permutation enumeration

fn main() {
    // n ~ 10
    let [n, m]: [usize; 2] = read_array();
    let mut adj: Vec<Vec<Option<usize>>> = vec![vec![None; n]; n];
    for _ in 0..m {
        let [a, b, c]: [usize; 3] = read_array();
        adj[a - 1][b - 1] = Some(c);
        adj[b - 1][a - 1] = Some(c);
    }

    let mut result = 0;
    generate_permutations(n, &mut |perm| {
        let score: usize = (0..(n - 1))
            .map(|i| adj[perm[i]][perm[i + 1]])
            .map_while(|c| c)
            .sum();
        result = result.max(score);
    });

    println!("{}", result);
}

fn generate_permutations(n: usize, callback: &mut dyn FnMut(&Vec<usize>)) {
    fn recurse(s: usize, perm: &mut Vec<usize>, callback: &mut dyn FnMut(&Vec<usize>)) {
        if s == 0 {
            callback(&perm);
            return;
        }
        for i in bit_iterator(s) {
            perm.push(i);
            recurse(s ^ (1 << i), perm, callback);
            perm.pop();
        }
    }
    recurse((1 << n) - 1, &mut vec![], callback);
}

fn bit_iterator(mut s: usize) -> impl Iterator<Item = usize> {
    std::iter::from_fn(move || {
        if s == 0 {
            None
        } else {
            let next = s.trailing_zeros() as usize;
            s = s & (s - 1);
            Some(next)
        }
    })
}

/*
python misc/run.py atcoder/abc317/c/main_v3.rs

%%%% begin
4 4
1 2 1
2 3 10
1 3 100
1 4 1000
%%%%
1110
%%%% end

%%%% begin
10 1
5 9 1
%%%%
1
%%%% end

%%%% begin
10 13
1 2 1
1 10 1
2 3 1
3 4 4
4 7 2
4 8 1
5 8 1
5 9 3
6 8 1
6 9 5
7 8 1
7 9 4
9 10 3
%%%%
20
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
