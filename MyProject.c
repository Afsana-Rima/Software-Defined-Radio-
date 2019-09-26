char uart_rd,txt[12];
unsigned int i,k=0,renum;
unsigned long counter;
unsigned int numb,rnum;

void setupForS(){
     TRISC=0x00;
     CCP1CON=0b00001100;
     PWM1_Init(38000);
     PWM1_Set_Duty(50);
}

void setupForR(){
     ADCON1=0b00001111;
     INTCON.GIE=1;
     INTCON.PEIE=1;
     INTCON2.RBPU=1;
     PIE1.TMR2IE=1;
     PIR1.TMR2IF=0;
     PR2=255;
     T2CON.TMR2ON=0;
     TRISA=0xFF;
}

void sentData(unsigned int number){

     unsigned int pnum,i,digit[5];

     pnum=number;
     number=(number/10);
     digit[1]=(pnum-(number*10));
     digit[3]=(number/10);
     digit[2]=(number-(digit[3]*10));

     PWM1_Start();
     delay_us(2575);
     PWM1_Stop();
     Delay_us(100000);

     for (i=1;i<4;i++){

         if (digit[i]==0){
            PWM1_Start();
            delay_us(100);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==1){
            PWM1_Start();
            delay_us(325);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==2){
            PWM1_Start();
            delay_us(575);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==3){
            PWM1_Start();
            delay_us(825);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==4){
            PWM1_Start();
            delay_us(1075);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==5){
            PWM1_Start();
            delay_us(1325);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==6){
            PWM1_Start();
            delay_us(1575);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==7){
            PWM1_Start();
            delay_us(1825);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==8){
            PWM1_Start();
            delay_us(2075);
            PWM1_Stop();
            Delay_us(100000);
         }
         if (digit[i]==9){
            PWM1_Start();
            delay_us(2325);
            PWM1_Stop();
            Delay_us(100000);
         }
     }
}


void main() {
     UART1_Init(19200);
     Delay_ms(1000);

 while (1) {

   if (UART1_Data_Ready()) {
      uart_rd=UART1_Read();}

   if (uart_rd=='M'){
      UART1_Write('N');
      UART1_Write(10);
      uart_rd=0;
   }





   else if(uart_rd=='R'){                       ////**** RECEIVING MODE ****////
        uart_rd=0;
        setupForR();
        while(1){
                 if(UART1_Data_Ready()){
                 uart_rd=UART1_Read();}

                 if (uart_rd=='M'){
                    UART1_Write('R');
                    UART1_Write(10);
                    uart_rd=0;
                 }
                 else if (uart_rd=='R'){
                      uart_rd=0;
                      while (1) {
                            while(PORTA.RA1);
                            if (PORTA.RA0==1){
                               T2CON.TMR2ON=1;
                               counter=0;
                               TMR2=0;
                               while(!RA1_bit);
                               T2CON.TMR2ON=0;
                               counter = counter*256+TMR2;
                            }
                            if (5050<counter && counter <=5550){
                               renum=1;
                            }
                            while (renum==1) {
                                while(PORTA.RA1);
                                if(PORTA.RA1==0){
                                  T2CON.TMR2ON=1;
                                  counter=0;
                                  TMR2=0;
                                  while(!RA1_bit);
                                  T2CON.TMR2ON=0;
                                  counter = counter*256+TMR2;
                                  if(100<=counter && counter<=550){
                                   rnum=0;
                                  }
                                  else if (550<counter && counter <=1050){
                                  rnum=1;
                                  }
                                  else if (1050<counter && counter <=1550){
                                  rnum=2;
                                  }
                                  else if (1550<counter && counter <=2050)
                                  {
                                  rnum=3;
                                  }
                                  else if (2050<counter && counter <=2550)
                                  {
                                  rnum=4;
                                  }
                                  else if (2550<counter && counter <=3050)
                                  {
                                  rnum=5;
                                  }
                                  else if (3050<counter && counter <=3550)
                                  {
                                  rnum=6;
                                  }
                                  else if (3550<counter && counter <=4050)
                                  {
                                  rnum=7;
                                  }
                                  else if (4050<counter && counter <=4550)
                                  {
                                  rnum=8;
                                  }
                                  else if (4550<counter && counter <=5050)
                                  {
                                  rnum=9;
                                  }

                                  k++;

                                  if (k==1){
                                     numb=rnum;
                                  }
                                  else if (k==2){
                                       numb=rnum*10+numb;
                                  }
                                  else if (k==3){
                                      numb=rnum*100+numb;
                                      UART1_Write(numb);
                                      k=0;
                                      numb=0;
                                      renum=0;
                                  }
                                }
                            }
                      }
                 }
        }
    }






   else if(uart_rd=='S'){uart_rd=0;       ////**********SENDING MODE********////

       setupForS();

       while (1){
             if (UART1_Data_Ready()){
                uart_rd=UART1_Read();}

             if (uart_rd=='M'){
                UART1_Write('S');
                UART1_Write(10);
                uart_rd=0;
             }
             else if (uart_rd=='S'){uart_rd=0;

                  while (1){
                        if (UART1_Data_Ready()){
                           uart_rd=UART1_Read();
                           sentData(uart_rd);
                        }
                  }
             }
       }
    }
  }
}


void interrupt(){

     if (PIR1.TMR2IF==1){
        counter++;
        PIR1.TMR2IF=0;
     }
}