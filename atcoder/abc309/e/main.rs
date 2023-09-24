// WIP

// https://atcoder.jp/contests/abc309/tasks/abc309_e

// mis-read that parent can have multiple children...

fn main() {
    // ~ 10^5
    let [n, m]: [usize; 2] = read_array();
    let to_parent: Vec<usize> = read_vec();
    let insurances: Vec<[usize; 2]> = (0..m).map(|_| read_array()).collect();

    // re-order person by generation
    let to_generation: Vec<usize> = {
        let mut to_child: Vec<Option<usize>> = vec![None; n];
        for (i, &p) in to_parent.iter().enumerate() {
            to_child[p - 1] = Some(i + 1);
        }
        dbg!(&to_parent);
        dbg!(&to_child);
        let mut ordered = vec![0];
        for i in 0..n - 1 {
            let v = to_child[ordered[i]].unwrap();
            ordered.push(v);
        }
        let mut to_generation = vec![0; n];
        for i in 0..n {
            to_generation[ordered[i]] = i;
        }
        to_generation
    };

    // collect generation intervals
    let intervals: Vec<[usize; 2]> = insurances
        .iter()
        .map(|[x, y]| {
            let i = to_generation[x - 1];
            [i, i + y + 1]
        })
        .collect();

    // sweep as event
    #[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
    enum Event {
        Start,
        End,
        Check,
    }
    let mut events: Vec<(usize, Event)> = vec![];
    for i in 0..n {
        events.push((i, Event::Check));
    }
    for [x, y] in intervals {
        events.push((x, Event::Start));
        events.push((y, Event::End));
    }
    events.sort();

    let mut acc: usize = 0;
    let mut checks: Vec<usize> = vec![0; n];
    for (i, event) in events {
        match event {
            Event::Start => {
                acc += 1;
            }
            Event::End => {
                acc -= 1;
            }
            Event::Check => {
                checks[i] = acc;
            }
        }
    }

    let result = checks.iter().filter(|&&i| i > 0).count();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc309/e/main.rs

%%%% begin
7 3
1 2 1 3 3 3
1 1
1 2
4 3
%%%%
4
%%%% end

%%%% begin
10 10
1 1 3 1 2 3 3 5 7
2 1
5 1
4 3
6 3
2 1
7 3
9 2
1 2
6 2
8 1
%%%%
10
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
