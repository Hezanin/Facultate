function [inversa] = exe3(myMatrix)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

inversa = 0;

if det(myMatrix) ~= 0
    inversa = inv(myMatrix);
else 
    rang = rank(myMatrix)
end