% x0 = [4 0.05 0.1];
% X = lsqcurvefit(@PT1T, x0, t,y)

t1 = resp_12V.time(:,1);
y1 = resp_12V.signals(1).values(:,1);
y1 = y1/9.55;



x0 = [25 0.004 0.005]
X = lsqcurvefit(@PT2, x0, t1, y1)
sys = tf(X(1), conv([X(2), 1], [X(3) 1]))
step(sys*12)
hold on
plot(t1, y1, 'r')

integrator = tf(1, [1 0]);
G = series(integrator, sys)

pole(G)
figure
rlocus(G)

pcr = 0.175701;
kcr = 325; %aus root locus
kp = 0.6*kcr

Ti = 0.5*pcr;
Td = 0.125*pcr;


ki = kp/Ti
kd = Td*kp

Ts = 0.0001;

