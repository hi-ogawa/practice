# misc

```bash
# Lint *.py
pip install -r requirements.txt
shopt -s globstar
flake8 **/*.py
black **/*.py

# Lint *.js
npm install
npx eslint '**/*.js' --fix --format unix

# Lint *.cpp
shopt -s globstar
clang-format **/*.cpp -i --style="{BasedOnStyle: Google, ReflowComments: false}"

# Build precompiled headers (cf. misc/run.py)
echo '#include <bits/stdc++.h>' > ./build/pch.hpp
clang++ -std=c++17 -O2 -march=native ./build/pch.hpp -o ./build/pch.hpp.gch
clang++ -std=c++17 -g -DDEBUG -fsanitize=address -fsanitize=undefined ./build/pch.hpp -o ./build/pch.hpp.gch-debug
```
