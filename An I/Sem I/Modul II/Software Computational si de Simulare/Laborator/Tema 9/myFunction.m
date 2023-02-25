function [B] = myFunction(A,n)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

[l,c] = size(A);
a = diag(A);
b = diag(flipr(A));

if l~=c
    error('matricea nu este patratica');
end

if n>=0
    B = A^n;
elseif n<0
    B = (A^(-1))^n;
elseif n==0
    B = [a ; b];
end