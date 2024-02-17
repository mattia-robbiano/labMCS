%Evoluzione temporale barra di metallo con un impulso di calore al centro

function HeatScheme

    % Parametri fisici
    eta = 0.2; L = 0.5; kappa = 10;

    % Delta x, Delta t
    N = 101;
    x = linspace(0.0,L,N);
    dx = x(2)-x(1); dt = (eta*dx^2)/kappa;

    % Impulso di calore iniziale
    T0 = 20; DeltaT = 80;
    T = ones(N,1)*T0; T((N-1)/2+1) = T0+DeltaT;

    % Evoluzione
    t = 0;
    tend = 1000*dt;
    T_temp = ones(N-2,1)*T0;
    A = inv(eye(N-2,N-2)*((2/eta)+2)-diag(ones(1,N-3),1)-diag(ones(1,N-3),-1));
    while t<tend

        % Cranck-Nicholson o inv. matrice
        T_temp(1,1) = T0 + T(1,1)+T(2,1)*((2/eta)-2)+T(3,1);
        T_temp(2:N-3,1) = T(2:N-3,1) + T(3:N-2,1)*((2/eta)-2) + T(4:N-1,1);
        T_temp(N-2,1) = T0+T(N-2,1)+T(N-1,1)*((2/eta)-2)+T(N,1);
        T(2:N-1,1) = A * T_temp;

        %Disegno funzione teorica
        f = @(x,t)[(1/(sqrt(2*pi)*sqrt(2*kappa*t)))*exp(-((x-x((N-1)/2+1)).^2)/(24*kappa*t))];
        y = f(x,t);

        plot(x,y,"r");
        plot(x,T,"b");
        drawnow limitrate nocallbacks
        pause(0.001);
        t = t+dt;
    end
end
