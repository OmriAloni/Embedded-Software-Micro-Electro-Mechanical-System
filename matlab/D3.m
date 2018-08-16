function [yaw,roll,pitch] = D3()
global MyCOM
disp('3D');

global status; %% get out of the loop
status = 0;

%Cube generate
 A = [-4 -2.5 1];
 B = [4 -2.5 1];
 C = [-4 2.5 1];
 D = [-4 -2.5 -1];
 E = [-4 2.5 -1];
 F = [4 -2.5 -1];
 G = [4 2.5 1];
 H = [4 2.5 -1];
 P = [A;B;F;H;G;C;A;D;E;H;F;D;E;C;G;B];
 plot3(P(:,1),P(:,2),P(:,3),'g');% original cube
 axis([-10 10 -10 10 -10 10]);
 
tic;
while status == 0
    fprintf (MyCOM, 'D');
    pitchstr = fscanf (MyCOM, '%c', 7);
    yawstr = fscanf (MyCOM, '%c', 7);
    rollstr = fscanf (MyCOM, '%c', 7);
   
    pitch = deg2rad(str2double(pitchstr)/1000);
    roll = deg2rad(str2double(rollstr)/1000);
    yaw = deg2rad(str2double(yawstr)/1000);

    dcm = angle2dcm(yaw, pitch, roll);
    P1 = P*dcm;
    plot3(P1(:,1),P1(:,2),P1(:,3),'black') % rotated cube
    
    axis([-10 10 -10 10 -10 10]);
    patch( [P1(1,1),P1(2,1),P1(5,1),P1(6,1)],[P1(1,2),P1(2,2),P1(5,2),P1(6,2)],[P1(1,3),P1(2,3),P1(5,3),P1(6,3)],'red');
    patch( [P1(1,1),P1(2,1),P1(3,1),P1(8,1)],[P1(1,2),P1(2,2),P1(3,2),P1(8,2)],[P1(1,3),P1(2,3),P1(3,3),P1(8,3)],'black');
    patch( [P1(1,1),P1(6,1),P1(9,1),P1(8,1)],[P1(1,2),P1(6,2),P1(9,2),P1(8,2)],[P1(1,3),P1(6,3),P1(9,3),P1(8,3)],'black');
    patch( [P1(6,1),P1(5,1),P1(4,1),P1(1,1)],[P1(6,2),P1(5,2),P1(4,2),P1(1,2)],[P1(6,3),P1(5,3),P1(4,3),P1(1,3)],'black');
    patch( [P1(8,1),P1(9,1),P1(4,1),P1(3,1)],[P1(8,2),P1(9,2),P1(4,2),P1(3,2)],[P1(8,3),P1(9,3),P1(4,3),P1(3,3)],'blue');
    patch( [P1(2,1),P1(5,1),P1(4,1),P1(3,1)],[P1(2,2),P1(5,2),P1(4,2),P1(3,2)],[P1(2,3),P1(5,3),P1(4,3),P1(3,3)],'black');
    
    text(-7,17,15,  num2str(yaw));
    text(-7,17,13, num2str(pitch));
    text(-7,17,11, num2str(roll));

    grid on;
    ttt = toc;
    text(-7,17,9, num2str(ttt));
    tic; % Start a stopwatch timer
    drawnow;
 
end
