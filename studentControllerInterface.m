classdef studentControllerInterface < matlab.System
    properties (Access = private)
        %% You can add values that you want to store and updae while running your controller.
        % For more information of the supported data type, see
        % https://www.mathworks.com/help/simulink/ug/data-types-supported-by-simulink.html
        t_prev = -0.01;
        p_prev = -0.19;
        theta_prev = 0;
        a_ball_ref_prev = 0;
        theta_d = 0;
    end
    methods(Access = protected)
        % function setupImpl(obj)
        %    disp("You can use this function for initializaition.");
        % end

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
            
            %% Tracking via feedback linearization
            t_prev = obj.t_prev;
            p_prev = obj.p_prev;
            theta_dprev = obj.theta_d;
            theta_prev = obj.theta_prev;
            a_ball_ref_prev = obj.a_ball_ref_prev;

            % extract reference trajectory at the current timestep.
            [p_ball_ref, v_ball_ref, a_ball_ref] = get_ref_traj(t);

            % compute speed and angular speed
            dt = t-t_prev;
            p_dot = (p_ball-p_prev)/dt;
            theta_dot = (theta-theta_prev)/dt;
            a_ref_dot = (a_ball_ref-a_ball_ref_prev)/dt;

            if t==0
                p_dot = 0;
                theta_dot = 0;
                a_ref_dot = 0;
            end;

% % Linearization controller 
%             % some constants;
            r = 0.0254;
            L = 0.4255;
            g = 9.81;
            K = 1.5;
            tau = 0.025;
% 
%             % compute states
%             x1 = p_ball;
%             x2 = p_dot;
%             x3 = theta;
%             x4 = theta_dot;
%             x2_dot = (5*g/7)*(r/L)*sin(x3) - (5/7)*(L/2-x1)*(r/L)^2*x4^2*(cos(x3))^2;
%             r = (5*g/7)*(r/L)*cos(x3)*x4 + (5/7)*x2*(r/L)^2*x4^2*(cos(x3))^2 + (5/7)*(L/2-x1)*(r/L)^2*x4^3*2*cos(x3)*sin(x3) + (5/7)*(L/2-x1)*(r/L)^2*(2/tau)*x4^2*(cos(x3))^2;
%             g = -(5/7)*(L/2-x1)*(r/L)^2*(2*K/tau)*x4*(cos(x3))^2;
% 
%             % the error dynamics
%             e = x1 - p_ball_ref;
%             e_d = x2 - v_ball_ref;
%             e_dd = x2_dot - a_ball_ref;
%             % the simple tracking rule
%             sum_err = -(e+3*e_d+3*e_dd);
%             u = (sum_err+a_ball_ref-r)/g;
%             V_servo = u;
%             theta_d = 0;


            % outer loop via crude linearization
%             k_c = 5.46;
%             z = 0.9;
%             theta_d = k_c*( z * (p_ball_ref - p_ball) - p_dot);
            
            %outer loop via partial ignoring higher order terms
            k_1 = 5; %5;
            k_2 = 3.5; %3.5;
            e_1 = p_ball - p_ball_ref;
            e_2 = p_dot - v_ball_ref;
            v = (a_ball_ref - k_1*e_1 - k_2*e_2)/0.42;
            v = max(v, -0.82);
            v = min(v, 0.82);
            theta_d = asin(v);


            % Make sure that the desired servo angle does not exceed the physical
            % limit. This part of code is not necessary but highly recommended
            % because it addresses the actual physical limit of the servo motor.
%             theta_saturation = 56 * pi / 180;
%             theta_d = min(theta_d, theta_saturation);
%             theta_d = max(theta_d, -theta_saturation);
            %theta_ddot = (theta_d - theta_dprev)/dt;

            % inner loop
            k_p = 13.5;
            k_v = 0.078;
            V_servo = k_p * (theta_d - theta) + k_v*(- theta_dot);

            % Update class properties if necessary.
            obj.t_prev = t;
            obj.p_prev = p_ball;
            obj.theta_d = theta_d;
            obj.theta_prev = theta;
            obj.a_ball_ref_prev = a_ball_ref;
            
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
