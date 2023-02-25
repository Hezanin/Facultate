Note = [9.5 9.33 8.75; 8.7 10 9; 10 9.5 10];

op = [mean(Note,2)];
reshape(op,1,3);
[maxim,ind]=max(op);