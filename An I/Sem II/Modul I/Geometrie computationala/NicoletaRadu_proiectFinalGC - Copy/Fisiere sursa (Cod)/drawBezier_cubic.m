function [x,y] = drawBezier_cubic(bezier_coordinates)
% Draws a cubic Bezier Curve using Bernstein polynomials
% Input arguments reprezent the following points:
% start,2 control,end 

% time array
t = 0:0.001:1;
s = max(size(bezier_coordinates));

% Bernstein polynomials
bernstein_b0 = (1 - t).^3;
bernstein_b1 = 3 .* (1 - t).^2 .* t;
bernstein_b2 = 3 .* (1 - t) .* t.^2;
bernstein_b3 = t.^3;

% Calculates XY coordinates
x = bezier_coordinates(1,1)*bernstein_b0 + bezier_coordinates(1,2)*bernstein_b1 + bezier_coordinates(1,3)*bernstein_b2 + bezier_coordinates(1,4)*bernstein_b3;
y = bezier_coordinates(2,1)*bernstein_b0 + bezier_coordinates(2,2)*bernstein_b1 + bezier_coordinates(2,3)*bernstein_b2 + bezier_coordinates(2,4)*bernstein_b3;

hold on
drawPolygon(bezier_coordinates)
plot(x,y,'b','LineWidth',0.2)
axis([0,1,0,2])
end