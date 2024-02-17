%Evoluzione del moto di una corda data una forma iniziale
function Corda
    % parametri geometrici e fisici
    N = 101;
    L = 4*pi;
    %x = linspace(0,L,N);

    % valori psi(x,t) a t=0
    f = @(x)[sin(x)];
    psi_0 = feval(f,x);
    %psi_0 = normpdf(x);   
    psi_1 = x;
    psi_1(2:N-1) = 2*psi_0(2:N-1) + (0.09) * (psi_0(1:N-2)+psi_0(3:N)-2*psi_0(2:N-1));
    psi_n = x;

    for i=1:1000
    plot(x,psi_1);
    psi_0(N) = 0;
    psi_0(1) = 0;
    psi_1(N) = 0;
    psi_1(1) = 0;
    psi_n(N) = 0;
    psi_n(1) = 0;

    % evoluzione
    psi_n(2:N-1) = 2*psi_1(2:N-1) - psi_0(2:N-1) + (0.09)*(psi_0(3:N)+psi_0(1:N-2)-2*psi_0(2:N-1));        
    psi_1 = psi_n;
    psi_0 = psi_1;
    
    drawnow limitrate nocallbacks;
    end
end