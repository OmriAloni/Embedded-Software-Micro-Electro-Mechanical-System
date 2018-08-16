function varargout = Comp(varargin)
% COMP MATLAB code for Comp.fig
%      COMP, by itself, creates a new COMP or raises the existing
%      singleton*.
%
%      H = COMP returns the handle to a new COMP or the handle to
%      the existing singleton*.
%
%      COMP('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in COMP.M with the given input arguments.
%
%      COMP('Property','Value',...) creates a new COMP or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Comp_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Comp_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Comp

% Last Modified by GUIDE v2.5 13-Aug-2018 13:04:00

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Comp_OpeningFcn, ...
                   'gui_OutputFcn',  @Comp_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before Comp is made visible.
function Comp_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Comp (see VARARGIN)

% Choose default command line output for Comp
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

clc; clear all;  % Clean all the ports and variables
delete(instrfindall);
movegui('northwest');

% UIWAIT makes Comp wait for user response (see UIRESUME)
% uiwait(handles.Main_Menu);

% --- Outputs from this function are returned to the command line.
function varargout = Comp_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in CompassBut.
function CompassBut_Callback(hObject, eventdata, handles)
    % hObject    handle to CompassBut (see GCBO)
    % eventdata  reserved - to be defined in a future version of MATLAB
    % handles    structure with handles and user data (see GUIDATA)
    
    global status; %% get out of the loop
    status = 1;
    run Compas_Temp.m;  

% --- Executes on button press in D3.
function D3_Callback(hObject, eventdata, handles)
% hObject    handle to D3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    global status; %% get out of the loop
    status = 1;
    run D3.m;


% --- Executes on button press in PaintBut.
function PaintBut_Callback(hObject, eventdata, handles)
% hObject    handle to PaintBut (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    
    global status; %% get out of the loop
    status = 1;
    run Paint.m;

% --- Executes on button press in Exitbut.
function Exitbut_Callback(hObject, eventdata, handles)
% hObject    handle to Exitbut (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global status;
status = 1;
clear ; close all; % Clean all the ports and variables
delete(instrfindall);
clc;

% --- Executes on button press in connectBUt.
function connectBUt_Callback(hObject, eventdata, handles)
% hObject    handle to connectBUt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA) 
    
%%CONNECTION %%
global MyCOM
MyCOM = serial('COM7', 'Baudrate', 115200); 
fopen(MyCOM);
disp('Connected');


% --- Executes on button press in Stop_But.
function Stop_But_Callback(hObject, eventdata, handles)
% hObject    handle to Stop_But (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    global status;
    status = 1;
    

% --- Executes during object creation, after setting all properties.
function Stop_But_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Stop_But (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes on button press in Move_But.
function Move_But_Callback(hObject, eventdata, handles)
% hObject    handle to Move_But (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    global status; %% get out of the loop
    status = 1;
    run Move.m;
