function [yourMatrix] = exe13(m,n)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here


for indL = 1:m
    for indC = 1:n
        yourMatrix(indL,indC) = '*';
    end
end


mat2str(yourMatrix);

for indexL = 1:m
    for indexC = 1:n
        if rem(indexC,2) == 1
            yourMatrix(indexL,indexC) = '*';
        else
            yourMatrix(indexL,indexC) = '@';
        end
    end
end