// WIP

use std::{collections::BTreeSet, fmt::Debug, io, str::FromStr};

fn to_order(values: Vec<i64>) -> Vec<usize> {
    let n = values.len();
    let mut result: Vec<usize> = (0..n).collect();
    result.sort_by_key(|&i| -&values[i]);
    result
}

fn main() -> io::Result<()> {
    let [n, x, y, z] = read_tokens::<usize, 4>().unwrap(); // \le 100
    let a_vec: Vec<i64> = read_tokens_vec().unwrap();
    let b_vec: Vec<i64> = read_tokens_vec().unwrap();
    let c_vec: Vec<i64> = (0..n).map(|i| a_vec[i] + b_vec[i]).collect();
    let a_order = to_order(a_vec);
    let b_order = to_order(b_vec);
    let c_order = to_order(c_vec);

    let mut result: Vec<usize> = Vec::new();
    let mut done: BTreeSet<usize> = BTreeSet::new();
    {
        let mut x_acc = 0;
        for i in a_order {
            if x_acc >= x {
                break;
            }
            if !done.contains(&i) {
                result.push(i);
                done.insert(i);
                x_acc += 1;
            }
        }
    }
    {
        let mut y_acc = 0;
        for i in b_order {
            if y_acc >= y {
                break;
            }
            if !done.contains(&i) {
                result.push(i);
                done.insert(i);
                y_acc += 1;
            }
        }
    }
    {
        let mut z_acc = 0;
        for i in c_order {
            if z_acc >= z {
                break;
            }
            if !done.contains(&i) {
                result.push(i);
                done.insert(i);
                z_acc += 1;
            }
        }
    }

    result.sort();
    for i in result {
        println!("{}", i + 1);
    }
    Ok(())
}

/*
python misc/run.py atcoder/abc260/b/main.rs

%%%% begin
6 1 0 2
80 60 80 60 70 70
40 20 50 90 90 80
%%%%
1
4
5
%%%% end

%%%% begin
5 2 1 2
0 100 0 100 0
0 0 100 100 0
%%%%
1
2
3
4
5
%%%% end

%%%% begin
15 4 3 2
30 65 20 95 100 45 70 85 20 35 95 50 40 15 85
0 25 45 35 65 70 80 90 40 55 20 20 45 75 100
%%%%
2
4
5
6
7
8
11
14
15
%%%% end
*/

//
// io
//

fn read_tokens_vec<F: FromStr>() -> io::Result<Vec<F>>
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

fn read_tokens<F: FromStr + Sized + Default + Copy, const N: usize>() -> io::Result<[F; N]>
where
    <F as FromStr>::Err: Debug,
{
    let vec = read_tokens_vec::<F>()?;
    if vec.len() != N {
        return Err(io::Error::new(io::ErrorKind::Other, ""));
    }
    let mut result: [F; N] = [F::default(); N];
    for i in 0..N {
        result[i] = vec[i];
    }
    Ok(result)
}
