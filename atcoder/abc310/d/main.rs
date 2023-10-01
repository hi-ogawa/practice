// TLE

// https://atcoder.jp/contests/abc310/tasks/abc310_d

fn main() {
    // n, t ~ 10
    let [n, t, m]: [usize; 3] = read_array();

    let mut bad_masks: Vec<usize> = vec![0; n];
    for _ in 0..m {
        let [x, y]: [usize; 2] = read_array();
        bad_masks[x - 1] |= 1 << (y - 1);
        bad_masks[y - 1] |= 1 << (x - 1);
    }

    // brute force: divide "n" into "t"     (TODO: not true, right..?)
    //   binom(n + (t - 1), n) ~ 10^6
    let mut result = 0;
    let mut team_masks = vec![0; t];

    let solve = RecursiveClosure::new(|solve, x: usize| {
        if x == n {
            // check at least one
            if team_masks.iter().all(|&u| u != 0) {
                result += 1;
            }
            return;
        }
        // TODO: looks bad... (this becomes O(t^n))
        for k in 0..t {
            if team_masks[k] & bad_masks[x] == 0 {
                team_masks[k] ^= 1 << x;
                solve.call(x + 1);
                team_masks[k] ^= 1 << x
            }
        }
    });
    solve.call(0);

    // ignore double count by symmetry
    fn factorial(n: usize) -> usize {
        if n > 1 {
            n * factorial(n - 1)
        } else {
            1
        }
    }
    result = result / factorial(t);
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc310/d/main.rs

%%%% begin
5 2 2
1 3
3 4
%%%%
4
%%%% end

%%%% begin
5 1 2
1 3
3 4
%%%%
0
%%%% end

%%%% begin
6 4 0
%%%%
65
%%%% end

%%%% begin
10 6 8
5 9
1 4
3 8
1 6
4 10
5 7
5 6
3 7
%%%%
8001
%%%% end

# custom tests
%%%% begin
10 10 0
%%%%
%%%% end
*/

//
// utils
//

struct RecursiveClosure<F>(std::cell::RefCell<F>);

impl<F> RecursiveClosure<F> {
    fn new<Arg, Ret>(f: F) -> Self
    where
        F: FnMut(&dyn Callable<Arg, Ret>, Arg) -> Ret,
    {
        RecursiveClosure(std::cell::RefCell::new(f))
    }
}

trait Callable<Arg, Ret> {
    fn call(&self, arg: Arg) -> Ret;
}

impl<Arg, Ret, F> Callable<Arg, Ret> for RecursiveClosure<F>
where
    F: FnMut(&dyn Callable<Arg, Ret>, Arg) -> Ret,
{
    fn call(&self, arg: Arg) -> Ret {
        (unsafe { &mut *self.0.as_ptr() })(self, arg)
    }
}

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
