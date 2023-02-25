function [P] = lerp(p0,p1)
% Lerping - implemented for De Casteljau's Algorithm 
% Part of calculating & drawing a Bezier Curve
t = 0:0.01:1;
P = (1 - t) .* p0 + t .* p1;
end