A = [2 7 9 7 ; 3 1 5 6 ; 8 1 2 5];

sum(A);

reshape(A,2,6);

flipud(A);

fliplr(A);

prod(A);

mean(A,2);

A';

prod(A');

prod(A(:,1:2),2);

prod(A',2);

sort(A,2);

[M,I] = sort(A,2);

diag(A);

diag(A,1);

[m,ind] = max(A(:,1:2:end-1));




