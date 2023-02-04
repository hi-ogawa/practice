// AC

use std::{cell::RefCell, collections::BTreeMap, fmt::Debug, io, rc::Rc, str::FromStr};

fn main() -> io::Result<()> {
    let n_k: Vec<usize> = read_tokens()?; // [1, 2×10^5]
    let n = n_k[0];
    let k = n_k[1];
    let ps: Vec<usize> = read_tokens()?.iter().map(|p| p - 1usize).collect(); // {0, .., n-1}

    let mut result: Vec<i64> = vec![-1; n];

    // on-the-table stacks ordered by the top card
    let mut stacks: BTreeMap<usize, Rc<RefCell<Vec<usize>>>> = BTreeMap::new();

    for (i, &x) in ps.iter().enumerate() {
        if let Some((&y, stack)) = stacks.range(x..).next() {
            // convoluted control flow to workaround mutation lifetime
            let mut done = false;
            {
                let mut stack = stack.borrow_mut();
                stack.push(x);
                if stack.len() == k {
                    for &z in stack.iter() {
                        result[z] = i as i64 + 1;
                    }
                    done = true;
                }
            }
            if !done {
                stacks.insert(x, stack.clone());
            }
            stacks.remove(&y);
        } else {
            if k == 1 {
                result[x] = i as i64 + 1;
                continue;
            }
            stacks.insert(x, Rc::new(RefCell::new(vec![x])));
        }
    }

    for i in result {
        println!("{}", i);
    }
    Ok(())
}

/*
python misc/run.py atcoder/abc260/d/main.rs

%%%% begin
5 2
3 5 2 1 4
%%%%
4
3
3
-1
4
%%%% end

%%%% begin
5 1
1 2 3 4 5
%%%%
1
2
3
4
5
%%%% end

%%%% begin
15 3
3 14 15 9 2 6 5 13 1 7 10 11 8 12 4
%%%%
9
9
9
15
15
6
-1
-1
6
-1
-1
-1
-1
6
15
%%%% end
*/

//
// io
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
