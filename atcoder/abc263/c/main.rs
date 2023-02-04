// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?; // 1 <= n <= m <= 10

    let mut buffer = vec![0; n];
    solve((1 << m) - 1, n, 0, &mut buffer, &|v| {
        for (i, x) in v.iter().enumerate() {
            print!("{}", x + 1);
            print!("{}", if i == n - 1 { "\n" } else { " " });
        }
    });

    Ok(())
}

fn solve<F: Fn(&Vec<usize>)>(s: usize, k: usize, i: usize, result: &mut Vec<usize>, f: &F) {
    if (s.count_ones() as usize) < k {
        return;
    }
    if k == 0 {
        f(result);
        return;
    }
    for x in BitIterator(s) {
        result[i] = x;
        solve(s & !((1 << (x + 1)) - 1), k - 1, i + 1, result, f)
    }
}

// bit set iteration
struct BitIterator(usize);

impl Iterator for BitIterator {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        let x = self.0;
        if x == 0 {
            return None;
        }
        self.0 = x & (x - 1);
        Some(x.trailing_zeros() as usize)
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc263/c/main.rs

%%%% begin
2 3
%%%%
1 2
1 3
2 3
%%%% end

%%%% begin
3 5
%%%%
1 2 3
1 2 4
1 2 5
1 3 4
1 3 5
1 4 5
2 3 4
2 3 5
2 4 5
3 4 5
%%%% end
*/

//
// utils
//

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
