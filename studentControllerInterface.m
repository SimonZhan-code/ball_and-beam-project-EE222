classdef studentControllerInterface < matlab.System
    properties (Access = private)
        %% You can add values that you want to store and updae while running your controller.
        % For more information of the supported data type, see
        % https://www.mathworks.com/help/simulink/ug/data-types-supported-by-simulink.html
        t_prev = -1;
        theta_d = 0;
        extra_dummy1 = 0;
        extra_dummy2 = 0;
        Ts = 0.1;
        mpcobj = struct('OutputVariables', [struct('Min', 0, 'Max', 0) struct('Min', 0, 'Max', 0)]);
        states = struct('Plant', [0;0;0;0], 'Disturbance', [], 'Noise', [], 'LastMove', [], 'Covariance', eye(4));
        mv = 0;
        u_buffer = zeros(1,3);
        mpc_time = 0.045;
        states_history = zeros(4,15/0.01);
        i = int32(1);
    end
    methods(Access = protected)
        function setupImpl(obj)
            coder.extrinsic('setoutdist'); coder.extrinsic('tf'); coder.extrinsic('ss'); coder.extrinsic('mpc'); coder.extrinsic('mpcstate'); coder.extrinsic('c2d');
            p = 30;     % Prediction horizon
            m = 3;      % Control horizon
            [~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized([0;0;0;0], 0);
            plant = c2d(ss(A,B,C,D), obj.Ts);

            Weights = struct('MV',25,'MVRate',2, 'OV', [250 5]); % Weights
            MV = struct('Min',-10,'Max',10,'RateMin',-100,'RateMax',100); % Input constraints
            obj.mpcobj = struct('OutputVariables', [struct('Min', 0, 'Max', 0) struct('Min', 0, 'Max', 0)]);
            obj.mpcobj = mpc(plant,obj.Ts,p,m,Weights,MV);
            obj.mpcobj.OutputVariables(1).Min = -0.19;
            obj.mpcobj.OutputVariables(2).Min = -56*pi/180;
            obj.mpcobj.OutputVariables(1).Max = 0.19;
            obj.mpcobj.OutputVariables(2).Max = 56*pi/180;

            obj.states = struct('Plant', [0;0;0;0], 'Disturbance', [], 'Noise', [], 'LastMove', [], 'Covariance', eye(4));
            obj.states = mpcstate(obj.mpcobj);
            obj.states.Plant = [-0.19;0;0;0];
%             setoutdist(obj.mpcobj,'model',tf(zeros(2,1)))
            obj.mv = 0;
        end

        function V_servo = stepImpl(obj, t, p_ball, theta)
        % This is the main function called every iteration. You have to implement
        % the controller in this function, bu you are not allowed to
        % change the signature of this function. 
        % Input arguments:
        %   t: current time
        %   p_ball: position of the ball provided by the ball position sensor (m)
        %
        %   theta: servo motor angle provided by the encoder of the motor (rad)
        % Output:
        %   V_servo: voltage to the servo input.  
            tic;
            coder.extrinsic('tf'); coder.extrinsic('ss'); coder.extrinsic('mpc'); coder.extrinsic('mpcstate'); coder.extrinsic('c2d'); coder.extrinsic('mpcmoveAdaptive');
            if t <= 0
                obj.setupImpl();
            end
            t_prev = obj.t_prev;
            % Extract reference trajectory at the current timestep.
            L = 30; % lookahead for traj
            [p_ball_ref, v_ball_ref, ~] = get_ref_traj(t:obj.Ts:t+obj.mpc_time+L*obj.Ts);
%             [p_ball_ref, v_ball_ref, ~] = get_ref_traj(t);

            dt = t - t_prev; % add delay for simulink??
            V_servo = obj.mv;
            if dt >= obj.Ts - obj.mpc_time
                [~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized(obj.states.Plant, obj.mv);
                newPlant = struct('A', eye(4), 'B', zeros(4,1));
                newPlant = c2d(ss(A,B,C,D), obj.Ts);
                X = obj.states.Plant;
                U = obj.mv;
                Y = obj.states.Plant([1 3]);
                DX = newPlant.A*X+newPlant.B*U - X;
                newNominal = struct('U',U,'Y',Y,'X',X,'DX',DX);
                
                info = struct('Uopt', zeros(1,4));
                [V_servo, info] = mpcmoveAdaptive(obj.mpcobj, obj.states, newPlant, newNominal, [p_ball; theta], [p_ball_ref' zeros(size(p_ball_ref'))], 0);
                obj.u_buffer = info.Uopt(1:3);
                obj.mv = V_servo;
                obj.t_prev = t;
                mpc_time = toc
                obj.mpc_time = 0.8*obj.mpc_time + 0.2*mpc_time;
            end
            obj.states_history(:, obj.i) = obj.states.Plant;
            obj.i = obj.i + 1;
            % Update class properties if necessary.
            obj.theta_d = obj.states.Plant(3);

        end
    end
    
    methods(Access = public)
        % Used this for matlab simulation script. fill free to modify it as
        % however you want.
        function [V_servo, theta_d] = stepController(obj, t, p_ball, theta)        
            V_servo = stepImpl(obj, t, p_ball, theta);
            theta_d = obj.theta_d;
        end
    end
    
end
