% TIPUL I 
% EXE a
% a = 10;
% b = 15;
% M = a + (b - a) * rand(4,3)
% 
% exe b
% minimum = floor(min(min(M)));
% suma = floor(sum(sum(M)));
% rez = lcm(minimum, suma);
% 
% exe c
% V1 = reshape(M,1,[]);
% rezultat = any(V1 < 5*pi);
% 
% exe d
% nu stiu
% 
% exe e
% s1 = 'Maria';
% s2 = 'Ana';
% s3 = 'Ioana';
% s4 = 'Georgiana';
% s5 = 'Camelia';
% 
% str2mat(s1,s2,s3,s4,s5);
% 
% exe f
% nu stiu
% 
% TIPUL III
% exe 1
% x = linspace(-pi/2,pi/2,30);
% y1 = cos(x).^2;
% y2 = exp(x.^2 + 5);
% 
% hold on
% subplot(2,1,1); plot(x,y1,'--r');
% subplot(2,1,2); plot(x,y2,'-.g')
% hold off
% 
% exe 2
% [x,y] = meshgrid(linspace(-1,1,30));
% z = exp(sin(x + y) .* cos(x));
% 
% R = [10 10]
% N = 20;
% [x1,y1,z1] = cylinder(R,N);
% 
% figure(1)
% surf(z);
% 
% figure(2)
% surf(x1,y1,z1); shading interp
% 
M = a + (b - a) * rand(4,4)
B = reshape(M,1,[]);
y = 5;
f4(M,B,y)
