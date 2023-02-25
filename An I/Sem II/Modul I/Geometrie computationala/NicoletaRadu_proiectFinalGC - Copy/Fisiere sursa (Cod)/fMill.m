function [] = fMill(p)
% F-Mill algorithm for geometric continuity in Bezier curves
% The input argument is a matrix containing the control polygon's
% coordonates
% The purpose of this function is to draw a spline Bezier curve

n = max(size(p));
l = zeros(2,n-2);

a = p(1,2);
e = p(2,2);
c = p(1,n-1);
d = p(2,n-1);

hold on
for j = 1:(n-2)
    l(:,j) = p(:,j+2) - p(:,j);
end
    ultim = 3  * (n-1) + 1;
    b = ones(2,ultim);
    b(:,1) = p(:,1);
    b(:,2) = [a;e];
    b(:,3) = p(:,2) - (1/6) * l(:, 1);

for k = 1:(n-3)
    b(:,3*k+1) = p(:,k+1);
    b(:,3*k+2) = p(:,k+1) + (1/6) * l(:,k);
    b(:,3*k+3) = p(:,k+2) - (1/6) * l(:,k+1);
end
    
    b(:,3*(n-2)+1) = p(:,n-1);
    b(:,3*(n-2)+2) = p(:,n-1) + (1/6) * l(:,n-2);
    b(:,3*(n-2)+3) = [c;d];

    b(:,ultim) = p(:,n);
    i = 1;
    nr = 1;
    ng = floor(ultim/4)+1;
    
while nr<=ng
    plot(b(1,i:i+3),b(2,i:i+3),'kx-')
    nr = nr+1;
    i = i+3;
end

    t = 0:0.001:1;
    B0 = (1-t) .^3;
    B1 = 3.* (1-t).^2.*t;
    B2 = 3.* (1-t) .* t .^ 2;
    B3 = t.^3;
    B = [B0;B1;B2;B3];
    m = length(t);
    x = zeros(2,m);
    i = 1;
    nr = 1;
    
drawPolygon(p)

    while nr<=ng
        x = b(:,i:i+3) * B;
        plot(x(1,:),x(2,:),'-','LineWidth',1,'Color',[0.4 0.1 0.0]);
        axis([0,1,0,2])
        %fill(x(1,:),x(2,:),'g')
        nr = nr + 1;
        i = i + 3;
    end
end








