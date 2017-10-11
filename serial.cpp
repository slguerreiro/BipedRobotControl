#include "stdafx.h"


/* ..................................................................
Unit:         serial.c
Date:         96.May.30
Author:       Vitor Sequeira (viseq)
Revision:     1.0
			  1.1  viseq  96.August.16
Comments:
Notes:        This file contains some routines to deal with com ports.
              NT version
   .................................................................. */

#include    <windows.h>
#include    <stdio.h>
#include    <time.h>
#include    "serial.h"


/* ..................................................................
Function:     InitComPort()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Initialize a serial port
Arguments:    port       port number
              baud       baud rate
              parity     parity
              data       number of data bits
              stop       number of stop bits
Returns:      serial port handle
              1 - 5 : invalid value in parameter number...
Calls:        
Notes:        .acceptable values for 'baud':
                                            0, 11, 110   -   110 baud
                                            1, 15, 150   -   150 baud
                                            2, 30, 300   -   300 baud
                                            3, 60, 600   -   600 baud
                                            4, 12, 1200  -  1200 baud
                                            5, 24, 2400  -  2400 baud
                                            6, 48, 4800  -  4880 baud
                                            7, 96, 9600  -  9600 baud
											9,192,19200  - 19200 baud

              .acceptable values for 'parity':
                                            0, 'n', 'N' - no parity
                                            1, 'o', 'O' - odd parity
                                            2, 'e', 'E' - even parity

              .acceptable values for 'data':
                                            0, 5 - five data bits
                                            1, 6 - six data bits
                                            2, 7 - seven data bits
                                            3, 8 - eight data bits

              .acceptable values for 'stop':
                                            1 - one stop bit
                                            2 - two stop bits

   .................................................................. */
HANDLE InitComPort(int port, int baud,int  parity,int data,int stop )
//int  port, baud, parity, data, stop ;
{
HANDLE hCom;
char	aux_port[8];
FILE * report;
report = fopen("report.txt","at");
   
   switch( port )
   {
      case  COM1 : strcpy(aux_port, "COM1");
				   break;
      case  COM2 : strcpy(aux_port, "COM2");
				   break;
	  case  COM3 : strcpy(aux_port, "COM3");
				   break;
      case  COM4 : strcpy(aux_port, "COM4");
				   break;
	  case  COM5 : strcpy(aux_port, "COM5");
				   break;

	  case  COM6 : strcpy(aux_port, "COM6");
				   break;
	  default : fprintf(report,"port %d not supported\n", port);
				exit(0);
				   // default    : return( 1 ) ;
    }
   switch( baud )
   {
      case  192 :
	  case    8 :	baud = 19200;
      case 19200 : break;
      
      case   96 :
      case    7 :	baud = 9600;
      case 9600 : break;

      case   48 :
      case    6 :   baud = 4800; 
      case 4800 : break;

      case   24 :
      case    5 :   baud = 2400; 
      case 2400 : break;

      case   12 :
      case    4 :   baud = 1200; 
      case 1200 : break;

      case   60 :
      case    3 :   baud = 600;
      case  600 : break;

      case   30 :
      case    2 :   baud = 300;
      case  300 : break;

      case   15 :
      case    1 :   baud = 150;
      case  150 : break;

      case   11 :
      case    0 :   baud = 110;
      case  110 : break ;

      // default   : return( 2 ) ;
    }
   switch( parity )
   {
      case 'n' :
      case 'N' : 
      case  0  : parity = NOPARITY ;
					break ;

      case 'o' :
      case 'O' : 
      case  1  : parity = ODDPARITY ;
					break ;

      case 'e' :
      case 'E' : 
      case  2  : parity = EVENPARITY ;
					break ;


      // default: return( 3 ) ;
    }
   switch( data )
   {
      case 0 : data = 5 ;
      case 5 : break ;

      case 1 : data = 6 ;
      case 6 : break ;

      case 2 : data = 7 ;
      case 7 : break ;

      case 3 : data = 8 ;
      case 8 : break ;

      // default: return( 4 ) ;
    }
   switch( stop )
   {
      case  1 : stop=ONESTOPBIT;
					break;
      case  2 : stop=TWOSTOPBITS;
				    break ;
      // default : return( 5 ) ;
    }

   hCom=ConfigureSerialPort(aux_port, baud, parity, stop, data);
   if (hCom == INVALID_HANDLE_VALUE) {
      /* handle error */
	fprintf(report,"Error Init comport: %s, %d, %d, %d\n", aux_port,baud,parity,stop,data);
}
fclose(report);
   return( hCom ) ;
 }


/* ..................................................................
Function:     CloseComPort()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Closes a serial port
Arguments:    hCom      Serial port handler
Returns:      
Calls:
Notes:        
       -----> .DO NOT FORGET to close all opened ports before exiting. Failing
              to do so may crash your system.
   .................................................................. */

BOOL CloseComPort(HANDLE hCom)

{
	BOOL fCloseStat;
	fCloseStat=CloseHandle(hCom);

	return(fCloseStat);
}


/* ..................................................................
Function:     OutQueueSize()
Date:         92.Aug.03
Author:       Vitor Sequeira
Comments:     Return the number of bytes waiting in the output queue
Arguments:    port      port number
Returns:      no. of bytes waiting to be trandmitted in the output queue
              if -1, either port number is invalid or port is not open
Calls:        
Notes:        Not yet implemented
   .................................................................. */
