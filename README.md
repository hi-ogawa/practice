Math and Programming Practice

```
# Lint *.py
pip install -r requirements.txt
shopt -s globstar
flake8 **/*.py
black **/*.py

# Lint *.js
npm install
npx eslint '**/*.js' --fix --format unix
```
