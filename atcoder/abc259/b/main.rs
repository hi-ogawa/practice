// AC

// https://atcoder.jp/contests/abc259/tasks/abc259_b

use std::{f64::consts::PI, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (a, b, d) = read_tokens::<f64>().map(|v| (v[0], v[1], v[2]))?;

    fn multiply(m: [[f64; 2]; 2], v: [f64; 2]) -> [f64; 2] {
        [
            m[0][0] * v[0] + m[0][1] * v[1],
            m[1][0] * v[0] + m[1][1] * v[1],
        ]
    }

    let t = d / 180.0 * PI;
    let result = multiply([[t.cos(), -t.sin()], [t.sin(), t.cos()]], [a, b]);
    println!("{} {}", result[0], result[1]);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc259/b/main.rs

%%%% begin
2 2 180
%%%%
-2 -2
%%%% end

%%%% begin
5 0 120
%%%%
-2.49999999999999911182 4.33012701892219364908
%%%% end

%%%% begin
0 0 11
%%%%
0.00000000000000000000 0.00000000000000000000
%%%% end

%%%% begin
15 5 360
%%%%
15.00000000000000177636 4.99999999999999555911
%%%% end

%%%% begin
-505 191 278
%%%%
118.85878514480690171240 526.66743699786547949770
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
