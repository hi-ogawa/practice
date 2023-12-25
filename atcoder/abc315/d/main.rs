// AC

// https://atcoder.jp/contests/abc315/tasks/abc315_d

use std::collections::BTreeMap;

fn main() {
    // ~ 2000
    let [h, w]: [usize; 2] = read_array();
    let board: Vec<Vec<char>> = (0..h)
        .map(|_| read_vec::<String>()[0].chars().collect())
        .collect();

    // track multiset for each row and column
    let mut rows: Vec<BTreeMap<char, usize>> = vec![BTreeMap::new(); h];
    let mut cols: Vec<BTreeMap<char, usize>> = vec![BTreeMap::new(); w];
    for i in 0..h {
        for j in 0..w {
            let c = board[i][j];
            *rows[i].entry(c).or_default() += 1;
            *cols[j].entry(c).or_default() += 1;
        }
    }

    loop {
        // loop at most h + w

        let rows_remove: Vec<usize> = (0..h)
            .filter(|&i| rows[i].len() == 1 && rows[i].values().next().unwrap() >= &2)
            .collect();
        let cols_remove: Vec<usize> = (0..w)
            .filter(|&i| cols[i].len() == 1 && cols[i].values().next().unwrap() >= &2)
            .collect();
        // dbg!(&rows, &cols, &rows_remove, &cols_remove);

        if rows_remove.len() == 0 && cols_remove.len() == 0 {
            break;
        }

        for &i in &rows_remove {
            for &c in rows[i].keys() {
                for j in 0..w {
                    // loop at most h x w times
                    if cols[j].get(&c).is_none() {
                        continue;
                    }
                    let k = cols[j].entry(c).or_default();
                    assert!(*k > 0);
                    *k -= 1;
                    if *k == 0 {
                        cols[j].remove(&c);
                    }
                }
            }
            rows[i].clear();
        }

        for &j in &cols_remove {
            for &c in cols[j].keys() {
                for i in 0..h {
                    if rows[i].get(&c).is_none() {
                        continue;
                    }
                    let k = rows[i].entry(c).or_default();
                    assert!(*k > 0);
                    *k -= 1;
                    if *k == 0 {
                        rows[i].remove(&c);
                    }
                }
            }
            cols[j].clear();
        }
    }

    let result = rows
        .iter()
        .map(|row| row.values().sum::<usize>())
        .sum::<usize>();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc315/d/main.rs

%%%% begin
4 3
aaa
aaa
abc
abd
%%%%
2
%%%% end

%%%% begin
2 5
aaaaa
abcde
%%%%
4
%%%% end

%%%% begin
3 3
ooo
ooo
ooo
%%%%
0
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
