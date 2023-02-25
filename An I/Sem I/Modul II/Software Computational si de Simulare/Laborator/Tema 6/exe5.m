function [produs] = exe5(yourVector)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

n = length(yourVector);
produs = 1;

for index = 1:n
    produs = produs * yourVector(index);
end