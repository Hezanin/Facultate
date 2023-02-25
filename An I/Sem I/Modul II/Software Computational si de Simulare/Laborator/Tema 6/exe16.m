function [finalVect] = exe16(vect1, vect2)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here

v1 = length(vect1);
v2 = length(vect2);
fV = v1 + v2;

finalVect = zeros(1,fV);
specialIndex = 0;

if v1 ~= v2
    error = 'vectorii trebuie sa fie de aceeasi marime!!!'

elseif v1 == v2
    % for vector 1
    for index = 1:2:fV
            finalVect(index) = vect1(specialIndex + 1);
        end
    end
    
    % for vector 2
    for index = 2:2:fV
        finalVect(index) = vect2(specialIndex + 1);
    end
end