function [matrixB, numY] = someFunction(matrixA, numA, numB, numX)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

[l,c] = size(matrixA);
numX = input("Dati valoare pentru X: ")
while numX < numA && numX > numB
    numX = input("Dati valoare pentru X: ")
end

if numX >= numA && numX <= numB
    matrixB = randi([numA,numB],l,c);
end

[l,c,Valoare] = find(matrixA < numX);
numY = sum(Valoare)
end