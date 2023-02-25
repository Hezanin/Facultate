% b
a = [2 -3 7 4];
b = [4 5 -1 2];
matrix1 = complex(a,b);
matrix1 = [matrix1(1:2);matrix1(3:4)];


a = [-2 1 2];
b = [4 1 7];
matrix2 = [complex(a,b)];
matrix2 = [7, matrix2(1:end)];
matrix2 = [matrix2(1:2);matrix2(3:4)];

% c

o = [5 -7 4];
p = [2 2 -3];
v1 = [complex(o,p)];

r = [-3 8 9];
s = [1 4 -7];
v2 = [complex(r,s)];

w2=angle(v1); %unghiul in radiani
w2 = [(pi/180) * w2(1:end)]; %grade

abs(w2); %modul
real(w2); %partea reala
imag(w2); %partea imaginara
conj(w2); %conjugatul

%exercitiul 18

a = [2 5 256];
b = [7 8 1/3];

v3 = [2^7 5^8 256.^1/3];
a.^b;

M5 = pow2(matrix1)



