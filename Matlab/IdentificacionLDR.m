clc
clear variables
close all

Ts = 0.05; %periodo de muestreo en segundos
tf = 5; %tiempo de simulacion en segundos

t = 0:Ts:tf;

ta = 1;
% Señal escalon de 0 a 20 unidades en 5 segundos
for k = 1: numel(t)
    if(k*Ts > ta)
        u(k)=20;
    else
        u(k) =0;
    end
end

com = 'COM8';
delete(instrfind({'Port'},{com}));
port = serial(com);
set(port,'Baudrate',9600);
set(port,'StopBits',1);
set(port,'DataBits',8);
set(port,'Parity','none');
set(port,'Terminator','CR/LF');
set(port,'OutputBuffersize',200);
set(port,'InputBuffersize',200);
set(port,'Timeout',5);

fopen(port);

pause(5);

for k=1:length(t)
    tic
    fprintf(port,'%s\n',num2str(u(k)),'sync');
   y(k) = fscanf(port,'%i\n');

    while toc < Ts
    end
end

fclose(port)
delete(port)

plot(t,y,'b'), hold on
plot(t,u,'r')
xlabel('Time (s)'), ylabel('%')
legend('Y','U'),grid on
%% Almacenar los datos capturados

U = u'; %Input
Y = y'; %output
save('DataLDR2','U','Y');
%% Identificar el modelo
indent
systemIdentification
%% Almacenar función  de transferencia
save('Transfer_function_LDR')
%% Sintonizar ganancias PID
pidtool
%% Convertir la planta tiempo discreto
c2d(C,0.05,'tustin')

