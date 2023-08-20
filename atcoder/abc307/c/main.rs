// WIP

// https://atcoder.jp/contests/abc307/tasks/abc307_c

fn main() {
    fn read_board() -> (Vec<Vec<bool>>, usize, usize) {
        // h, w <= 10
        let v: Vec<usize> = read_tokens();
        let (h, w) = (v[0], v[1]);
        let mut board: Vec<Vec<bool>> = vec![];
        for _ in 0..h {
            board.push(
                read_tokens::<String>()[0]
                    .chars()
                    .map(|c| c == '#')
                    .collect(),
            )
        }
        (board, h, w)
    }

    let board1 = read_board().0;
    let board2 = read_board().0;
    let (board3, h, w) = read_board();

    // bruteforce

    fn get_board_value(board: &Vec<Vec<bool>>, (i, j): (usize, usize), (di, dj): (isize, isize)) -> bool {
        let i = i as isize + di;
        let j = j as isize + dj;
        let h = board.len() as isize;
        let w = board[0].len() as isize;
        if 0 <= i && i < h && 0 <= j && j < w {
            board[i as usize][j as usize]
        } else {
            false
        }
    }

    let check_match = |(i1, j1, i2, j2): (isize, isize, isize, isize)| -> bool {
        // TODO: cannot cut arbitrary... (it has to include both board1 and board2)
        for i in 0..h {
            for j in 0..w {
                let a = get_board_value(&board1, (i, j), (i1, j1));
                let b = get_board_value(&board2, (i, j), (i2, j2));
                let c = board3[i][j];
                if a | b != c {
                    return false;
                }
            }
        }
        true
    };

    for i1 in -10..=10 {
        for j1 in -10..=10 {
            for i2 in -10..=10 {
                for j2 in -10..=10 {
                    if check_match((i1, j1, i2, j2)) {
                        println!("Yes");
                        return;
                    }
                }
            }
        }
    }

    println!("No");
}

/*
python misc/run.py atcoder/abc307/c/main.rs

%%%% begin
3 5
#.#..
.....
.#...
2 2
#.
.#
5 3
...
#.#
.#.
.#.
...
%%%%
Yes
%%%% end

%%%% begin
2 2
#.
.#
2 2
#.
.#
2 2
##
##
%%%%
No
%%%% end

%%%% begin
1 1
#
1 2
##
1 1
#
%%%%
No
%%%% end

%%%% begin
3 3
###
...
...
3 3
#..
#..
#..
3 3
..#
..#
###
%%%%
Yes
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
