// AC

/*
$ time ./build/main < atcoder/abc262/d/data/in.txt
794961497

real    0m1,412s
user    0m1,135s
sys     0m0,219s
 */

use std::{
    fmt::Debug,
    io,
    ops::{Index, IndexMut},
    str::FromStr,
};

const MODULO: usize = 998244353;

struct MultiVec {
    sizes: [usize; 4],
    data: Vec<usize>,
}

impl MultiVec {
    fn new(sizes: [usize; 4]) -> Self {
        let n: usize = sizes.iter().product();
        MultiVec {
            sizes,
            data: vec![0; n],
        }
    }

    fn index_impl(&self, i: [usize; 4]) -> usize {
        let [i0, i1, i2, i3] = i;
        let [_, s1, s2, s3] = self.sizes;
        ((i0 * s1 + i1) * s2 + i2) * s3 + i3
    }
}

// not used
impl Index<[usize; 4]> for MultiVec {
    type Output = usize;
    fn index(&self, i: [usize; 4]) -> &usize {
        let j = self.index_impl(i);
        &self.data[j]
    }
}

impl IndexMut<[usize; 4]> for MultiVec {
    fn index_mut(&mut self, i: [usize; 4]) -> &mut usize {
        let j = self.index_impl(i);
        &mut self.data[j]
    }
}

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // [1, 100]
    let ls: Vec<usize> = read_tokens()?; // [1, 10^9]

    // dp[i][j][k][l] = #{ S | S ⊆ {a1, ..., ai} and ∑S % l = j and |S| = k }
    let mut dp = MultiVec::new([n + 1, n, n + 1, n + 1]);
    for l in 1..=n {
        dp[[0, 0, 0, l]] = 1;
    }
    for i in 0..n {
        for j in 0..n {
            for k in 0..n {
                for l in 1..=n {
                    // dp[[i + 1, j, k, l]] += dp[[i, j, k, l]];
                    // dp[[i + 1, j, k, l]] %= MODULO;
                    // dp[[i + 1, (j + ls[i]) % l, k + 1, l]] += dp[[i, j, k, l]];
                    // dp[[i + 1, (j + ls[i]) % l, k + 1, l]] %= MODULO;

                    // precompute index
                    let from = dp.index_impl([i, j, k, l]);
                    let to1 = dp.index_impl([i + 1, j, k, l]);
                    let to2 = dp.index_impl([i + 1, (j + ls[i]) % l, k + 1, l]);
                    dp.data[to1] = (dp.data[to1] + dp.data[from]) % MODULO;
                    dp.data[to2] = (dp.data[to2] + dp.data[from]) % MODULO;
                }
            }
        }
    }

    let result = (1..=n).map(|l| dp[[n, 0, l, l]]).sum::<usize>() % MODULO;
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc262/d/main_v2.rs

%%%% begin
3
2 6 2
%%%%
6
%%%% end

%%%% begin
5
5 5 5 5 5
%%%%
31
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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
