function [newMat] = exe15(yourMAtrix,col_1,col_2)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

[l,c] = size(yourMAtrix);
newMat = zeros(l,c);

r = 0;
copyC = c;

% if columns nums are smaller than rows
if c < l
    copyC = c + (l - c);
else
    copyC = c;
end


% change matrix columns
for ind = 1:copyC
        r = yourMAtrix([ind],[col_1]);
        yourMAtrix([ind],[col_1]) = yourMAtrix([ind],[col_2]);
        yourMAtrix([ind],[col_2]) = r;
end


% add values to newMat from yourMAtrix    
for indl = 1:l
    for indc = 1:c
        newMat(indl,indc) = yourMAtrix(indl,indc);
    end
end

end
