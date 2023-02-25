A = [2 7 9 1 7; 3 1 5 2 6; 8 4 1 2 5];A(:,2:2:end)
v = [sum(A(:,2:2:end))];

w = [prod(A(1:2:end,:),2)];

sum(A(:,1:2:end));

sqrt(A);
mean(sqrt(A),2);