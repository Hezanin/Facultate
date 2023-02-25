function [outputArg1,outputArg2] = createSpheres(numOfSpheres,numOfVertices)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

dimSubplot = ceil(sqrt(numOfSpheres))
for ind = 1:numOfSpheres
    [x,y,z] = sphere(numOfVertices);
    subplot(dimSubplot,dimSubplot,ind); 

    surf(x,y,z,'FaceColor',[rand(1),rand(1),rand(1)]);
    title('Nr sferei este: ',num2str(ind));
end