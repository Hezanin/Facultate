function [x] = f4(a,b,y)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
x = [];
[l,c] = size(a);

if l ~= c && (l * c) ~= length(b)
    error('Date gresite');
end

if y == 2
    x = a ./ b;
elseif y == 1
    x = b / (a * transpose(a));
elseif y == 0
    x = inv(a);
else
    x = zeros(1,length(b));
    x(1:end) = NaN;
end
x
end