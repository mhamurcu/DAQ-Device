using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
using System.IO.Ports;


namespace SerialUSBController.USB
{
    class USBEngine
    {
        USBConnectionManager connectionManager;
        USBDataProcessor dataProcessor;
        TextBox textBoxReceiving;
        PictureBox pictureBoxGraph;
        ProgressBar[] progBar = new  ProgressBar[16];
        Label[] labelVoltage = new Label[16];

        bool isPortOpen;
        Thread readThread;
        byte[] byteBuffer = new byte[256];
        byte[] readBuffer = new byte[256];
        byte[] sendBuffer = new byte[256];
        double[] voltageBuffer = new double[256];
        int readBytes;
        int totalBytes = 0;
        int expectedBytes = 1;
        int expectedBytesNew = 1;

        Stopwatch stopwatch = new Stopwatch();

        public USBEngine(TextBox textBoxReceiving_, PictureBox pictureBoxGraph_, Label[] voltageLabel_, ProgressBar[] progBar_)
        {
            connectionManager = new USBConnectionManager();
            dataProcessor = new USBDataProcessor();
            this.textBoxReceiving = textBoxReceiving_;
            this.pictureBoxGraph = pictureBoxGraph_;
            this.progBar = progBar_;
            this.labelVoltage = voltageLabel_;
        }

        public void StartEngine(string com, int baudRate) 
        {
            isPortOpen = connectionManager.ConnectToUSBPort(com, baudRate);
            if (!isPortOpen)
            {
                InformUI("Bağlantı sağlanamadı.");
                return;
            }
            sendBuffer[0] = 0;
            sendBuffer[1] = 0;
            sendBuffer[2] = 0;
            sendBuffer[3] = 0;
            sendBuffer[4] = 0;
            readThread = new Thread(ReadFromUSBConnection);
            readThread.Start();
            connectionManager.Send(".", sendBuffer, 5);
            stopwatch.Start();

        }

        public void ChangeSendArray(byte[] array , int change)
        {
            
         
            Array.Copy(array, 0, sendBuffer, 0, 2);
            expectedBytesNew += change; 
            if (expectedBytesNew < 1)
                expectedBytesNew = 1;
            else if (expectedBytesNew == 3)
                expectedBytesNew = 2;
        }
        public void arraycopy2 (byte[] array)
        {
            Array.Copy(array, 0, sendBuffer, 0, 5);
        }
       

        public void ReadFromUSBConnection()
        {
            while (isPortOpen)
            {
                try
                {
                    while (((readBytes = connectionManager.ReadBytes(ref byteBuffer)) > 0))
                    {
                        Array.Copy(byteBuffer, 0, readBuffer, totalBytes, readBytes);
                        totalBytes += readBytes;
                        if (totalBytes >= expectedBytes)
                        {
                            if (expectedBytes > 1)
                            {
                                double voltage = dataProcessor.CalculateVoltage(readBuffer, totalBytes, ref voltageBuffer, sendBuffer);
                                for (int i = 0; i < 11; i++)
                                {
                                    if (voltageBuffer[i] >= 11 || voltageBuffer[i] <= -11)
                                    {
                                        //stopwatch.Stop();4  
                                        //stopwatch.Reset();
                                        //InformUI("Hatalı Ölçüm: " + voltage);
                                        UpdateProgressBar(0, i);
                                        UpdateVoltage(12000, i);
                                    }

                                    else
                                    {
                                        UpdateVoltage(voltageBuffer[i], i);
                                        int progress = (int)(voltageBuffer[i] / 0.1f);
                                        UpdateProgressBar(progress, i);
                                        //InformUI(String.Format("Time elapsed (ns): {0}", stopwatch.Elapsed.TotalMilliseconds * 1000000));
                                    }
                                }
                            }
                            InformUI(String.Format("Time elapsed (ms): {0}", stopwatch.Elapsed.TotalMilliseconds));
                            totalBytes = 0;
                            expectedBytes = expectedBytesNew;
                            stopwatch.Stop();
                            stopwatch.Reset();

                            connectionManager.Send(".",sendBuffer,5);
                            stopwatch.Start();
                        }
                    }
                }
                catch (TimeoutException)
                {
                }
            }
            expectedBytes = expectedBytesNew;
            readThread.Join();
        }

