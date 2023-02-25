function [rezultat] = exe4(x)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

if x < 1
    rezultat = 1 / (2 * x - 1);
elseif x == 1
    rezultat = 0;
elseif x > 1
    rezultat = log(x^2 - 2 * x + 2);
else
    error = 'Valoarea introdusa este ilegala'

end