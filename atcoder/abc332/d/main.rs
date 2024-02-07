// WIP

// https://atcoder.jp/contests/abc332/tasks/abc332_d

use std::collections::{BTreeMap, VecDeque};

fn main() {
    // ~ 5
    let [h, w]: [usize; 2] = read_array();
    let grid1: Vec<Vec<usize>> = (0..h).map(|_| read_vec()).collect();
    let grid2: Vec<Vec<usize>> = (0..h).map(|_| read_vec()).collect();

    // row operations and col operations are independent.
    // thus #(possible configurations) = h! w!

    // precompute neighboring-swap distance
    let perm_h_distance = get_perm_swap_distance(h);
    let perm_w_distance = get_perm_swap_distance(w);

    // brute-force permutations
    let mut result = usize::MAX;
    let mut perm_h: Vec<usize> = (0..h).collect();
    loop {
        let mut perm_w: Vec<usize> = (0..w).collect();
        loop {
            let mut ok = true;
            for i in 0..h {
                for j in 0..w {
                    if grid1[perm_h[i]][perm_w[j]] != grid2[i][j] {
                        ok = false;
                    }
                }
            }
            if ok {
                result = result.min(perm_h_distance[&perm_h] + perm_w_distance[&perm_w]);
            }

            if !next_permutation(&mut perm_w) {
                break;
            }
        }
        if !next_permutation(&mut perm_h) {
            break;
        }
    }

    if result == usize::MAX {
        println!("-1");
    } else {
        println!("{}", result);
    }
}

fn get_perm_swap_distance(n: usize) -> BTreeMap<Vec<usize>, usize> {
    let mut distance: BTreeMap<Vec<usize>, usize> = BTreeMap::new();
    let mut queue: VecDeque<Vec<usize>> = VecDeque::new();
    let root: Vec<usize> = (0..n).collect();
    distance.insert(root.clone(), 0);
    queue.push_back(root.clone());
    while let Some(v) = queue.pop_front() {
        for i in 0..(n - 1) {
            let mut u = v.clone();
            u.swap(i, i + 1);
            if distance.get(&u).is_none() {
                distance.insert(u.clone(), distance[&v] + 1);
                queue.push_back(u.clone());
            }
        }
    }
    distance
}

/*
python misc/run.py atcoder/abc332/d/main.rs

%%%% begin
4 5
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
1 3 2 5 4
11 13 12 15 14
6 8 7 10 9
16 18 17 20 19
%%%%
3
%%%% end

%%%% begin
2 2
1 1
1 1
1 1
1 1000000000
%%%%
-1
%%%% end

%%%% begin
3 3
8 1 6
3 5 7
4 9 2
8 1 6
3 5 7
4 9 2
%%%%
0
%%%% end

%%%% begin
5 5
710511029 136397527 763027379 644706927 447672230
979861204 57882493 442931589 951053644 152300688
43971370 126515475 962139996 541282303 834022578
312523039 506696497 664922712 414720753 304621362
325269832 191410838 286751784 732741849 806602693
806602693 732741849 286751784 191410838 325269832
304621362 414720753 664922712 506696497 312523039
834022578 541282303 962139996 126515475 43971370
152300688 951053644 442931589 57882493 979861204
447672230 644706927 763027379 136397527 710511029
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

//
// https://en.cppreference.com/w/cpp/algorithm/next_permutation
//

fn next_permutation(v: &mut Vec<usize>) -> bool {
    //
    // 1. find suffix s.t.
    //
    // ... x  <  y1 >= .. >= yk >= .. >= yn
    //
    // where k = max { i | y_i > x }
    //
    // 2. by swapping (x, yk),
    //
    // ... yk <= y1 >= .. >= x  >= .. >= yn
    //
    // 3. by reversing (y1, ..., yn)
    //
    // ... yk <= yn <= .. <= x  <= .. <= r1
    //

    // 1.0. find descending suffix
    let n = v.len();
    let i = (1..n).rev().find(|&i| v[i - 1] < v[i]);
    if i.is_none() {
        return false;
    }

    // 1.1. find y_k > x
    let i = i.unwrap();
    let j = i + v[i..n].partition_point(|&y| y > v[i - 1]) - 1;

    // 2.
    v.swap(i - 1, j);

    // 3.
    for d in 0..((n - i) / 2) {
        v.swap(i + d, n - 1 - d);
    }
    true
}
