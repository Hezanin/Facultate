function [] = drawPolygon(coordinates)
% Draws polygon based on matrix's coordinates
% Input argument representz the coordinates matrix for XY

% matrix columns
size_coordinates = max(size(coordinates))

hold on
plot(coordinates(1,1),coordinates(2,1),'o','markerfacecolor','k')
plot(coordinates(1,size_coordinates),coordinates(2,size_coordinates),'o','markerfacecolor','k')
plot(coordinates(1,:),coordinates(2,:),'ko')
plot(coordinates(1,:),coordinates(2,:),'-k','LineWidth',.01)
end