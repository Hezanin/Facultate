function [newCoordonates] = rotate(coordonates,degree)
% Input argument represent a 2x5 matrix containing the coordonates
% The polygon will be rotated based on the given degree value

x = coordonates(1,:) * cos(degree) - coordonates(2,:) * sin(degree);
y = coordonates(1,:) * sin(degree) + coordonates(2,:) * cos(degree);
newCoordonates = [x ; y];

% hold on
% plot(x,y,"k")
% axis([0,10,0,10])
end