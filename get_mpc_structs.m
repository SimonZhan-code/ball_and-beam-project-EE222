clear all; close all;

Ts = 0.05;
p = 40;     % Prediction horizon
m = 20;      % Control horizon
[~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;0;0], 0);
plant = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.001), Ts));

Weights = struct('MV',5,'MVRate',20, 'OV', [100 0.01]); % Weights
MV = struct('Min',-10,'Max',10); % Input constraints
% mpcobj = struct('OutputVariables', [struct('Min', 0, 'Max', 0) struct('Min', 0, 'Max', 0)]);
mpcobj = mpc(plant,Ts,p,m,Weights,MV);
mpcobj.OutputVariables(1).Min = -0.17;
mpcobj.OutputVariables(2).Min = -56*pi/180;
mpcobj.OutputVariables(1).Max = 0.17;
mpcobj.OutputVariables(2).Max = 56*pi/180;
% setEstimator(mpcobj, 'custom');
% Y = struct('Weight',[1000,0],'Min',[-0.19,-56*pi/180],'Max',[0.19,56*pi/180]);
% U = struct('Min',-10, 'Max', 10);
% setterminal(mpcobj,Y,U)

mpcstate = mpcstate(mpcobj);
mpcstate.Plant = [-0.19;0;-56*pi/180;0;0];

[configData,stateData,onlineData] = getCodeGenerationData(mpcobj, 'InitialState', mpcstate,'IsAdaptive', true);
onlineData.signals.ref = zeros(p, 2);

save('mpc.mat', 'configData','stateData', 'onlineData')

func = 'mpcmoveCodeGeneration';
if false
    funcOutput = 'mpcmoveMEX';
    Cfg = coder.config('mex');
    Cfg.DynamicMemoryAllocation = 'off';
    Cfg.ConstantInputs = 'IgnoreValues';
    codegen('-config',Cfg,func,'-o',funcOutput,'-args',...
        {coder.Constant(configData),stateData,onlineData});
else
    Cfg = coder.config('lib');
    Cfg.DynamicMemoryAllocation = 'Off';
    codegen('-config',Cfg,func,'-args',...
        {coder.Constant(configData),stateData,onlineData});
end
copyfile("codegen\lib\mpcmoveCodeGeneration\mpcmoveCodeGeneration.lib", ".");

% [~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;50*pi/180;0], 0);
% plant = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.001), Ts));
% 
% Weights = struct('MV',5,'MVRate',20, 'OV', [100 0.01]); % Weights
% MV = struct('Min',-10,'Max',10); % Input constraints
% % mpcobj = struct('OutputVariables', [struct('Min', 0, 'Max', 0) struct('Min', 0, 'Max', 0)]);
% mpcobj = mpc(plant,Ts,p,m,Weights,MV);
% mpcobj.OutputVariables(1).Min = -0.19;
% mpcobj.OutputVariables(2).Min = -56*pi/180;
% mpcobj.OutputVariables(1).Max = 0.19;
% mpcobj.OutputVariables(2).Max = 56*pi/180;
% 
% 
% [configData1,stateData,onlineData] = getCodeGenerationData(mpcobj, 'InitialState', mpcstate,'IsAdaptive', false);
% onlineData.signals.ref = zeros(p, 2);
% 
% 
% [~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;-50*pi/180;0], 0);
% plant = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.001), Ts));
% 
% Weights = struct('MV',5,'MVRate',20, 'OV', [100 0.01]); % Weights
% MV = struct('Min',-10,'Max',10); % Input constraints
% 
% mpcobj = mpc(plant,Ts,p,m,Weights,MV);
% mpcobj.OutputVariables(1).Min = -0.19;
% mpcobj.OutputVariables(2).Min = -56*pi/180;
% mpcobj.OutputVariables(1).Max = 0.19;
% mpcobj.OutputVariables(2).Max = 56*pi/180;
% 
% 
% [configData2,stateData,onlineData] = getCodeGenerationData(mpcobj, 'InitialState', mpcstate,'IsAdaptive', false);
% onlineData.signals.ref = zeros(p, 2);
