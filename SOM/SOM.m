clc
clear
close all
echo off
X=5;
Y=5;
Z=7;
nodos = randi(10,X,Y,Z);
DataSeed;
radioIni=3;
consTiem=3;
LearningRI=1;
epocaFinal=100;
%nodos=ones(2,2,1);
%nodos(1,2,:)=7;
%
%datos=[9];

%Revolvemos los datos
for j=length(datos): -1: 1
		idx = randi(j);
		temp = datos(idx,:);
		datos(idx,:) = datos(j,:);
		datos(j,:) = temp(:);
end
datos;

for epoca=1:1:epocaFinal
  radio=radioIni*exp(-(epoca-1)/consTiem);
  radio=radioIni;
  for h=1: length(datos)
    BMU_dist=9999999;
    
    for i=1: 1: X
      for j=1: 1: Y
        distTemp=0;
        for k=1: 1: Z
          distTemp=distTemp+(datos(h,k)-nodos(i,j,k))^2;
        end
        distTemp=sqrt(distTemp);
        if distTemp<=BMU_dist
          BMU_dist=distTemp;
          BMU_X=i;
          BMU_Y=j;
        endif        
        end
    end
    radioW=BMU_X-floor(radio);
    radioE=BMU_X+floor(radio);
    radioN=BMU_Y-floor(radio);
    radioS=BMU_Y+floor(radio);
    
    if BMU_X-floor(radio) <1
      radioW=1;
    endif
    
    if BMU_X+floor(radio) >X
      radioE=X;
    endif
    
    if BMU_Y-floor(radio) <1
      radioN=1;
    endif
    
    if BMU_Y+floor(radio) >Y
      radioS=Y;
    endif
 
    LearningR=LearningRI*exp(-(epoca-1)/consTiem);
%      echo on
    for i=radioW: 1: radioE
      for j=radioN: 1: radioS
%        datosTest=datos(h,1:7)
%        pruebita2=datos(h,1:7).-nodos(i,j,:)
%        nodosTest=nodos(i,j,:)
%        vectorTest=(LearningR*((datos(h,1:7)-squeeze(nodos(i,j,:))').^2));
        for p=1:Z
          nodos(i,j,p)=nodos(i,j,p)+(LearningR*(datos(h,p)-nodos(i,j,p)));
        endfor
      end
    end
  end
end

%Clases

ocurrencia1 = zeros(X,Y);
ocurrencia2 = zeros(X,Y);
ocurrencia3 = zeros(X,Y);

for h=1: length(datos)
 BMU_dist=9999999; 
 for i=1: 1: X
   for j=1: 1: Y
     distTemp=0;
     for k=1: 1: Z
       distTemp=distTemp+(datos(h,k)-nodos(i,j,k))^2;
     end
     distTemp=sqrt(distTemp);
    if distTemp<=BMU_dist
      BMU_dist=distTemp;
      BMU_X=i;
      BMU_Y=j;
    endif    
   end
  end
    if datos(h,8)==1
      ocurrencia1(BMU_X,BMU_Y) = ocurrencia1(BMU_X,BMU_Y) + 1;
    endif
    if datos(h,8)==2
      ocurrencia2(BMU_X,BMU_Y) = ocurrencia2(BMU_X,BMU_Y) + 1;
    endif
    if datos(h,8)==3
      ocurrencia3(BMU_X,BMU_Y) = ocurrencia3(BMU_X,BMU_Y) + 1;
    endif
end
figure
imagesc(ocurrencia1), colormap(gray);
figure
imagesc(ocurrencia2), colormap(gray);
figure
imagesc(ocurrencia3), colormap(gray);
%%%%Clase1
[t,y_m]=max(max(ocurrencia1))
[t,x_m]=max(ocurrencia1)
x_m=x_m(y_m)
suma=ocurrencia1(x_m,y_m);

    if !(x_m-1 <1)
      suma=suma+ocurrencia1(x_m-1,y_m);
    endif

    if !(x_m+1 >X)
      suma=suma+ocurrencia1(x_m+1,y_m);
    endif
    
    if !(y_m-1 <1)
      suma=suma+ocurrencia1(x_m,y_m-1);
    endif
    
    if !(y_m+1 >Y)
      suma=suma+ocurrencia1(x_m,y_m+1);
    endif
 
 C1Efcy=suma/70
 
 %Clase2
 [t,y_m]=max(max(ocurrencia2))
[t,x_m]=max(ocurrencia2)
x_m=x_m(y_m)
suma=ocurrencia2(x_m,y_m);

    if !(x_m-1 <1)
      suma=suma+ocurrencia2(x_m-1,y_m);
    endif

    if !(x_m+1 >X)
      suma=suma+ocurrencia2(x_m+1,y_m);
    endif
    
    if !(y_m-1 <1)
      suma=suma+ocurrencia2(x_m,y_m-1);
    endif
    
    if !(y_m+1 >Y)
      suma=suma+ocurrencia2(x_m,y_m+1);
    endif
    
     C2Efcy=suma/70
    
    
    %CLASE3
    [t,y_m]=max(max(ocurrencia3))
[t,x_m]=max(ocurrencia3)
x_m=x_m(y_m)
suma=ocurrencia3(x_m,y_m);

    if !(x_m-1 <1)
      suma=suma+ocurrencia3(x_m-1,y_m);
    endif

    if !(x_m+1 >X)
      suma=suma+ocurrencia3(x_m+1,y_m);
    endif
    
    if !(y_m-1 <1)
      suma=suma+ocurrencia3(x_m,y_m-1);
    endif
    
    if !(y_m+1 >Y)
      suma=suma+ocurrencia3(x_m,y_m+1);
    endif

     C3Efcy=suma/70
     
     EficienciaGeneral=(C1Efcy+C2Efcy+C3Efcy)/3