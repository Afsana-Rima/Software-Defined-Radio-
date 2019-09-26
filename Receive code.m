disp('This program shows the data available in the buffer after every 3 second ')
run=1;
while(run)
    if(s.bytesavailable~=0)
        pause(3)
        data=fread(s,s.bytesavailable);
        data1=rot90(data);
        sData=char(data1);
        disp(sData)
        pause(1.3)
    else
        disp('There are no Data in the buffer')
        chack=input('Do You Want to See Data Which Will be Received [Y/N] = ','s');
        if strcmp(chack,'Y')
            continue;
        else
            run=0;
        end
    end
end