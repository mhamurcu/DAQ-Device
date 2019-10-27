using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;

namespace SerialUSBController.USB
{
    class USBConnectionManager
    {
        SerialPort activeSerialPort = new SerialPort();

        internal string[] ListPorts()
        {
            return SerialPort.GetPortNames();
        }

        public int CurrentBaudRate
        {
            get
            {
                return activeSerialPort.BaudRate;
            }
        }

        internal bool ConnectToUSBPort(string com, int baudRate)
        {
            try
            {
                activeSerialPort.PortName = com;
                activeSerialPort.BaudRate = baudRate;
                activeSerialPort.Open();
            }
            catch
            {
                return false;
            }
            return true;
        }

        internal int ReadBytes(ref byte[] buffer)
        {
            if (activeSerialPort.IsOpen)
                return activeSerialPort.Read(buffer, 0, buffer.Length);
            else
                return 0;
        }

        internal bool CloseUSBSocket()
        {
            try
            {
                activeSerialPort.Close();
            }
            catch
            {
                return false;
            }
            return true;
        }

        internal void Send(string p , byte[] sendBuffer ,int sendSize)
        {
            if (activeSerialPort.IsOpen)
                //activeSerialPort.WriteLine(p);
                activeSerialPort.Write(sendBuffer,0,sendSize);
        }
    }
}
