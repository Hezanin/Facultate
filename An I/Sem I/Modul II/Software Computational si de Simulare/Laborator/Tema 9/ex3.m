function [fxy] = ex3(x,y)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

fxy = (1 / 2 * pi) .* exp((-1/2) .* (x.^2 + y.^2));
end