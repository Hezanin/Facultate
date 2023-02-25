function [p,a,c] = exe6(n,m,x)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
p = 1;

if n > m

    if x == 1
        p = factorial_n(n);
    elseif x == 2
        a = factorial_n(n) / (factorial_n(n-m));
    elseif x == 3
        c = factorial_n(n) / (factorial_n(m) * factorial_n(n-m));
    else 
        message = 'X inafara multimii'
        p = factorial_n(n);
    end

elseif n == m
        message = 'n == m'
        p = factorial_n(n);
else
aux = n;
n = m;
m = aux;

    if x == 1
        p = factorial_n(n);
    elseif x == 2
        a = factorial_n(n) / (factorial_n(n-m));
    elseif x == 3
        c = factorial_n(n) / (factorial_n(m) * factorial_n(n-m));
    else 
        message = 'X inafara multimii'
        p = factorial_n(n);
    end
end