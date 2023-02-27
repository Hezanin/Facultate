% Exercitiul 2: B
% REZOLVARE
% clear, clc
% format long
% 
% a = [3.14, 999996, 0.000009, 1.00345];
% x = [3.141592, 1000000, 0.000012, 1.000145];
% Measure(a,x);
% 
% % Exercitiul 2: C
% % REZOLVARE
% clear, clc
% a = [52,101,297];
% x = [50,100,300];
% Measure(a,x);
% Masurarea mai exacta este: 0.00990099

% Exercitiul 6
% REZOLVARE
% clear, clc
% values = [2.416752; 6.216253; 3.454650];
% 
% % Decimalele cerute
% n = [2, 3, 4, 5];
% 
% for i = 1:length(n)
%    rounded_values(:, i) = roundn(values, -n(i));
%    rounded_values(:, i) = round(rounded_values(:, i) * 10^n(i)) / 10^n(i);
%    if mod(rounded_values(:, i) * 10^n(i), 2) == 1
%        rounded_values(:, i) = rounded_values(:, i) - 1 / 10^n(i)
%    end
% end

% Exercitiul 7
% REZOLVARE

% clear, clc
% values = [2.456750; 2.42629; 2.456752; 2.416512; 2.45350]
% 
% % Decimalele cerute
% n = [3, 3, 3, 3, 3];
% 
% for i = 1:5
%    rounded_values(:, i) = roundn(values, -3);
%    rounded_values(:, i) = round(rounded_values(:, i) * 10^3) / 10^3;
%    if mod(rounded_values(:, i) * 10^3, 2) == 1
%        rounded_values(:, i) = rounded_values(:, i) - 1 / 10^3
%    end
% end

% Exercitiul 10
% REZOLVARE

clear, clc
a = [500, 499.992, 500.02, 499.979, 499.989];
x = [499.987, 499.987, 499.987, 499.987, 499.987];
Measure(a,x)




