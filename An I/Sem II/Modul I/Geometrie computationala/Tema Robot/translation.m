function [newCoordonates] = translation(coordonates, translateValueX,translateValueY)
% Input argument represents a 2x5 matrix containing the coordonates
% Output represents the new coordonates matrix after translation

transform = [translateValueX ; translateValueY];
newCoordonates = transform + coordonates;

hold on
% plot(newCoordonates(1,:),newCoordonates(2,:),"k")
% axis([0,10,0,10])
end