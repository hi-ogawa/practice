// WA

// https://atcoder.jp/contests/abc308/tasks/abc308_c

fn main() {
    let n: usize = read_tokens()[0];
    let mut ls: Vec<f64> = vec![];
    for _ in 0..n {
        let v: Vec<f64> = read_tokens();
        ls.push(v[0] / (v[0] + v[1]));
    }
    let mut result: Vec<usize> = (0..n).collect();
    // not sure when f64 comparison breaks
    // but it seems exact rational comparison is required (see main_v2.rs)
    result.sort_by(|&x, &y| ls[x].partial_cmp(&ls[y]).unwrap().reverse());
    println!(
        "{}",
        result
            .iter()
            .map(|i| (i + 1).to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );
}

/*
python misc/run.py atcoder/abc308/c/main.rs

%%%% begin
3
1 3
3 1
2 2
%%%%
2 3 1
%%%% end

%%%% begin
2
1 3
2 6
%%%%
1 2
%%%% end

%%%% begin
4
999999999 1000000000
333333333 999999999
1000000000 999999997
999999998 1000000000
%%%%
3 1 4 2
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
