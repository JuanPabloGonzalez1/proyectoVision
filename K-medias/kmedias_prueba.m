DataSeed
data = datos(:,1:7);
labels = datos(:, 8);
[centroides, etiq] = kmedias(data, 3, 200);
O = [labels, etiq'];
F1 = efectivxclase(O(1:70,:))*100;
F2 = efectivxclase(O(71:140,:))*100;
F3 = efectivxclase(O(141:210,:))*100;
display('Total ejemplos')
A = length(O)
display('Efectividad clase 1:')
F1
display('Efectividad clase 2:')
F2
display('Efectividad clase 3:')
F3