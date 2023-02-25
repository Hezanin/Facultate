function [newMatrix] = exe8(yourMatrix,option)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here

[l,c] = size(yourMatrix);
newMatrix = zeros(l,c);

% prin instructiuni de control
if option == 1
    for indexl =  1:l
        for indexc = 1:c
            if rem(yourMatrix(indexl,indexc),2) == 0
                yourMatrix(indexl,indexc) = inf;
            end
        end
    end
elseif option == 2
    [row,col] = find(rem(yourMatrix,2) == 0);
    yourMatrix(sub2ind(size(yourMatrix),row(:),col(:))) = inf;
else
    [row,col] = find(rem(yourMatrix,2) == 0);
    yourMatrix(sub2ind(size(yourMatrix),row(:),col(:))) = inf;
end

% prin comenzi matlab
for indexl = 1:l
    for indexc = 1:c
        newMatrix(indexl,indexc) = yourMatrix(indexl,indexc);
    end

end