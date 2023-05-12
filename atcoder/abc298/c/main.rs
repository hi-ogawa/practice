// AC

// https://atcoder.jp/contests/abc298/tasks/abc298_c

use std::collections::BTreeMap;

fn main() {
    // ~ 10^5
    let _n: usize = read_tokens()[0];
    let q: usize = read_tokens()[0];

    let mut box_to_card: Vec<BTreeMap<usize, usize>> = vec![BTreeMap::new(); 1000_000];
    let mut card_to_box: Vec<BTreeMap<usize, usize>> = vec![BTreeMap::new(); 1000_000];

    for _ in 0..q {
        let query: Vec<String> = read_tokens();
        match query[0].as_str() {
            "1" => {
                let i: usize = query[1].parse().unwrap();
                let j: usize = query[2].parse().unwrap();
                *card_to_box[i].entry(j).or_default() += 1;
                *box_to_card[j].entry(i).or_default() += 1;
            }
            "2" => {
                let j: usize = query[1].parse().unwrap();
                let mut result = String::new();
                for (&k, &v) in &box_to_card[j] {
                    for _ in 0..v {
                        if result.len() > 0 {
                            result += " ";
                        }
                        result += k.to_string().as_str();
                    }
                }
                println!("{}", result);
            }
            "3" => {
                let i: usize = query[1].parse().unwrap();
                let boxes = card_to_box[i].keys();
                let result = boxes.map(|i| i.to_string()).collect::<Vec<_>>().join(" ");
                println!("{}", result);
            }
            _ => unreachable!(),
        }
    }
}

/*
python misc/run.py atcoder/abc298/c/main.rs

%%%% begin
5
8
1 1 1
1 2 4
1 1 4
2 4
1 1 4
2 4
3 1
3 2
%%%%
1 2
1 1 2
1 4
4
%%%% end

%%%% begin
1
5
1 1 1
1 2 1
1 200000 1
2 1
3 200000
%%%%
1 2 200000
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
