function [] = Measure(a,x)
%  Return absolute and relative errors
%  If "Delta(a) > 0", we say that "a" approximates "x" by shortage.
%  If "Delta(a) < 0" we say that "a" approximates "x" by addition.

if nargin > 3
    error('Error! This Function Only Takes Three Arguments.');
end

sizeA = length(a);
sizeX = length(x);

if sizeA ~= sizeX
    error('Error! Invalid Size For Arrays')
end
  
deltaA = x - a;

if all(deltaA == 0)
    fprintf('deltaA is 0\n')
    return
end

absolute = abs(deltaA);
relative = absolute ./ abs(a);

i = 1;
while i <= sizeA
    fprintf('a = %.8f \n',a(i))
    fprintf('x = %.8f \n',x(i))

    fprintf('absolute = %.8f\n',absolute(i))
    fprintf('relative = %.8f\n',relative(i))

    if deltaA(i) > 0
    fprintf('a approximates x by shortage\n')
    fprintf('\n')
    else
    fprintf('a approximates x by addition\n')
    fprintf('\n')
    end

    i = i + 1;
end

[minimumAbsolute, minimumAbsolutePos] = min(absolute);
[minimumRelative, minimumRelativePos] = min(relative);

fprintf('ErrAbs = %.8f , position = %d\n',minimumAbsolute, minimumAbsolutePos)
fprintf('ErrRel = %.8f , position = %d\n',minimumRelative, minimumRelativePos)
end






