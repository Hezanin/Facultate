function [newCoordonates] = scale(coordonates, scaleAmountXAxis, scaleAmountYAxis)
% Input argument represents a 2x5 matrix containing X and Y coordinates
% Second input argument represents the value by which the polygon will be
% scaled up to

transform = [scaleAmountXAxis 0 ; 0 scaleAmountYAxis];
newCoordonates = transform * coordonates;

% plotting of the newly scaled polygon
% hold on
% plot(newCoordonates(1,:),newCoordonates(2,:),"k")
% axis([0,10,0,10])
end