#!/bin/bash
assert() {
    expected="$1"
    input="$2"

    ./10cc "$input" > tmp.s
    cc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

assert 0 "return 0;"
assert 42 "return 42;"
assert 21 "return 5+20-4;"
assert 41 "return 12 + 34 - 5 ;"
assert 47 'return 5+6*7;'
assert 15 'return 5*(9-6);'
assert 4 'return (3+5)/2;'
assert 10 'return -10+20;'
assert 75 'return -3*+5*-5;'

assert 0 'return 0==1;'
assert 1 'return 42==42;'
assert 1 'return 0!=1;'
assert 0 'return 42!=42;'

assert 1 'return 0<1;'
assert 0 'return 1<1;'
assert 0 'return 2<1;'
assert 1 'return 0<=1;'
assert 1 'return 1<=1;'
assert 0 'return 2<=1;'

assert 1 'return 1>0;'
assert 0 'return 1>1;'
assert 0 'return 1>2;'
assert 1 'return 1>=0;'
assert 1 'return 1>=1;'
assert 0 'return 1>=2;'

assert 3 'a = 3; return a;'
assert 22 'b = 5 * 6 - 8; return b;'
assert 2 'a=1;b=3;a=2; return a;'
assert 14 'a = 3; b = 5 * 6 - 8; return a + b / 2;'
assert 1 'a = 3; b = 1; a = b; return a;'
assert 3 'foo=3; return foo;'
assert 8 'foo123=3; bar=5; return foo123+bar;'

echo OK