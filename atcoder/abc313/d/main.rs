// AC

// https://atcoder.jp/contests/abc313/tasks/abc313_d

fn main() {
    // k: odd
    // k < n
    let [n, k]: [usize; 2] = read_array();

    let mut responses: Vec<usize> = vec![];

    // first k + 1 queries to determine all k + 1 elements
    for i in 1..=k + 1 {
        responses.push(request(&format!(
            "? {} {}",
            join_iter(&mut (1..i)),
            join_iter(&mut (i + 1..=k + 1))
        )));
    }

    // collect parity comprison of A1 and Ai
    for i in k + 2..=n {
        responses.push(request(&format!("? {} {}", join_iter(&mut (2..=k)), i)));
    }

    let mut result: Vec<usize> = vec![0; n];

    // find A1 by k queries by
    // - include A1         in k     queries (odd)
    // - include A2...A_k+1 in k - 1 queries (even)
    result[0] = responses[1..=k].iter().sum::<usize>() & 1;

    // find rest by parity comparison with a1
    for i in 1..=k {
        result[i] = (result[0] + responses[0] + responses[i]) & 1;
    }
    for i in k + 1..n {
        result[i] = (result[0] + responses[k] + responses[i]) & 1;
    }

    println!("! {}", join_iter(&mut result.iter()));
}

fn request(q: &str) -> usize {
    println!("{}", q);
    read_vec()[0]
}

fn join_iter<T: ToString>(it: &mut dyn Iterator<Item = T>) -> String {
    it.map(|x| x.to_string()).collect::<Vec<_>>().join(" ")
}

/*
python misc/run.py atcoder/abc313/d/main.rs

%%%% begin
5 3
0
1
0
0
1
%%%%
?  2 3 4
? 1 3 4
? 1 2 4
? 1.2 3
? 2 3 5
! 1 0 1 1 0
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
