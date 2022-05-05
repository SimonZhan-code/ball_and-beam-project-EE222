classdef studentControllerInterface < matlab.System
    properties (Access = private)
        %% You can add values that you want to store and updae while running your controller.
        % For more information of the supported data type, see
        % https://www.mathworks.com/help/simulink/ug/data-types-supported-by-simulink.html
        nn = 8;
        t_prev = -0.01;
        p_prev = -0.19;
        p_prevs = zeros(1,8);
        theta_prevs = zeros(1,8);
        theta_prev = 0;
        a_ball_ref_prev = 0;
        V_prev = 0;
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
            nn = obj.nn;
            t_prev = obj.t_prev;
            p_prev = obj.p_prev;
            p_prevs = obj.p_prevs;
            theta_prevs = obj.theta_prevs;
            theta_dprev = obj.theta_d;
            V_prev = obj.V_prev;
            theta_prev = obj.theta_prev;
            a_ball_ref_prev = obj.a_ball_ref_prev;

            % extract reference trajectory at the current timestep.
            [p_ball_ref, v_ball_ref, a_ball_ref] = get_ref_traj(t);
            
            %alpha = 0.6;
            eps = 0.5;
            % scaling
            if p_ball_ref > 0.06
                p_ball_ref = 0.06;
                
            end
            v_ball_ref = eps*v_ball_ref;
            a_ball_ref = eps*a_ball_ref;
%             p_ball_ref = alpha*p_ball_ref;
%             v_ball_ref = alpha*v_ball_ref;
%             a_ball_ref = alpha*a_ball_ref;
            
            % add noise
%             p_ball = p_ball + 0.0002*randn(1);
%             theta = theta + 0.05*randn(1);
            
            % filter
%             zeta = 0.2;
%             p_ball = p_ball*zeta + p_prev*(1-zeta);
%             theta = theta*zeta + theta_prev*(1-zeta);
            p_ball = mean([p_prevs, p_ball]);
            theta = mean([theta_prevs, theta]);

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

            %outer loop via partial ignoring higher order terms
            k_1 = 2; %5;
            k_2 = 1.5; %3.5;
            e_1 = p_ball - p_ball_ref;
            e_2 = p_dot - v_ball_ref;
            v = (a_ball_ref - k_1*e_1 - k_2*e_2)/0.42;
            v = max(v, -0.82);
            v = min(v, 0.82);
            theta_d = asin(v);
            theta_dd = (theta_d-theta_dprev)/dt;

            % inner loop
            k_p = 2.6;
            k_v = 0.003;
            V_servo = k_p * (theta_d - theta) + k_v*(theta_dd- theta_dot);
            beta = 0.3;
            V_servo = V_servo*beta + V_prev*(1-beta);

            % Update class properties if necessary.
            obj.t_prev = t;
            obj.p_prev = p_ball;
            for i = 1:(nn-1)
                obj.p_prevs(i) = p_prevs(i+1);
            end
            obj.p_prevs(nn) = p_ball;
            obj.theta_d = theta_d;
            obj.theta_prev = theta;
            for i = 1:(nn-1)
                obj.theta_prevs(i) = theta_prevs(i+1);
            end
            obj.theta_prevs(nn) = theta;
            obj.a_ball_ref_prev = a_ball_ref;
            obj.V_prev = V_servo;
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
