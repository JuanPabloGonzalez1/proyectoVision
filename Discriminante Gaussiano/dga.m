DataSeed
clases = datos(71:end, :);
clase1 = datos(71:140,:);
clase2 = datos(140:end,:);
media1 = mean(clase1);
media2 = mean(clase2);
phi = 0.5;
covarianza = zeros(7,7);
n = 7;%Caracteristicas
%Calculamos matriz de covarianza para ambas clases
for i = 1 : length(clases)
  if clases(8) == 2
    covarianza = covarianza + (clases(i,1:7) - media1(1:7))'*(clases(i,1:7) - media1(1:7) );%columna x fila
  else
    covarianza = covarianza + (clases(i,1:7) - media2(1:7))'*(clases(i,1:7) - media2(1:7) );%
  end
end
labels = zeros(1,length(clases));
%Distribuciones para ambas clases
for i = 1 : length(clases)
  labels(i) = normal(clases(i,1:7),media1(1:7),media2(1:7),covarianza,n);
end
display('Datos - Clases Datos - Clases finales de clasificador')
[clases,labels']