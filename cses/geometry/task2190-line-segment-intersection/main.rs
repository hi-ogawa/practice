// AC

use std::{fmt::Debug, io, str::FromStr};

fn check_intersect(p: (i64, i64), l1: (i64, i64), l2: (i64, i64)) -> bool {
    if get_signed_area(p, l1, l2) != 0 {
        return false;
    }

    let x0 = l2.0 - l1.0;
    let y0 = l2.1 - l1.1;
    let x1 = p.0 - l1.0;
    let y1 = p.1 - l1.1;

    let dot = x0 * x1 + y0 * y1;
    let len0 = x0 * x0 + y0 * y0;
    let len1 = x1 * x1 + y1 * y1;

    dot >= 0 && len0 >= len1
}

fn get_signed_area(p: (i64, i64), q: (i64, i64), r: (i64, i64)) -> i64 {
    let x0 = q.0 - p.0;
    let y0 = q.1 - p.1;
    let x1 = r.0 - p.0;
    let y1 = r.1 - p.1;
    x0 * y1 - x1 * y0
}

fn main_case() -> io::Result<()> {
    let v = read_tokens::<i64>()?; // [-10^9, 10^9];
    let p1 = (v[0], v[1]);
    let p2 = (v[2], v[3]);
    let q1 = (v[4], v[5]);
    let q2 = (v[6], v[7]);

    // check singular case (one endpoint is on the other segment)e
    if check_intersect(p1, q1, q2)
        || check_intersect(p2, q1, q2)
        || check_intersect(q1, p1, p2)
        || check_intersect(q2, p1, p2)
    {
        println!("YES");
        return Ok(());
    }

    // check non-singular case
    let p1_p2_q1 = get_signed_area(p1, p2, q1).signum();
    let p1_p2_q2 = get_signed_area(p1, p2, q2).signum();
    let q1_q2_p1 = get_signed_area(q1, q2, p1).signum();
    let q1_q2_p2 = get_signed_area(q1, q2, p2).signum();
    if p1_p2_q1 * p1_p2_q2 == -1 && q1_q2_p1 * q1_q2_p2 == -1 {
        println!("YES");
        return Ok(());
    }

    println!("NO");
    Ok(())
}

fn main() -> io::Result<()> {
    let t: usize = read_tokens()?[0]; // [1, 10^5]
    for _ in 0..t {
        main_case()?
    }
    Ok(())
}

/*
python misc/run.py cses/geometry/task2190-line-segment-intersection/main.rs

%%%% begin
5
1 1 5 3 1 2 4 3
1 1 5 3 1 1 4 3
1 1 5 3 2 3 4 1
1 1 5 3 2 4 4 1
1 1 5 3 3 2 7 4
%%%%
NO
YES
YES
YES
YES
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
