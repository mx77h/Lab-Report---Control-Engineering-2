function [y] = PT1T(x, t)   
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
Umag = 5;
K = x(1);
tau = x(2);
T = x(3);

y = Umag*K*(1-exp((-1/tau)*(t-T))).*heaviside(t-T);

end

