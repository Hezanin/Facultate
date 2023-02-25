function [prod] = factorial_n(n)
%UNTITLED3 Summary of this function goes here
%   Details./..
prod = 1;

for ind = 1:n
    prod = prod * ind;
end