int mapDeviceToPort(int portIndex, short baseAddr, int portRange);
short getPortAddress(int portNum);

short Peek8(short portIndex, short offset, int *status);
short Peek16(short portIndex, short offset, int *status);
long Peek32(short portIndex, short offset, int *status);

short Peek8M(short portIndex, short offset, short invert, int *status);
short Peek16M(short portIndex, short offset, short invert, int *status);
long Peek32M(short portIndex, short offset, short invert, int *status);

int  Poke8(short portIndex, short offset,short data, int *status);
int  Poke16(short portIndex, short offset,short data, int *status);
int  Poke32(short portIndex, short offset,long data, int *status);

int  Poke8M(short portIndex, short offset, short data, short invert, int *status);
int  Poke16M(short portIndex, short offset, short data, short invert, int *status);
int  Poke32M(short portIndex, short offset, long data, long invert, int *status);

short  PeekPoke8(short portIndex, short offset,short data,short mask, short invert, int *status);
short  PeekPoke16(short portIndex, short offset,short data,short mask, short invert, int *status);
long  PeekPoke32(short portIndex, short offset,long data, long mask, long invert, int *status);


long  BlockPeek8(short portIndex, short offset,char *buffer,long numBytes, int *status);
long  BlockPeek16(short portIndex, short offset,short *buffer,long numBytes, int *status);
long  BlockPeek32(short portIndex, short offset,long *buffer,long numBytes, int *status);

long  BlockPoke8(short portIndex, short offset,char *buffer,long numBytes, int *status);
long  BlockPoke16(short portIndex, short offset,short *buffer,long numBytes, int *status);
long  BlockPoke32(short portIndex, short offset,long *buffer,long numBytes, int *status);

long  BlockPeek8X(short portIndex, short offset,char *buffer,long numBytes,long delay,int *status);
long  BlockPeek16X(short portIndex, short offset,short *buffer,long numBytes,long delay, int *status);
long  BlockPeek32X(short portIndex, short offset,long *buffer,long numBytes,long delay, int *status);

long  BlockPeek8XM(short portIndex, short offset,char *buffer,long numBytes,long delay, short invert, int *status);
long  BlockPeek16XM(short portIndex, short offset,short *buffer,long numBytes,long delay, short invert, int *status);
long  BlockPeek32XM(short portIndex, short offset,long *buffer,long numBytes,long delay, long invert, int *status);

long  BlockPoke8X(short portIndex, short offset,char *buffer,long numBytes,long rptCount,long delay, int *status);
long  BlockPoke16X(short portIndex, short offset,short *buffer,long numBytes,long rptCount,long delay, int *status);
long  BlockPoke32X(short portIndex, short offset,long *buffer,long numBytes,long rptCount,long delay, int *status);

long  BlockPoke8XM(short portIndex, short offset,char *buffer,long numBytes,long rptCount,long delay, short invert, int *status);
long  BlockPoke16XM(short portIndex, short offset,short *buffer,long numBytes,long rptCount,long delay, short invert, int *status);
long  BlockPoke32XM(short portIndex, short offset,long *buffer,long numBytes,long rptCount,long delay, long invert, int *status);

long  BlockPeek8L(short portIndex, short offset,long *buffer,long dataPoints, int *status);
long  BlockPeek16L(short portIndex, short offset,long *buffer,long dataPoints, int *status);
long  BlockPeek32L(short portIndex, short offset,long *buffer,long dataPoints, int *status);

long  BlockPoke8L(short portIndex, short offset,long *buffer,long dataPoints, int *status);
long  BlockPoke16L(short portIndex, short offset,long *buffer,long dataPoints, int *status);
long  BlockPoke32L(short portIndex, short offset,long *buffer,long dataPoints, int *status);

long  BlockPeek8XL(short portIndex, short offset,long *buffer,long dataPoints,long delay,int *status);
long  BlockPeek16XL(short portIndex, short offset,long *buffer,long dataPoints,long delay, int *status);
long  BlockPeek32XL(short portIndex, short offset,long *buffer,long dataPoints,long delay, int *status);

long  BlockPeek8XLM(short portIndex, short offset,long *buffer,long dataPoints,long delay, short invert, int *status);
long  BlockPeek16XLM(short portIndex, short offset,long *buffer,long dataPoints,long delay, short invert, int *status);
long  BlockPeek32XLM(short portIndex, short offset,long *buffer,long dataPoints,long delay, long invert, int *status);

long  BlockPoke8XL(short portIndex, short offset,long *buffer,long dataPoints,long rptCount,long delay, int *status);
long  BlockPoke16XL(short portIndex, short offset,long *buffer,long dataPoints,long rptCount,long delay, int *status);
long  BlockPoke32XL(short portIndex, short offset,long *buffer,long dataPoints,long rptCount,long delay, int *status);

long  BlockPoke8XLM(short portIndex, short offset,long *buffer,long dataPoints,long rptCount,long delay, short invert, int *status);
long  BlockPoke16XLM(short portIndex, short offset,long *buffer,long dataPoints,long rptCount,long delay, short invert, int *status);
long  BlockPoke32XLM(short portIndex, short offset,long *buffer,long dataPoints,long rptCount,long delay, long invert, int *status);
