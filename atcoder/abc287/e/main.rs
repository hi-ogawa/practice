// AC

// https://atcoder.jp/contests/abc287/tasks/abc287_e

use std::collections::HashMap;

fn main() {
    // ~ 10^5
    let n = read_tokens()[0];

    // sum_{s \in ls} |s| ~ 10^5
    let mut ls: Vec<Vec<char>> = vec![];
    for _ in 0..n {
        ls.push(read_tokens::<String>()[0].chars().collect());
    }

    // groups[l] = { indices divided by matching l-th prefix }
    let mut len_to_groups: Vec<Vec<Vec<usize>>> = vec![vec![(0..n).collect()]];

    // split each group by l-th character
    let split = |groups: &Vec<Vec<usize>>, l: usize| -> Vec<Vec<usize>> {
        let mut next_groups: Vec<Vec<usize>> = vec![];
        // TODO: can skip if |group| = 1
        for group in groups {
            let mut char_to_group: HashMap<char, Vec<usize>> = HashMap::new();
            for &i in group {
                if l < ls[i].len() {
                    char_to_group.entry(ls[i][l]).or_default().push(i);
                }
            }
            // CE https://atcoder.jp/contests/abc287/submissions/38639484
            // next_groups.extend(char_to_group.into_values());
            for (_k, v) in char_to_group {
                next_groups.push(v);
            }
        }
        next_groups
    };

    for l in 0.. {
        let next_groups = split(&len_to_groups[l], l);
        if next_groups.is_empty() {
            break;
        }
        len_to_groups.push(next_groups);
    }

    // find max "l" for each index
    let mut result = vec![0; n];
    for (l, groups) in len_to_groups.iter().enumerate() {
        for group in groups {
            if group.len() >= 2 {
                for &i in group {
                    result[i] = l;
                }
            }
        }
    }

    for l in result {
        println!("{}", l);
    }
}

/*
python misc/run.py atcoder/abc287/e/main.rs

%%%% begin
3
abc
abb
aac
%%%%
2
2
1
%%%% end

%%%% begin
11
abracadabra
bracadabra
racadabra
acadabra
cadabra
adabra
dabra
abra
bra
ra
a
%%%%
4
3
2
1
0
1
0
4
3
2
1
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
