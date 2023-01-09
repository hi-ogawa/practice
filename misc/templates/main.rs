// WIP

// {{PROBLEM_URL}}

fn main_case() {}

fn main() {
    main_case();
    // let t: usize = read_tokens()[0];
    // for _ in 0..t {
    //     main_case();
    // }
}

/*
python misc/run.py {{FILE}}

{{TESTS}}
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
