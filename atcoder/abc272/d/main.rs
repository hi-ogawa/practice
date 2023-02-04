// AC

// https://atcoder.jp/contests/abc272/tasks/abc272_d

use std::{collections::VecDeque, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // collect (x, y) s.t. x^2 + y^2 = m (brute-force)
    let mut edges: Vec<(usize, usize)> = vec![];
    for dx in 0..n {
        for dy in 0..n {
            if dx * dx + dy * dy == m {
                edges.push((dx, dy));
            }
        }
    }

    // bfs / dijkstra
    let mut dists: Vec<Vec<isize>> = vec![vec![-1; n]; n];
    let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
    dists[0][0] = 0;
    queue.push_back((0, 0));
    while let Some((x, y)) = queue.pop_front() {
        for &(dx, dy) in &edges {
            for &(p, q) in list_moves((x, y), (dx, dy), (n, n)).iter().flatten() {
                if dists[p][q] == -1 {
                    dists[p][q] = dists[x][y] + 1;
                    queue.push_back((p, q));
                }
            }
        }
    }

    // print
    for i in 0..n {
        for j in 0..n {
            if j > 0 {
                print!(" ");
            }
            print!("{}", dists[i][j]);
        }
        println!();
    }
    Ok(())
}

fn list_moves(
    (x, y): (usize, usize),
    (dx, dy): (usize, usize),
    (w, h): (usize, usize),
) -> [Option<(usize, usize)>; 4] {
    let check_coords = |x: isize, y: isize| -> Option<(usize, usize)> {
        if 0 <= x && x < w as isize && 0 <= y && y < h as isize {
            Some((x as usize, y as usize))
        } else {
            None
        }
    };
    let x = x as isize;
    let y = y as isize;
    let dx = dx as isize;
    let dy = dy as isize;
    [
        check_coords(x + dx, y + dy),
        check_coords(x - dx, y + dy),
        check_coords(x + dx, y - dy),
        check_coords(x - dx, y - dy),
    ]
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc272/d/main.rs

%%%% begin
3 1
%%%%
0 1 2
1 2 3
2 3 4
%%%% end

%%%% begin
10 5
%%%%
0 3 2 3 2 3 4 5 4 5
3 4 1 2 3 4 3 4 5 6
2 1 4 3 2 3 4 5 4 5
3 2 3 2 3 4 3 4 5 6
2 3 2 3 4 3 4 5 4 5
3 4 3 4 3 4 5 4 5 6
4 3 4 3 4 5 4 5 6 5
5 4 5 4 5 4 5 6 5 6
4 5 4 5 4 5 6 5 6 7
5 6 5 6 5 6 5 6 7 6
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<F: FromStr>() -> io::Result<Vec<F>>
where
    <F as FromStr>::Err: Debug,
{
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let mut result: Vec<F> = Vec::new();
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
