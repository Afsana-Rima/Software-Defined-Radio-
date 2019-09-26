%this is a test programme to send the matrix
%   A=[2 4 6; 1 3 5; 7 8 9]

COMPort=input('Type COM Port e.g COM1,COM2 ... \n','s');
disp('Establishing Connection.Please Wait ...')
s=serial(COMPort,'BaudRate',19200);
if strcmp(s.Status,'closed'), fopen(s); end
disp(['Selected COM Port is ',COMPort]);
 
    
if s.BytesAvailable~=0,fscanf(s);end    
fprintf(s,'M');
deviceMode=fscanf(s);

if strcmp(deviceMode,'N')
    disp('Mode is not selected yet')
    typedMode=input('\n Type [R/S]= ','s');
    fprintf(s,typedMode);
    deviceMode=fscanf(s);
    massage=sprintf('Your selected mode is = %s \n Mode in the device is = %s \n',typedMode,deviceMode);
    clear typedMode;

elseif strcmp(deviceMode,'R')
    disp('Device in this computer is in Receiving Mode')
    typedCmd=input('\n To receive data Press [R]= ','s');
    fprintf(s,typedCmd);
    clear typedCmd;
    disp('Now Sender have to Press S');
    Here 
    if s.BytesAvailable<2,goto Here;disp('s'),end
    
    sizeofB=fread(s,2);
    for i=1:sizeofB(1)
        for j=1:sizeofB(2)
            B(i,j)=fread(s,1);
        end
    end
    
elseif strcmp(deviceMode,'S')
    disp('Device in this computer is in Sending Mode')
    typedCmd=input('\n To send data Press [S]= ','s');
    fprintf(s,typedCmd);
    clear typedCmd;
    A=[2 4 6; 1 3 5; 7 8 9];
    fwrite(s,size(A,1));
    fwrite(s,size(A,2));
    for i=1:size(A,1)
        for j=1:size(A,2)
            verify=A(i,j);
            if verify>255
                disp('Unsupported Matrix! Values must be less than 255');
                break;
            end
            fwrite(s,A(i,j));
        end
    end
       
end


fclose(s)
delete(s)
clear all