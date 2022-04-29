classdef studentControllerInterface < matlab.System
    properties (Access = private)
        %% You can add values that you want to store and updae while running your controller.
        % For more information of the supported data type, see
        % https://www.mathworks.com/help/simulink/ug/data-types-supported-by-simulink.html
        t_prev = -1;
        theta_d = 0;
        Ts = 0.05;
        config;
        states = struct('Plant', zeros(5,1),'Disturbance', [],'Noise',[],'LastMove',[],'Covariance',eye(5),'iA',false(172,1));
        online;
        mv = 0;
        u_buffer = zeros(1,3);
        states_history = zeros(5,15/0.01);
        i = int32(1);
    end
    methods(Access = protected)
        function setupImpl(obj)
            F = coder.load('mpc.mat');
            obj.config = F.configData;
            obj.states = F.stateData;
            obj.online = F.onlineData;
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
            coder.extrinsic('absorbDelay'); coder.extrinsic('tf'); coder.extrinsic('ss'); coder.extrinsic('c2d'); coder.extrinsic('mpcmoveMEX'); coder.extrinsic('mpcmoveCodeGeneration');

            t_prev = obj.t_prev;
            dt = t - t_prev;
            V_servo = obj.mv;
            if dt >= obj.Ts*0.725
                tic;

                % Extract reference trajectory at the current timestep.
                L = 40; % lookahead for traj
                offset = linspace(0, (L-1)*obj.Ts, L);
                [p_ball_ref, ~, ~] = get_ref_traj(t+offset);
    
%                 [~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized(obj.states.Plant(1:4), obj.mv);
%                 newPlant = struct('A', eye(5), 'B', zeros(5,1), 'C', zeros(2,5), 'D', zeros(2,1));
%                 newPlant = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.0045), obj.Ts));
%                 X = obj.states.Plant;
%                 U = obj.mv;
%                 Y = obj.states.Plant([1 3]);
%                 DX = newPlant.A*X + newPlant.B*U - X;
%                 newModel = struct('A', newPlant.A, 'B', newPlant.B, 'C', newPlant.C, 'D', newPlant.D,'X',X,'U',U,'Y',Y,'DX',DX);
%                 info = struct('Uopt', zeros(1,4));
%                 newplanttime = toc
                obj.online.signals.ym = [p_ball; theta];
                obj.online.signals.ref = [p_ball_ref' zeros(size(p_ball_ref'))];

%                 obj.online.model = newModel;
                           
                [V_servo, obj.states] = mpcmoveMEX(obj.config, obj.states, obj.online);
                toc
                obj.mv = V_servo;
                obj.t_prev = t;
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
