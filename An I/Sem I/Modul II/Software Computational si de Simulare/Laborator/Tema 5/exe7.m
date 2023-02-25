function [x] = exe7(arr)
% Exercitiul 7
% Input - matrice, output - valoare

x = 0;
[l,c] = size(arr);

diagonalaA = sum(diag(arr));
diagonalaB = sum(diag(fliplr(arr)));
rezultat = abs(diagonalaA - diagonalaB);


if l == c
    for indl = 1:1:l
        for indc = 1:1:c
            if arr([indl],[indc]) > rezultat
                x = 1;
                break
            end
        end
    end
else
    error = 'Matricea nu este patratica'


x = arr;
end