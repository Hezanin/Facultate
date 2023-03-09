function I = integrala(n,k)
  I = zeros(1,max(n));
  I(1) = log(k+1)-log(k); % I0
  for i=2:max(n)
    I(i) = 1/i - k*I(i-1); % relația de recurență
  end
  I = I(n); % selectează valorile corespunzătoare lui n
end
