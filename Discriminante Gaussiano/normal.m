function L = normal(x,media1, media2,covarianza,n)
  
normal1 = (1/(((2*pi)^(n/2))*sqrt(det(covarianza))))*exp((-1/2)*(x - media1)*inv(covarianza)*(x - media1)');
normal2 = (1/(((2*pi)^(n/2))*sqrt(det(covarianza))))*exp((-1/2)*(x - media2)*inv(covarianza)*(x - media2)');

if normal1 > normal2
  L = 1;
else
  L = 2;
end

end