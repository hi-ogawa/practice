// AC

// https://atcoder.jp/contests/abc273/tasks/abc273_e

use std::{collections::BTreeMap, fmt::Debug, io, rc::Rc, str::FromStr};

fn main_case() -> io::Result<()> {
    // q ~ 10^5
    let q: usize = read_tokens()?[0];

    let mut history: Vec<Rc<List>> = vec![Rc::new(List::Nil)];

    let mut pages: BTreeMap<usize, usize> = BTreeMap::new();

    for i in 0..q {
        let query = read_tokens::<String>()?;
        let next = match query[0].as_str() {
            "ADD" => {
                let x: usize = query[1].parse().unwrap();
                Rc::new(List::Cons(history[i].clone(), x))
            }
            "DELETE" => match &*history[i] {
                List::Nil => Rc::new(List::Nil),
                List::Cons(ls, _) => ls.clone(),
            },
            "SAVE" => {
                let p: usize = query[1].parse().unwrap();
                pages.insert(p, i);
                history[i].clone()
            }
            "LOAD" => {
                let p: usize = query[1].parse().unwrap();
                let j = *pages.entry(p).or_insert(0);
                history[j].clone()
            }
            _ => unreachable!(),
        };
        let result = match &*next {
            List::Nil => -1,
            List::Cons(_, x) => *x as isize,
        };
        if i > 0 {
            print!(" ");
        }
        print!("{}", result);
        history.push(next);
    }
    println!("");

    Ok(())
}

#[derive(Debug)]
enum List {
    Nil,
    Cons(Rc<List>, usize),
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc273/e/main.rs

%%%% begin
11
ADD 3
SAVE 1
ADD 4
SAVE 2
LOAD 1
DELETE
DELETE
LOAD 2
SAVE 1
LOAD 3
LOAD 1
%%%%
3 3 4 4 3 -1 -1 4 4 -1 4
%%%% end

%%%% begin
21
ADD 4
ADD 3
DELETE
ADD 10
LOAD 7
SAVE 5
SAVE 5
ADD 4
ADD 4
ADD 5
SAVE 5
ADD 2
DELETE
ADD 1
SAVE 5
ADD 7
ADD 8
DELETE
ADD 4
DELETE
LOAD 5
%%%%
4 3 4 10 -1 -1 -1 4 4 5 5 2 5 1 1 7 8 7 4 7 1
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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
