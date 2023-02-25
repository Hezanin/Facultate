function [count] = gasesteValoarea(yourMatrix,yourVar)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

[l,c] = size(yourMatrix);
count = 0;

for indL = 1:l
    for indC = 1:c
        if yourMatrix(indL,indC) == yourVar
            count = count + 1;
        end
    end
end