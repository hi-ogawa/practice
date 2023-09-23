// AC

// https://atcoder.jp/contests/abc298/tasks/abc298_f

use std::collections::HashMap;

fn main() {
    // ~ 10^5
    let n: usize = read_tokens()[0];

    // ~ 10^9
    let mut point_map: HashMap<(usize, usize), usize> = HashMap::new();
    for _ in 0..n {
        let v: Vec<usize> = read_tokens();
        point_map.insert((v[0], v[1]), v[2]);
    }

    // horizontal/veritical aggregation
    let mut x_scores: HashMap<usize, usize> = HashMap::new();
    let mut y_scores: HashMap<usize, usize> = HashMap::new();

    for (&(x, y), &p) in &point_map {
        *x_scores.entry(x).or_default() += p;
        *y_scores.entry(y).or_default() += p;
    }

    // to vec
    let x_scores_vec: Vec<(usize, usize)> = x_scores.into_iter().collect();
    let mut y_scores_vec: Vec<(usize, usize)> = y_scores.into_iter().collect();

    // order y_scores
    y_scores_vec.sort_by_key(|&(_, p)| p);
    y_scores_vec.reverse();

    // traverse
    let mut result = 0;
    for &(x, px) in &x_scores_vec {
        for &(y, py) in &y_scores_vec {
            match point_map.get(&(x, y)) {
                Some(p) => {
                    result = result.max(px + py - p);
                }
                None => {
                    result = result.max(px + py);
                    // no need to look further since y score is ordered
                    // and this ensures for/for loops at most O(point_map.len())
                    break;
                }
            }
        }
    }

    // we can always find empty row/column at least
    for &(_, px) in &x_scores_vec {
        result = result.max(px);
    }
    for &(_, py) in &y_scores_vec {
        result = result.max(py);
    }

    println!("{}", result);
}

/*
python misc/run.py atcoder/abc298/f/main.rs

%%%% begin
4
1 1 2
1 2 9
2 1 8
3 2 3
%%%%
20
%%%% end

%%%% begin
1
1 1000000000 1
%%%%
1
%%%% end

%%%% begin
15
158260522 877914575 602436426
24979445 861648772 623690081
433933447 476190629 262703497
211047202 971407775 628894325
731963982 822804784 450968417
430302156 982631932 161735902
880895728 923078537 707723857
189330739 910286918 802329211
404539679 303238506 317063340
492686568 773361868 125660016
650287940 839296263 462224593
492601449 384836991 191890310
576823355 782177068 404011431
818008580 954291757 160449218
155374934 840594328 164163676
%%%%
1510053068
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
