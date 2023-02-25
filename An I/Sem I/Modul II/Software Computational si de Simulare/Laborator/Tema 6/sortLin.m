function [newM] = sortLin(M,lin)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

[l,c] = size(M);
newM = zeros(l,c);

C_1 = 0;
C_2 = 0;
min_idx = 0;


sortat = 1;

for indL = 1:l
    for indC = 1:c-1
        sortat = 1;
	      while sortat == 1
	            sortat = 0;
                 if M(lin,indC+1) < M(lin,indC)
                    C_1 = indC;
                    C_2 = indC + 1;

		            sortat = 1;
                    M = exe15(M,C_1,C_2);
                 end
        end
    end
end

% add values to newMat from yourMAtrix    
for indl = 1:l
    for indc = 1:c
        newM(indl,indc) = M(indl,indc);
    end
end
end