int  OutQueueSize(int port )
//int  port ;
{
   int   size ;

   size=0;
return(size);
 }


/* ..................................................................
Function:     InputQueueSize()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Return the number of bytes remaining in the input queue
Arguments:    port      port number
Returns:      no. of bytes waiting to be retreived from the input queue
              if -1, either port number is invalid or port is not open
              if -2, the queue filled up and bytes may have been lost
Calls:        
Notes:        Not yet implemented
   .................................................................. */
int  InputQueueSize(int port )
//int  port ;
{
   int   size;

   size=0;
return(size);
 }


/* ..................................................................
Function:     ReadComByte()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Read a byte from a serial port
Arguments:    hCom         serial port Handle
              byte         byte read from port
              remain       no. of bytes remaining in the input queue
              status       port status word
Returns:      
Calls:
Notes:        
   .................................................................. */
BOOL ReadComByte(HANDLE hCom, char *byte, int *remain, int *status)
{
BOOL fReadStat;
LPVOID	ch;
DWORD	len=1;
char	b1;

ch='\0';
fReadStat=ReadComBlock(hCom, &ch, &len);

b1=(char)ch;

*byte=b1;
*remain=len;

return (fReadStat);
}


/* ..................................................................
Function:     ReadComBlock()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Read a block of bytes from a serial port
Arguments:              
Returns:      
Calls:
Notes:        
                 .................................................................. */

BOOL ReadComBlock(HANDLE hCom, LPVOID *lpszBlock, DWORD *dwLength)
{
BOOL fReadStat;

DWORD len=1;

DWORD time1;

time1 = GetTickCount();

while ( (GetTickCount()-time1) < 2	);

fReadStat = ReadFile( hCom, lpszBlock,
		                    *dwLength, dwLength, NULL ) ;

if (!fReadStat) {
    /* Handle the error. */
	printf("ReadComBlock:Error in Reading\n");
	
}

return (fReadStat);
}

/* ..................................................................
Function:     WriteComByte()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Write a byte to a serial port
Arguments:    
              byte         byte to write to port
Returns:      
Calls:
Notes:       
   .................................................................. */

BOOL WriteComByte(HANDLE hCom, char byte)
{
BOOL fWriteStat;
DWORD dwLength;
LPSTR dwBuffer;

dwBuffer[0]=byte;

dwLength=1;

fWriteStat = WriteFile( hCom, dwBuffer,
		                    dwLength, &dwLength, NULL ) ;

if (!fWriteStat) {
    /* Handle the error. */
	printf("WriteComByte:Error in Writing\n");
}

return (fWriteStat);
}



/* ..................................................................
Function:     WriteComBlock()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Write a block of bytes to a serial port
Arguments:    
Returns:      
Calls:
Notes:        
   .................................................................. */
BOOL WriteComBlock(HANDLE hCom, LPSTR dwBuffer, DWORD dwLength)
{
BOOL fWriteStat;
FILE * report = fopen("report.txt","at");
fWriteStat = WriteFile( hCom, dwBuffer,
		                    dwLength, &dwLength, NULL ) ;

if (!fWriteStat) {
    /* Handle the error. */
	fprintf(report,"WriteComBlock:Error in Writing\n");

}
fclose(report);
return (fWriteStat);
}


/* ..................................................................
Function:     CleanOutputQueue()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     Remove all data remaining in the output queue
Arguments:    port         port number
Returns:      
Calls:
Notes:        Not yet implemented
   .................................................................. */


int CleanOutputQueue(int port)
{
	return(0);
}


/* ..................................................................
Function:     ConfigureSerialPort()
Date:         96.May.30
Author:       Vitor Sequeira
Comments:     
Arguments:    
Returns:      
Calls:
Notes:        
   .................................................................. */

HANDLE ConfigureSerialPort(char *port, int baud, int parity, int stop, int data)

{
HANDLE hCom;  
DCB dcb;
DWORD dwError;
BOOL fSuccess;
FILE *fp;

fp = fopen("report.txt","at");

hCom = CreateFile(port,
    GENERIC_READ | GENERIC_WRITE,
    0,    /* comm devices must be opened w/exclusive-access */
    NULL, /* no security attrs */
    OPEN_EXISTING, /* comm devices must use OPEN_EXISTING */
    0,    /* not overlapped I/O */
    NULL  /* hTemplate must be NULL for comm devices */
    );

if (hCom == INVALID_HANDLE_VALUE) {
    dwError = GetLastError();

    /* handle error */

	fprintf(fp,"Error 1\n");
}

/*
 * Omit the call to SetupComm to use the default queue sizes.
 * Get the current configuration.
 */

fSuccess = GetCommState(hCom, &dcb);

if (!fSuccess) {
    /* Handle the error. */
	fprintf(fp,"Error 2\n");
}


/* Fill in the DCB: baud, data bits, parity, stop bit. */

dcb.BaudRate = baud;
dcb.ByteSize = data;
dcb.Parity = parity;
dcb.StopBits = stop;

fSuccess = SetCommState(hCom, &dcb);

if (!fSuccess) {
	fprintf(fp,"Error 3\n");
    /* Handle the error. */
}


fclose(fp);
return (hCom);

}
