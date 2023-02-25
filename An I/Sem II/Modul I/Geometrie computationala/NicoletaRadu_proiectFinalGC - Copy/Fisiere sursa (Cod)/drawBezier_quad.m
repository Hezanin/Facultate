function [x,y] = drawBezier_quad(bezier_coordinates)
% Draws a quadratic Bezier Curve using Bernstein polynomials
% Input arguments reprezents the Bezier's control polygon coordinates
% The coordinates are XY (2D space) points

% time array
t = 0:0.001:1;

% number of matrix columns
s = max(size(bezier_coordinates));

% Bernstein polynomials
bernstein_b0 = (1 - t).^2;
bernstein_b1 = 2 * t.* (1 - t);
bernstein_b2 = t .^ 2;

% Calculates XY coordinates
x = bezier_coordinates(1,1)*bernstein_b0 + bezier_coordinates(1,2)*bernstein_b1 + bezier_coordinates(1,3)*bernstein_b2;
y = bezier_coordinates(2,1)*bernstein_b0 + bezier_coordinates(2,2)*bernstein_b1 + bezier_coordinates(2,3)*bernstein_b2;

hold on
drawPolygon(bezier_coordinates)
plot(x,y,'b','LineWidth',0.2)
axis([0,1,0,2])
end