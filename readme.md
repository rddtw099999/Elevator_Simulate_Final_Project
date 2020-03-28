

## Details

This is a micro controller course project  which emulated  method like elevator. This project using STM32E_EVAL  micro controller  and  use UART communicate between PC and Client


        VB Clients      <=====================>  STM32
         000000000                                000
          9 bits datas                           3 bits datas


*warranty if start and stop bit not all received than throw out all data and re-transfer again

Beep does in PC client





## Transfer rules
 STM32 First Transfer data to VB and than receive from VB
Otherwise,VB Receive and than transfer.

STM32 Client:

	bit       	   content

    1    		127 start bits
    2    		0 means up floor or 1 down floor
    3   		currentfloor bit
    4   		target floor bit
    5  			1f state    00
    6   		2f state    00  
    7   		3f state    10 means 3f up button clicked
    8  			4f state    11 means 4f down button clicked
    9   		126 stop bits

 PC Client

    bit
    1     connect flag

 just check if both PC and Client are connected
(![](https://i.imgur.com/JkGmBQd.png)
