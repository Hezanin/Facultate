x = [3 2 5 1 6 8]';
y = [1 2 4 7 3 5]';

sum(x);
a = sum(x) + y;
b = prod(x.^y);

max(y);
z = x.*max(y);
