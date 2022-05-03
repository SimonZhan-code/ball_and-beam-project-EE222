
[~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;0;0], 0);

p = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.001), 0.05))

X = [0;0;0;0;0];
U = 0;
Y = [0;0];
DX = p.A*X + p.B*U - X;
p0 = struct('A',p.A,'B',p.B,'C',p.C,'D',p.D,'X',X,'U',U,'Y',Y,'DX',DX);

[~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;-10*pi/180;0], 0);

p = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.001), 0.05))

X = [0;0;-10*pi/180;0;0];
U = 0;
Y = [0;-10*pi/180];
DX = p.A*X + p.B*U - X;
p1 = struct('A',p.A,'B',p.B,'C',p.C,'D',p.D,'X',X,'U',U,'Y',Y,'DX',DX);

[~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;10*pi/180;0], 0);

p = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.001), 0.05))

X = [0;0;10*pi/180;0;0];
U = 0;
Y = [0;10*pi/180];
DX = p.A*X + p.B*U - X;
p2 = struct('A',p.A,'B',p.B,'C',p.C,'D',p.D,'X',X,'U',U,'Y',Y,'DX',DX);
save('plants.mat', 'p0', 'p1', 'p2')