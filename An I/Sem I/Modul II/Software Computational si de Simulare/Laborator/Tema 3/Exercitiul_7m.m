A = rand(3);
a = 10;
B = a+rand(4,5);

C = randn(4); 
C = randn(2,3);

E = randi([5,9],5,2);

F = randi([-5,5],3);

G = ones(4);

H = zeros(1,5);
H(:);

a = 5;
b = 8;
I = a+(b-a)*rand(2,3);

% M1 matrix
a = eye(3);
b = ones(1,4);
d = b(:);
c = ones(1,3);
M1 = [c;a];
M1 = [M1 d];

% M2 matrix
a = zeros(2);
b = eye(2);
c = ones(1,4);
c = c(:);
M2 = [b;a];
M2 = [c M2];

% M3 matrix
a = eye(3);
b = zeros(1,3);
b = b(:);
c = ones(1,4);

M3 = [a b];
M3 = [M3;c];

max(length(M2));
min(length(M2));

[a,b] = size(A);
P = eye(a,b);


