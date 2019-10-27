using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SerialUSBController.USB
{
    class USBDataProcessor
    {

        List<int> intList = new List<int>();

        public double CalculateVoltage(byte[] incomingByteArray, int readBytes , ref double[] returnArray, byte[] sendBuffer)
        {
            int totalChannel = 0;
            int incomingValue = 0;
           
            if ((sendBuffer[0] & 0x01) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[0]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
                returnArray[0] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[0] & 0x02) != 0)
            {   
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[1] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[0] & 0x04) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[2] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[0] & 0x08) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[3] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[0] & 0x10) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[4] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[0] & 0x20) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[5] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[0] & 0x40) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[6] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[0] & 0x80) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[7] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[1] & 0x01) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[8] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[1] & 0x02) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]) - 1940;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[9] = incomingValue * 0.000804931d * 6.66d;
            if ((sendBuffer[1] & 0x04) != 0)
            {
                incomingValue = (int)(((int)incomingByteArray[1 + totalChannel * 2] << 8) + (int)incomingByteArray[+totalChannel * 2]);
                if (incomingValue >= 32768)
                    incomingValue -= 65536;
                totalChannel++;
            }
            else
                incomingValue = 0;
            returnArray[10] = incomingValue * 0.00030517578125d;
            //returnArray[10] += 10;
            returnArray[10] /= (10.0d / 3.3);
            return returnArray[0];
        }
    }
}
