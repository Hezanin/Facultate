function [P] = drawBezier_casteljau_cubic(M)
% De Casteljau's algorithm for drawing Bezier Curves
% Input arguments reprezent the following points:
% start,2 control,end  

% De Casteljau's calculation for finding the curve's point(C3)
A = lerp(M(:,1),M(:,2));
B = lerp(M(:,2),M(:,3));
C = lerp(M(:,3),M(:,4));
D = lerp(A,B);
E = lerp(B,C);
P = lerp(D,E);

t = 1/2;
level_1 = zeros(2,3);
level_2 = zeros(2,2);
level_3 = zeros(2,1);

for i=1:3
level_1(:,i)=M(:,i).*(1-t)+M(:,i+1).*t; %nivelul 1
end
for i=1:2
level_2(:,i)=level_1(:,i).*(1-t)+level_1(:,i+1).*t; %nivelul 2
end
level_3(:,1) = level_2(:,1).*(1-t)+level_2(:,2).*t; %nivelul 3


hold on
drawPolygon(M)
plot(level_1(1,:),level_1(2,:),'-g*')
plot(level_2(1,:),level_2(2,:),'-k*')
plot(level_3(1,:),level_3(2,:),'m*')
plot(P(1,:),P(2,:),'k','LineWidth',1)
axis([0,1,0,2])
end