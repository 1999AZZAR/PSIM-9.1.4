function varargout = PSimDialog(varargin)
% PSIMDIALOG M-file for PSimDialog.fig
%      PSIMDIALOG, by itself, creates a new PSIMDIALOG or raises the existing
%      singleton*.
%
%      H = PSIMDIALOG returns the handle to a new PSIMDIALOG or the handle to
%      the existing singleton*.
%
%      PSIMDIALOG('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PSIMDIALOG.M with the given input arguments.
%
%      PSIMDIALOG('Property','Value',...) creates a new PSIMDIALOG or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before PSimDialog_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to PSimDialog_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help PSimDialog

% Last Modified by GUIDE v2.5 22-Nov-2005 14:19:23

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @PSimDialog_OpeningFcn, ...
                   'gui_OutputFcn',  @PSimDialog_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin & isstr(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before PSimDialog is made visible.
function PSimDialog_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to PSimDialog (see VARARGIN)

% Choose default command line output for PSimDialog
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);
set(handles.PSimFileEdt, 'String', get_param(gcbh, 'Parameters'));
set(handles.sBack, 'String', get_param(gcbh, 'Parameters'));
% UIWAIT makes PSimDialog wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = PSimDialog_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes during object creation, after setting all properties.
function PSimFileEdt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to PSimFileEdt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function PSimFileEdt_Callback(hObject, eventdata, handles)
% hObject    handle to PSimFileEdt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of PSimFileEdt as text
%        str2double(get(hObject,'String')) returns contents of PSimFileEdt as a double


% --- Executes on button press in BrowseBtn.
function BrowseBtn_Callback(hObject, eventdata, handles)
% hObject    handle to BrowseBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
SimCoupler(100, get(handles.PSimFileEdt, 'String'));
%[filename, pathname] = uigetfile({'*.sch','PSim Files (*.sch)';'*.*', 'All Files (*.*)'}, 'Choose a PSIM File');
%ss1 = ['''', pathname, filename, ''''];
set(handles.PSimFileEdt, 'String', get_param(gcbh, 'Parameters'));

% --- Executes on button press in ShowCircuitBtn.
function ShowCircuitBtn_Callback(hObject, eventdata, handles)
% hObject    handle to ShowCircuitBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
SimCoupler(105, get(handles.PSimFileEdt, 'String'));


% --- Executes on button press in CloseBtn.
function CloseBtn_Callback(hObject, eventdata, handles)
% hObject    handle to CloseBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close;


% --- Executes on button press in ApplyBtn.
function ApplyBtn_Callback(hObject, eventdata, handles)
% hObject    handle to ApplyBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%set_param(gcbh, 'Parameters', get(handles.PSimFileEdt, 'String'));
SimCoupler(101, get(handles.PSimFileEdt, 'String'));



% --- Executes on button press in CancelBtn.
function CancelBtn_Callback(hObject, eventdata, handles)
% hObject    handle to CancelBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
sOld = get(handles.sBack, 'String');
set_param(gcbh, 'Parameters', sOld);
if (strcmp(sOld, ''''''))
    set_param(gcbh, 'name', 'SimCoupler')
    set_param(gcbh, 'MaskDisplay', 'plot(-60,-60,60,60,x1,y1,x2,y2)');
end
close;


% --- Executes during object creation, after setting all properties.
function sBack_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sBack (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function sBack_Callback(hObject, eventdata, handles)
% hObject    handle to sBack (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sBack as text
%        str2double(get(hObject,'String')) returns contents of sBack as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


