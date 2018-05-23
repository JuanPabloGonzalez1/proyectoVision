%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Recibe un arreglo de datos vector, el numero de clases K y el numero max
%de iteraciones. Regresa arreglo de centros y arreglo de etiquetas (clases)
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%SE PUEDE EJECUTAR:%%%%%%%%%%%%%%%%%%%%%%%%%
%[centroides, etiq] = kmedias(data, 3, 200);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [centros, indices] = kmedias(vector, K, iteraciones)
L = size(vector,1);%Valores y arreglos a utilizar
D = size(vector,2);
cent = zeros(K,D);
dista = zeros(L,K);
indices = zeros(1,L);
%nsample = randi(L);
%cent = datasample(vector ,K,'Replace',false);% tomamos K centros del vector sin remplazo
cent = vector(randi(L, K, 1),:);
for p = 1 : iteraciones
%%%%%%%%%%%%%%%Distancias a centroides 
    for i = 1 : L
        for j = 1 : K
            dista(i,j) = sum((vector(i,:) - cent(j,:)) .^ 2);%guardamos distancias de centros a puntos
        end
        [minimo, ind] = min(dista(i,:));%Tomamos clase con menor distancia
        indices(i) = ind;
    end
%%%%%%%%%%%%%Nuevo centroide
    for i = 1 : K
        clasei = vector(indices == i,:);%Separamos clases
        tamclase = size(clasei, 1);
        if tamclase == 1
            cent(i,:) = clasei;
        else
            cent(i,:) = sum(clasei)/tamclase;%Media de cada clase
        end
    end
end
centros = cent;
end