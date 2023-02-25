function [fibVector] = exe18(n)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here

fibVector = zeros(1,n+2);
fibVector(1) = 0;
fibVector(2) = 1;

if n <= 0
    error = 'N trebuie sa fie un numar pozitiv!!!'

else
    for index = 3:n
        fibVector(index) = fibVector(index - 1) + fibVector(index - 2);
    end

end
end