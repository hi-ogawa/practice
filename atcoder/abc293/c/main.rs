// WIP

// https://atcoder.jp/contests/abc293/tasks/abc293_c

fn main() {
    // ~ 10
    let (h, w) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };
    let mut board: Vec<Vec<usize>> = vec![];
    for _ in 0..h {
        board.push(read_tokens());
    }
    dbg!(&board);

    // dp(i, j) = { valid paths from (0, 0) to (i, j) }
    // let mut dp: Vec<Vec<Vec<
}

/*
python misc/run.py atcoder/abc293/c/main.rs

%%%% begin
3 3
3 2 2
2 1 3
1 5 4
%%%%
3
%%%% end

%%%% begin
10 10
1 2 3 4 5 6 7 8 9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
31 32 33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48 49 50
51 52 53 54 55 56 57 58 59 60
61 62 63 64 65 66 67 68 69 70
71 72 73 74 75 76 77 78 79 80
81 82 83 84 85 86 87 88 89 90
91 92 93 94 95 96 97 98 99 100
%%%%
48620
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
