// AC

// https://atcoder.jp/contests/abc332/tasks/abc332_d

use std::collections::{BTreeMap, VecDeque};

fn main() {
    // ~ 5
    let [h, w]: [usize; 2] = read_array();
    let grid1: Vec<Vec<usize>> = (0..h).map(|_| read_vec()).collect();
    let grid2: Vec<Vec<usize>> = (0..h).map(|_| read_vec()).collect();

    // row operations and column operations are independent.
    // thus #(possible configurations) = h! w!

    // BFS to get distance
    //   O(n!^2 n n^2) ~ 10^7
    let mut distance: BTreeMap<Vec<Vec<usize>>, usize> = BTreeMap::new();
    let mut queue: VecDeque<Vec<Vec<usize>>> = VecDeque::new();
    distance.insert(grid1.clone(), 0);
    queue.push_back(grid1.clone());
    while let Some(v) = queue.pop_front() {
        if v == grid2 {
            println!("{}", distance[&v]);
            return;
        }
        for (i1, i2, j1, j2) in (0..(h - 1))
            .map(|i| (i, i + 1, 0, 0))
            .chain((0..(w - 1)).map(|j| (0, 0, j, j + 1)))
        {
            let mut u = v.clone();
            u.swap(i1, i2);
            for row in &mut u {
                row.swap(j1, j2);
            }
            if distance.get(&u).is_none() {
                distance.insert(u.clone(), distance[&v] + 1);
                queue.push_back(u.clone());
            }
        }
    }
    println!("-1");
}

/*
python misc/run.py atcoder/abc332/d/main_v2.rs

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
