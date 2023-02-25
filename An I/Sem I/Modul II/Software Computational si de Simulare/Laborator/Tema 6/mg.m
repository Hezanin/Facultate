function [mediaG] = mg(yourVector)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

mSize = length(yourVector);
mediaG = 1;
prod = 1;

for index = 1:mSize
    prod = prod * yourVector(index);
end

mediaG = sqrt(prod);

end