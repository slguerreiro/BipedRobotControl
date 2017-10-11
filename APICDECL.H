/* $Header:  Exp $
 *
 *  $Description: defines prototypes for all API's to ppppapi.dll $
 *
 *  $Written by:    Tony Yokoyama, MXD $
 *
 *  $Revision:  $
 *
 *  $Date:  $
 *
 *  $Copyright: 1997, Hewlett-Packard Company. All rights reserved.$
 *
 */

#if __cplusplus
extern "C" {
#endif

int mapDeviceToPort(int portNum, USHORT baseAddr, int portRange);
USHORT getPortAddress(int portNum);

USHORT Peek8(USHORT portIndex, USHORT offset, int *status);
USHORT Peek16(USHORT portIndex, USHORT offset, int *status);
ULONG Peek32(USHORT portIndex, USHORT offset, int *status);

int Poke8(USHORT portIndex, USHORT offset, USHORT data, int *status);
int Poke16(USHORT portIndex, USHORT offset, USHORT data, int *status);
int Poke32(USHORT portIndex, USHORT offset, ULONG data, int *status);

USHORT Peek8M(USHORT portIndex, USHORT offset, USHORT invertmask, int *status);
USHORT Peek16M(USHORT portIndex, USHORT offset, USHORT invertmask, int *status);
ULONG Peek32M(USHORT portIndex, USHORT offset, ULONG invertmask, int *status);

int Poke8M(USHORT portIndex, USHORT offset, USHORT data, USHORT invertmask, int *status);
int Poke16M(USHORT portIndex, USHORT offset, USHORT data, USHORT invertmask, int *status);
int Poke32M(USHORT portIndex, USHORT offset, ULONG data, ULONG invertmask, int *status);

USHORT PeekPoke8(USHORT portIndex, USHORT offset, USHORT data, USHORT mask, USHORT invert, int *status);
USHORT PeekPoke16(USHORT portIndex, USHORT offset,USHORT data, USHORT mask, USHORT invert, int *status);
ULONG PeekPoke32(USHORT portIndex, USHORT offset, ULONG data, ULONG mask, ULONG invert, int *status);

ULONG BlockPeek8(USHORT portIndex, USHORT offset, UCHAR *buffer, ULONG numBytes, int *status);
ULONG BlockPeek16(USHORT portIndex, USHORT offset, USHORT *buffer, ULONG numBytes, int *status);
ULONG BlockPeek32(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG numBytes, int *status);

ULONG BlockPeek8L(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, int *status);
ULONG BlockPeek16L(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, int *status);
ULONG BlockPeek32L(USHORT portIndex, USHORT offset, ULONG *buffer,ULONG itemCount, int *status);

ULONG BlockPoke8(USHORT portIndex, USHORT offset, UCHAR *buffer, ULONG numBytes, int *status);
ULONG BlockPoke16(USHORT portIndex, USHORT offset, USHORT *buffer, ULONG numBytes, int *status);
ULONG BlockPoke32(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG numBytes, int *status);

ULONG BlockPoke8L(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, int *status);
ULONG BlockPoke16L(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, int *status);
ULONG BlockPoke32L(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, int *status);

ULONG BlockPeek8X(USHORT portIndex, USHORT offset, UCHAR *buffer, ULONG numBytes, ULONG delay, int *status);
ULONG BlockPeek16X(USHORT portIndex, USHORT offset, USHORT *buffer, ULONG numBytes, ULONG delay, int *status);
ULONG BlockPeek32X(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG numBytes, ULONG delay, int *status);

ULONG BlockPeek8XM(USHORT portIndex, USHORT offset, UCHAR *buffer, ULONG numBytes, ULONG delay, USHORT invertmask,int *status);
ULONG BlockPeek16XM(USHORT portIndex, USHORT offset, USHORT *buffer, ULONG numBytes, ULONG delay, USHORT invertmask,int *status);
ULONG BlockPeek32XM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG numBytes, ULONG delay, ULONG invertmask,int *status);

ULONG BlockPeek8XL(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG delay, int *status);
ULONG BlockPeek16XL(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG delay, int *status);
ULONG BlockPeek32XL(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG delay, int *status);

ULONG BlockPeek8XLM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG delay, USHORT invert, int *status);
ULONG BlockPeek16XLM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG delay, USHORT invert, int *status);
ULONG BlockPeek32XLM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG delay, ULONG invert, int *status);

ULONG BlockPoke8X(USHORT portIndex, USHORT offset, UCHAR *buffer, ULONG numBytes, ULONG rptCount, ULONG delay, int *status);
ULONG BlockPoke16X(USHORT portIndex, USHORT offset, USHORT *buffer, ULONG numBytes, ULONG rptCount, ULONG delay, int *status);
ULONG BlockPoke32X(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG numBytes, ULONG rptCount, ULONG delay, int *status);

ULONG BlockPoke8XM(USHORT portIndex, USHORT offset, UCHAR *buffer, ULONG numBytes, ULONG rptCount, ULONG delay, USHORT invertmask, int *status);
ULONG BlockPoke16XM(USHORT portIndex, USHORT offset, USHORT *buffer, ULONG numBytes, ULONG rptCount, ULONG delay, USHORT invertmask, int *status);
ULONG BlockPoke32XM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG numBytes, ULONG rptCount, ULONG delay, ULONG invertmask, int *status);

ULONG BlockPoke8XL(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG rptCount, ULONG delay, int *status);
ULONG BlockPoke16XL(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG rptCount, ULONG delay, int *status);
ULONG BlockPoke32XL(USHORT portIndex, USHORT offset,ULONG *buffer, ULONG itemCount, ULONG rptCount, ULONG delay, int *status);

ULONG BlockPoke8XLM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG rptCount, ULONG delay, USHORT invert, int *status);
ULONG BlockPoke16XLM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG rptCount, ULONG delay, USHORT invert, int *status);
ULONG BlockPoke32XLM(USHORT portIndex, USHORT offset, ULONG *buffer, ULONG itemCount, ULONG rptCount, ULONG delay, ULONG invert, int *status);

#if __cplusplus
}
#endif

