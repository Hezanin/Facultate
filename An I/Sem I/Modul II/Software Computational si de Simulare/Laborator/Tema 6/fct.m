function [rezultat] = fct(x)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

if x <=1
    rezultat = exp(x) + x - 1;
else
    rezultat = 1 / (x^(x-1));
end