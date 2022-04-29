clear all; close all;

Ts = 0.05;
p = 40;     % Prediction horizon
m = 10;      % Control horizon
[~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;0;0], 0);
plant = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.001), Ts));

Weights = struct('MV',1,'MVRate',1, 'OV', [200 10]); % Weights
MV = struct('Min',-10,'Max',10,'RateMin',-100,'RateMax',100); % Input constraints
mpcobj = struct('OutputVariables', [struct('Min', 0, 'Max', 0) struct('Min', 0, 'Max', 0)]);
mpcobj = mpc(plant,Ts,p,m,Weights,MV);
mpcobj.OutputVariables(1).Min = -0.19;
mpcobj.OutputVariables(2).Min = -56*pi/180;
mpcobj.OutputVariables(1).Max = 0.19;
mpcobj.OutputVariables(2).Max = 56*pi/180;

mpcstate = mpcstate(mpcobj);
mpcstate.Plant = [-0.19;0;0;0;0];

[configData,stateData,onlineData] = getCodeGenerationData(mpcobj, 'InitialState', mpcstate,'IsAdaptive', false);
onlineData.signals.ref = zeros(p, 2);

% configData = coder.Constant(configData);

save('mpc.mat', 'configData','stateData', 'onlineData')

func = 'mpcmoveCodeGeneration';
funcOutput = 'mpcmoveMEX';
Cfg = coder.config('mex');
Cfg.DynamicMemoryAllocation = 'off';
codegen('-config',Cfg,func,'-o',funcOutput,'-args',...
    {coder.Constant(configData),stateData,onlineData});