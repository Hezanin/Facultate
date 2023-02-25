function [P,N,O] = exe10(yourVector)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

vectorSize = length(yourVector);
P = 0;
N = 0;
O = 0;

for index = 1:vectorSize
    if yourVector(index) == 0
        O = O + 1;
    elseif yourVector(index) > 0
        P = P + 1;
    elseif yourVector(index) < 0
        N = N + 1;
    end
end

P
N
O
end