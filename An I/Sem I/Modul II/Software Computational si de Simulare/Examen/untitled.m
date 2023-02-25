% V = logspace(10^02, 10^2,12);
% 
% a = floor(V(6));
% b = floor(V(9));
% rezultat = lcm(a,b);
% 
% test = [5 6 1 2 0 -7];
% 
% any(V < 1);
% find(V < 1);
% V(V < 1);
% 
% sir = '1234455665544321';
% rez = [strfind(sir,'4')]
% rezultat = length(rez)

% A = randi([2,6],4,6);
% n = 2;
% 
% f(A,n);

R = [10 10]
r = 10;
[X,Y,Z] = cylinder(r);
h = 8;
Z = Z*h;

[x1,y1]= meshgrid(linspace(1,10,30));
z1 = (x1 / y1) + exp(3) ./ sqrt(x1);

figure(1)
surf(X,Y,Z)

figure(2)
surf(x1,y1,z1); shading interp

% q1 = [1 7 0 5 12];
% q2 = [1 8 0 8 13];



% M = [1 2 -1; -1 1 -1; 1 1 0];
% B = [1 -2 1];
% B = B(:);
% x = [i*1;i*2;i*3];
% 
% A .* x == B
% p = [3 , 0 , 2];
% q = [1 , 1];
% [q,d] = polyder(p,q)

