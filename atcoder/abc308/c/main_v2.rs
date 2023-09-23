// AC

// https://atcoder.jp/contests/abc308/tasks/abc308_c

fn main() {
    let n: usize = read_tokens()[0];
    let ls: Vec<Vec<usize>> = (0..n).map(|_| read_tokens()).collect();
    let mut result: Vec<usize> = (0..n).collect();
    result.sort_by(|&i, &j| {
        (ls[i][0] * (ls[j][0] + ls[j][1]))
            .cmp(&(ls[j][0] * (ls[i][0] + ls[i][1])))
            .reverse()
    });
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
python misc/run.py atcoder/abc308/c/main_v2.rs

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
