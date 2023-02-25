function [bezier_coordinates] = getXY(n)
% Function to return matrix with chosen XY coordonates
% Input arguments represent Bezier Curve degree
% which turns into a n+1 points taken for matrix's coordinates

% Prompt user for number of points
[x,y] = ginput(n+1)
size_x = length(x);
size_y = length(y);

x = reshape(x,1,size_x);
y = reshape(y,1,size_y);
bezier_coordinates = [ x(1:end) ; y(1:end)];
end