function [dxdt, y, A, B, C, D] = ball_and_beam_dynamics_linearized(x, u)
%% parameters
r_g = 0.0254;
L = 0.4255;
g = 9.81;
K = 10;
tau = 0.1;

% y
y = [1 0 0 0; 0 0 1 0]*x;
%% Compute dxdt
dxdt = x;
% z_dot
dxdt(1) = x(2);
% z_dot_dot
dxdt(2) = 5*g/7*r_g/L*sin(x(3)) - 5/7*(L/2 - x(1))*(r_g/L)^2*x(4)^2*(cos(x(3)))^2;
% theta_dot
dxdt(3) = x(4);
% theta_dot_dot
dxdt(4) = -x(4)/tau + K/tau*u;

% used by A
ddx2dx1 = 5/7*(r_g/L)^2*x(4)^2*(cos(x(3)))^2;
ddx2dx3 = 5*g/7*r_g/L*cos(x(3)) + 10/7*(L/2 - x(1))*(r_g/L)^2*x(4)^2*sin(2*x(3));
ddx2dx4 = -10/7*(L/2 - x(1))*(r_g/L)^2*x(4)*(cos(x(3)))^2;

ddx4dx4 = -1.0/tau;
% used by B
ddx4du = K/tau;
% LTI
A = [0 1 0 0
     ddx2dx1 0 ddx2dx3 ddx2dx4
     0 0 0 1
     0 0 0 ddx4dx4];
B = [0;0;0;ddx4du];
C = [1 0 0 0; 0 0 1 0];
D = zeros(2,1);