        public void StopEngine()
        {
            if (connectionManager.CloseUSBSocket())
            {
                isPortOpen = false;
            }
            else
            {
                InformUI("Soket kapatılamadı.");
            }
        }

        internal string[] ListPorts()
        {
            return connectionManager.ListPorts();
        }

        internal string CurrentBaudRate
        {
            get
            {
                return "" + connectionManager.CurrentBaudRate;
            }
        }

        internal void SendText(string p)
        {
           // connectionManager.Send(p);
        }

        void InformUI(string message)
        {
            if (textBoxReceiving.InvokeRequired)
            {
                textBoxReceiving.Invoke((MethodInvoker)delegate
                {
                    AppendToUserTextBox(message);
                });
            }
            else
            {
                AppendToUserTextBox(message);
            }
        }

        void InformUISingle(string message)
        {
            if (textBoxReceiving.InvokeRequired)
            {
                textBoxReceiving.Invoke((MethodInvoker)delegate
                {
                    textBoxReceiving.Text = message;
                });
            }
            else
            {
                textBoxReceiving.Text = message;
            }
        }

        void UpdateProgressBar(int val , int index)
        {
            if (val <= 100 && val>=0)
            {
                if (progBar[index].InvokeRequired)
                {
                    progBar[index].Invoke((MethodInvoker)delegate
                    {
                        progBar[index].Value = val;
                    });
                }
                else
                {
                    progBar[index].Value = val;
                }
            }
            else if (val >= -100 && val < 0)
                {
                    if (progBar[index].InvokeRequired)
                    {
                        progBar[index].Invoke((MethodInvoker)delegate
                        {
                            progBar[index].Value = -val;                            
                        });
                    }
                    else
                    {
                        progBar[index].Value = -val;
                    }
                }
            else
            {
               // MessageBox.Show("Sınır değerlere ulaştınız.");
            }

        }


        void UpdateVoltage(double val,int index)
        {
            if (val > 10000)
            {

               /* if (labelVoltage[index].InvokeRequired)
                {
                    labelVoltage[index].Invoke((MethodInvoker)delegate
                    {
                        labelVoltage[index].Text = "Error";
                    });
                }
                else
                {
                    labelVoltage[index].Text = "Error";
                }*/
            }
            else if (val < -10000)
            {

               /* if (labelVoltage[index].InvokeRequired)
                {
                    labelVoltage[index].Invoke((MethodInvoker)delegate
                    {
                        labelVoltage[index].Text = "Error";
                    });
                }
                else
                {
                    labelVoltage[index].Text = "Error";
                }*/
            }
            else
            {

                if (labelVoltage[index].InvokeRequired)
                {
                    labelVoltage[index].Invoke((MethodInvoker)delegate
                    {
                        if(val<0)
                            labelVoltage[index].ForeColor = System.Drawing.Color.Red;
                        else
                            labelVoltage[index].ForeColor = System.Drawing.Color.Black;


                        labelVoltage[index].Text = val.ToString("00.00");
                    });
                }
                else
                {
                    if (val < 0)
                        labelVoltage[index].ForeColor = System.Drawing.Color.Red;
                    else
                        labelVoltage[index].ForeColor = System.Drawing.Color.Black;
                    labelVoltage[index].Text = val.ToString("00.00");
                }
            }
        }

        void AppendToUserTextBox(string message)
        {
            textBoxReceiving.AppendText(Environment.NewLine);
            textBoxReceiving.AppendText(message);
        }

    }
}
