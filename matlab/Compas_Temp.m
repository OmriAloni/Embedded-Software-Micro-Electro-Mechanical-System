function [ya] = Compas_Temp()
%%Connection%%
global MyCOM
disp('Comp&Temp');

global status; %% get out of the loop
status = 0;

while status == 0
    fprintf(MyCOM,'C'); %% C for Compass sent to the bakar
    compasss = fscanf (MyCOM, '%c', 7); %% get yaw from bakar
    tempstr = fscanf (MyCOM, '%c', 7); %% get temp from bakar
    
    temp=str2double(tempstr)/1000; %% convert to number
    yaw = str2double(compasss)/1000+180;
    yaw = deg2rad(yaw); %%convert to radian for compass func
    
    x = cos(yaw);
    y = sin(yaw);
    compass(x,y);
    
    text(-1.3,-1.3, 'Temperature', 'fontsize',16) 
    text(-0.5,-1.3, num2str(temp),'fontsize',24);
    
    drawnow;
end
ya = yaw