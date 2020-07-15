Math and Programming Practice

```
# Lint *.py
pip install -r requirements.txt
shopt -s globstar
black **/*.py

# Lint *.js
npm install
npx eslint '**/*.js' --fix --format unix
```
