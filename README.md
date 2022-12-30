# math and programming practice

## helper scripts

- `misc/run.py`
- `misc/prepare.sh`
- `misc/templates`
  - `main.cpp`, `main.rs`, `main.py`
  - `lib.cpp`, `lib.rs`

## example usage

```sh
# create a file "atcoder/abc268/d/main.rs" based on "misc/templates/main.rs" and download test data from https://atcoder.jp/contests/abc268/tasks/abc268_d
bash misc/prepare.sh atcoder/abc268/d/main.rs https://atcoder.jp/contests/abc268/tasks/abc268_d

# compile and run inline tests
python misc/run.py atcoder/abc268/d/main.rs --check
```
