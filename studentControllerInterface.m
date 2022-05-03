classdef studentControllerInterface < matlab.System
    properties (Access = private)
        %% You can add values that you want to store and updae while running your controller.
        % For more information of the supported data type, see
        % https://www.mathworks.com/help/simulink/ug/data-types-supported-by-simulink.html
        t_prev = -1;
        theta_d = 0;
        Ts = 0.05;
        states = coder.load('mpc.mat').stateData;
        online = coder.load('mpc.mat').onlineData;
        mv = 0.0;
        u_buffer = zeros(1,3);
%         states_history = zeros(5,15/0.01);
        i = int32(1);
        plant0 = coder.load('plants.mat').p0;
        plant1 = coder.load('plants.mat').p1;
        plant2 = coder.load('plants.mat').p2;
    end

    methods(Access = protected)
        function setupImpl(obj)
            F = coder.load('mpc.mat');
            obj.states = F.stateData;
            obj.online = F.onlineData;
            
            F = coder.load('plants.mat');
            plant0 = F.p0;
            plant1 = F.p1;
            plant2 = F.p2;

            proj_dir = 'C:\Users\mw542\documents\ucb\me237\ball_and-beam-project-ee222';
            libPriority = '';
            libPreCompiled = true;
            libLinkOnly = true;
            libName = 'mpcmoveCodeGeneration.lib';
            libPath = [proj_dir];
            coder.updateBuildInfo('addLinkObjects', libName, libPath, ...
                 libPriority, libPreCompiled, libLinkOnly);
            coder.updateBuildInfo('addSourceFiles','mpcmoveCodeGeneration.c');
            coder.updateBuildInfo('addSourceFiles','mpcmoveCodeGeneration_initialize.c');
            coder.updateBuildInfo('addSourceFiles','mpcmoveCodeGeneration_terminate.c');
            
            
            incl_path = [proj_dir '\codegen\dll\mpcmoveCodeGeneration'];
            coder.updateBuildInfo('addIncludePaths', incl_path)
            coder.cinclude('mpcmoveCodeGeneration.h');
            coder.cinclude('mpcmoveCodeGeneration_initialize.h');
            coder.cinclude('mpcmoveCodeGeneration_terminate.h');
        end

        function V_servo = stepImpl(obj, t, p_ball, theta) %#codegen
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
            dt = t - obj.t_prev;
            V_servo = double(obj.mv);

            if dt >= obj.Ts*0.725
                % Extract reference trajectory at the current timestep.
                L = 40; % lookahead for traj
                offset = linspace(0, (L-1)*obj.Ts, L) - 3*obj.Ts;
                [p_ball_ref, ~, ~] = get_ref_traj(t+offset);
    
%                 [~, ~, A, B, C, D] = ball_and_beam_dynamics_linearized(obj.states.Plant(1:4), obj.mv);
%                 newPlant = struct('A', eye(5), 'B', zeros(5,1), 'C', zeros(2,5), 'D', zeros(2,1));
%                 newPlant = absorbDelay(c2d(ss(A,B,C,D,'InputDelay', 0.0045), obj.Ts));

                if theta > 50*pi/180
                    obj.online.model = obj.plant2;
                elseif theta < -50*pi/180
                    obj.online.model = obj.plant1;
                else
                    obj.online.model = obj.plant0;
                end
                
                obj.online.signals.ym = [p_ball; theta];
                obj.online.signals.ref = [p_ball_ref' zeros(size(p_ball_ref))'];
                
%                 info = struct('Uopt', zeros(1,4), 'Cost', 0.0, 'Iterations', 0, 'Slack', 0.0, 'Topt', [0,0,0], );
                coder.ceval("mpcmoveCodeGeneration_initialize");
                coder.ceval("mpcmoveCodeGeneration", coder.ref(obj.states), coder.ref(obj.online), coder.ref(V_servo));
                coder.ceval("mpcmoveCodeGeneration_terminate");
%                 [V_servo, obj.states] = mpcmoveMEX(0, obj.states, obj.online);
                obj.mv = V_servo;
                obj.t_prev = t;
            end
%             obj.states_history(:, obj.i) = obj.states.Plant;
            obj.i = obj.i + 1;    
        end   

        function resetImpl(obj)
            F = coder.load('mpc.mat');
            obj.t_prev = -1;
            obj.theta_d = 0;
            obj.Ts = 0.05;
            obj.states = F.stateData;
            obj.online = F.onlineData;
            obj.mv = 0.0;
            obj.u_buffer = zeros(1,3);
            obj.i = int32(1);
        end

        function releaseImpl(obj)
            obj.states = struct();
            pbj.online = struct();
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
