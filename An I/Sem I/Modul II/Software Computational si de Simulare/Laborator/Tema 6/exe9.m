function [Mp] = exe9(yourVector)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

s = length(yourVector);
suma = 0;

for index = 1:s
    suma = suma + (yourVector(index).^2);
end

suma = suma / s;
Mp = sqrt(suma);


end