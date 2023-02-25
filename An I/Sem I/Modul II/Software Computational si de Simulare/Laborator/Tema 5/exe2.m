function [vectorFormat,marimeVector,sumaElem] = exe2(a,b,p)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

vectorFormat = (a:p:b);
marimeVector = length(vectorFormat)
sumaElem = 0;

for index = 1:marimeVector
    sumaElem = sumaElem + vectorFormat(index);
end

sumaElem

end