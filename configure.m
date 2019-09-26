clear s;
COMPort=input('Type COM Port e.g COM1,COM2 ... \n','s');
disp('Establishing Connection.Please Wait ...')
s=serial(COMPort,'BaudRate',19200);
if strcmp(s.Status,'closed'), fopen(s); end
disp(['Selected COM Port is ',COMPort]);
