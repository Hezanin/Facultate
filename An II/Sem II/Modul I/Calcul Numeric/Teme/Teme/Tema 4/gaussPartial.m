function x=gauss(a,b)
n=length(b);
[lin,col]=size(a);
if lin~=col
 error('Matricea nu e patratica');
else
 if(det(a)==0)
 error('Matricea este singulara, det(A)=0');
 end
end
a=[a b] % matricea extinsa
x=zeros(n,1);
tic % pornim cronometrul
for i=1:n
if ( (a(i,i)~=0) || ( max(abs(a(i:n,i)))~=0 ) )
 % in m se retine maximul
 % in k se retine linia unde s-a gasit maximul
 [m,k]=max(abs(a(i:n,i))); %retin cea mai mare valoare de pe coloana i
 k=k+i-1;
 %fixam linia k ca sa fie intotdeauna pt linii de sub pivot
 % schimbam linia i cu linia k pt toate coloanele
 a([i k],1:n+1)=a([k i],1:n+1);
 % o data fixat pivotul, putem imparti linia la pivot
 a(i,i:n+1)=a(i,i:n+1)/a(i,i);
 % aplicam regula de pivotare
 a(i+1:n,i+1:n+1)=a(i,i)*a(i+1:n,i+1:n+1)-a(i+1:n,i)*a(i,i+1:n+1);
 % dupa calcul adaugam sub pivot valoarea 0
 a(i+1:n,i)=0;
 else
 error('impartire la 0. Sistemul nu este compatibil determinat');
end %de la if
end %de la for
toc % oprim cronometrul (afiseaza secundele)
for k=n:-1:1
 x(k)=a(k,n+1)-a(k,k+1:n)*x(k+1:n); % calcularea vectorului cu
%solutiile
end
fprintf('\nSolutiile sub forma de fractii:\n')
disp(rats(x')) % ne afiseaza valorile lui x sub forma de fractii (rats)
end