%this is a test programme to send the matrix
%   A=[2 4 6; 1 3 5; 7 8 9]

done=0; 
while done~=1

if s.BytesAvailable~=0,fscanf(s);end    

fprintf(s,'M');
pause(1)
deviceMode=fgetl(s);

if strcmp(deviceMode,'N')
    disp('   Mode is not selected yet')
    typedMode=input('\n   To select Mode, Type [R/S]= ','s');
    fprintf(s,typedMode);
    
elseif strcmp(deviceMode,'R')
    fprintf(s,'R');
    pause(1)
    disp('Device is ready for receiving text')
    showing=1;
    while showing==1
    input('   Make sure that text has been transmitted completely!\n   To see received text press [Enter]');
    data=s.bytesavailable;
    if(data~=0)
        
        recievedData = fscanf(s);
        disp(recievedData)
        
    else
        
         disp('DATA IS NOT RECIEVED YET ! TRY AGAIN')   
        
    end
    asking=1;
        while asking==1
            comand=input('   Do you want to see any more Received text? [Y/N]=','s');
            if strcmp(comand,'Y')
                asking=0;
            elseif strcmp(comand,'N')
                disp('   Thank You')
                showing=0;
                done=1;
                asking=0;
            else
                disp('You entered a wrong text!')
            end
        end
    end
elseif strcmp(deviceMode,'S')
    
    typedCmd=input('\n\n   Make sure that the reciever is ready!\n\n   To send text press [Enter]');
    fprintf(s,'S');
    typing=1;
    while typing==1
        typedData=input('   Now Type the Text.\n   When typing is finished, press [Enter]\n','s');
        length=size(typedData,2);
        for k=1:length
            fwrite(s,typedData(k));
            pause(1)
        end
        asking=1;
        while asking==1
            comand=input('   Do you want to send any more text? [Y/N]=','s');
            if strcmp(comand,'Y')
                asking=0;
            elseif strcmp(comand,'N')
                disp('   Thank You')
                typing=0;
                done=1;
                asking=0;
            else
                disp('You entered a wrong text!')
            end
        end
    end
else
    disp('Either there is an error or The device is sending data'); 
    break;
end

end