// AC

// https://atcoder.jp/contests/abc294/tasks/abc294_e

fn main() {
    let (l, n1, n2) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1], v[2])
    };
    let ls: Vec<Vec<Vec<usize>>> = vec![
        (0..n1).map(|_| read_tokens()).collect(),
        (0..n2).map(|_| read_tokens()).collect(),
    ];

    //
    // solve by sweeping
    //

    // collect (boundary index, value, 0 or 1)
    let mut events: Vec<(usize, usize, usize)> = vec![];
    for (k, pairs) in ls.iter().enumerate() {
        let mut acc = 0;
        for pair in pairs {
            events.push((acc, pair[0], k));
            acc += pair[1];
        }
    }
    events.push((l, 0, 0));
    events.push((l, 0, 1));

    // sort
    events.sort();
    // dbg!(&events);

    // sweep
    let mut result = 0;
    let mut i_last = 0;
    let mut current = [0, 0];
    for (i, v, k) in events {
        if current[0] == current[1] {
            result += i - i_last;
        }
        current[k] = v;
        i_last = i;
    }

    println!("{}", result);
}

/*
python misc/run.py atcoder/abc294/e/main.rs

%%%% begin
8 4 3
1 2
3 2
2 3
3 1
1 4
2 1
3 3
%%%%
4
%%%% end

%%%% begin
10000000000 1 1
1 10000000000
1 10000000000
%%%%
10000000000
%%%% end

%%%% begin
1000 4 7
19 79
33 463
19 178
33 280
19 255
33 92
34 25
19 96
12 11
19 490
33 31
%%%%
380
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
