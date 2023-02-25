A = [5 2 1 ; 3 4 7 ; -5 8 10];
B = [9 19 -1; -5 7 4 ; 8 -10 16];
k = 7;

a = A + B
b = A - B
c = A + k
d = k - A
e = A/B
f = A\B
g = A*B^-1
h = A^-1 * B
i = B * A^-1
j = B\A

A/B == A*B^-1;
B\A == B^-1*A;
A\B == A^-1*B;


A/B - A * B^-1;
B\A - B^-1 * A;
A/B - A^-1 * B;

