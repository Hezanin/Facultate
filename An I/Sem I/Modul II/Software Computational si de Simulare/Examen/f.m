function [C] = f(A,n)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

[l,c] = size(A);

if l == c
    C = A.^n
elseif l ~= c
       if l > c
           dim = l - c;
           B = A(1:l - dim,1:c);
           C = B.^n
       else 
           dim = c - l;
           B = A(1:l,1: c - dim);
           C = B.^n
       end
end