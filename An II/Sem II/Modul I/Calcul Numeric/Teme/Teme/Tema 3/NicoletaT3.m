k1 = 5;
n1 = [10,25];
I1 = integrala(n1,k1);
subplot(2,2,1);
plot(1:n1(1),I1(1),'-o');
title(['k=',num2str(k1),', n=',num2str(n1(1))]);
subplot(2,2,2);
plot(1:n1(2),I1(2),'-o');
title(['k=',num2str(k1),', n=',num2str(n1(2))]);

k2 = 0.25;
n2 = [20,50];
I2 = integrala(n2,k2);
subplot(2,2,3);
plot(1:n2(1),I2(1),'-o');
title(['k=',num2str(k2),', n=',num2str(n2(1))]);
subplot(2,2,4);
plot(1:n2(2),I2(2),'-o');
title(['k=',num2str(k2),', n=',num2str(n2(2))]);
