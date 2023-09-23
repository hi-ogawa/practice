// AC

// https://atcoder.jp/contests/abc293/tasks/abc293_d

fn main() {
    // ~ 10^5
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    // 0    1  ... n-1  (red)
    // |    |        |
    // n  n+1     2n-1  (blue)

    let mut edges: Vec<(usize, usize)> = (0..n).map(|i| (i, i + n)).collect();

    let to_edge = |index: &str, color: &str| -> usize {
        let index: usize = index.parse().unwrap();
        let color: usize = match color {
            "R" => 0,
            "B" => n,
            _ => unreachable!(),
        };
        index - 1 + color
    };

    for _ in 0..m {
        let v: Vec<String> = read_tokens();
        edges.push((to_edge(&v[0], &v[1]), to_edge(&v[2], &v[3])));
    }

    //
    // PROP.
    //   connect component is loop  \iff  all verteces have degree = 2
    //

    let k = 2 * n;
    let mut degrees: Vec<usize> = vec![0; k];
    let mut dsu = Dsu::new(k);

    for &(x, y) in &edges {
        degrees[x] += 1;
        degrees[y] += 1;
        dsu.merge(x, y);
    }

    let mut components: Vec<Vec<usize>> = vec![vec![]; k];
    for i in 0..k {
        components[dsu.find(i)].push(i);
    }
    // dbg!(&edges);
    // dbg!(&components);

    let mut result: (usize, usize) = (0, 0);
    for xs in &components {
        if xs.len() > 0 {
            if xs.iter().all(|&i| degrees[i] == 2) {
                result.0 += 1;
            } else {
                result.1 += 1;
            }
        }
    }
    println!("{} {}", result.0, result.1);
}

struct Dsu {
    parents: Vec<usize>,
}

impl Dsu {
    fn new(n: usize) -> Self {
        Self {
            parents: (0..n).collect(),
        }
    }

    fn find(&mut self, x: usize) -> usize {
        let mut p = self.parents[x];
        if p != x {
            p = self.find(p);
            self.parents[x] = p;
        }
        p
    }

    fn merge(&mut self, mut dst: usize, mut src: usize) {
        dst = self.find(dst);
        src = self.find(src);
        self.parents[src] = dst;
    }
}

/*
python misc/run.py atcoder/abc293/d/main.rs

%%%% begin
5 3
3 R 5 B
5 R 3 B
4 R 2 B
%%%%
1 2
%%%% end

%%%% begin
7 0
%%%%
0 7
%%%% end

%%%% begin
7 6
5 R 3 R
7 R 4 R
4 B 1 R
2 R 3 B
2 B 5 B
1 B 7 B
%%%%
2 1
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
