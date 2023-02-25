A = [];
ones(10);

b = zeros(2,2); %first matrix
b = b(:);

c = ones(2,2); %second matrix
c = c(:);

g = [b c]; %right wing matrix

d = eye(2); %third matrix

e = zeros(2);  %fourth

h = [d;e];

M = [h,g];

[z,x] = size(M);
zeros(z,x);

A = max(M,[],"all");

max( max(M));
min(min(M));

N = [1 2 3 4;5 6 7 8]
Y = flip(N,2);
Z = flip(Y,1);
N = [N;Z];











