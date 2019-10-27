using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SerialUSBController.USB;
using System.Threading;
using System.IO.Ports;
namespace SerialUSBController
{

    public partial class Form1 : Form
    {
        USBEngine usbEngine;
        byte[] sendArray = new byte[256];
        byte flag = 0;
        public Form1()
        {
            InitializeComponent();
            sendArray[0] = 0;
            sendArray[1] = 0;
            sendArray[2] = 0;
            Label[] voltageLabels = new Label[16];
            voltageLabels[0] = labelVoltage;
            voltageLabels[1] = label3;
            voltageLabels[2] = label4;
            voltageLabels[3] = label5;
            voltageLabels[4] = label6;
            voltageLabels[5] = label7;
            voltageLabels[6] = label8;
            voltageLabels[7] = label9;
            voltageLabels[8] = label10;
            voltageLabels[9] = label11;
            voltageLabels[10] = label12;
            ProgressBar[] progressBarArray = new ProgressBar[16];
            progressBarArray[0] = progressBar;
            progressBarArray[1] = progressBar1;
            progressBarArray[2] = progressBar2;
            progressBarArray[3] = progressBar3;
            progressBarArray[4] = progressBar4;
            progressBarArray[5] = progressBar5;
            progressBarArray[6] = progressBar6;
            progressBarArray[7] = progressBar7;
            progressBarArray[8] = progressBar8;
            progressBarArray[9] = progressBar9;
            progressBarArray[10] = progressBar10;
            usbEngine = new USBEngine(textBoxReceiving, pictureBoxGraph, voltageLabels, progressBarArray);
            SetComPorts();
        }

        private void buttonRefreshComs_Click(object sender, EventArgs e)
        {
            SetComPorts();
        }

        void SetComPorts()
        {
            comboBoxComs.Items.Clear();
            comboBoxComs.Items.AddRange(usbEngine.ListPorts());
        }

        private void comboBoxComs_SelectedIndexChanged(object sender, EventArgs e)
        {
            textBoxBaudRate.Text = "" + usbEngine.CurrentBaudRate;
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (CheckComAndBaudRate())
                usbEngine.StartEngine(comboBoxComs.SelectedItem.ToString(), Convert.ToInt16(textBoxBaudRate.Text));
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            if (textBoxSending.Text != "")
            {
                usbEngine.SendText(textBoxSending.Text);
            }
        }

        private bool CheckComAndBaudRate()
        {
            bool isOk = true;
            try
            {
                Convert.ToInt16(textBoxBaudRate.Text);
            }
            catch
            {
                MessageBox.Show("BaudRate formatı uygun değil");
                isOk = false;
            }
            if (comboBoxComs.SelectedItem == null)
            {

                MessageBox.Show("COM noktası seçilmedi.");
                isOk = false;
            }
            return isOk;
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            usbEngine.StopEngine();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
                sendArray[0] |= 0x01;
            else
                sendArray[0] &= 0xFE;
            usbEngine.ChangeSendArray(sendArray, checkBox1.Checked ? 2 : -2);
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
                sendArray[0] |= 0x02;
            else
                sendArray[0] &= 0xFD;
            usbEngine.ChangeSendArray(sendArray, checkBox2.Checked ? 2 : -2);
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked)
                sendArray[0] |= 0x04;
            else
                sendArray[0] &= 0xFB;
            usbEngine.ChangeSendArray(sendArray, checkBox3.Checked ? 2 : -2);
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked)
                sendArray[0] |= 0x08;
            else
                sendArray[0] &= 0xF7;
            usbEngine.ChangeSendArray(sendArray, checkBox4.Checked ? 2 : -2);
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked)
                sendArray[0] |= 0x10;
            else
                sendArray[0] &= 0xEF;
            usbEngine.ChangeSendArray(sendArray, checkBox5.Checked ? 2 : -2);

        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox6.Checked)
                sendArray[0] |= 0x20;
            else
                sendArray[0] &= 0xDF;
            usbEngine.ChangeSendArray(sendArray, checkBox6.Checked ? 2 : -2);

        }

        private void checkBox7_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox7.Checked)
                sendArray[0] |= 0x40;
            else
                sendArray[0] &= 0xBF;
            usbEngine.ChangeSendArray(sendArray, checkBox7.Checked ? 2 : -2);
        }

        private void checkBox8_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox8.Checked)
                sendArray[0] |= 0x80;
            else
                sendArray[0] &= 0x7F;
            usbEngine.ChangeSendArray(sendArray, checkBox8.Checked ? 2 : -2);
        }

        private void checkBox9_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox9.Checked)
                sendArray[1] |= 0x01;
            else
                sendArray[1] &= 0xFE;
            usbEngine.ChangeSendArray(sendArray, checkBox9.Checked ? 2 : -2);
        }

        private void checkBox10_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox10.Checked)
                sendArray[1] |= 0x02;
            else
                sendArray[1] &= 0xFD;
            usbEngine.ChangeSendArray(sendArray, checkBox10.Checked ? 2 : -2);

        }

        private void checkBox11_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox11.Checked)
                sendArray[1] |= 0x10;
            else
                sendArray[1] &= 0xEF;
            usbEngine.ChangeSendArray(sendArray, 0);
        }

        private void checkBox12_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox12.Checked)
                sendArray[1] |= 0x20;
            else
                sendArray[1] &= 0xDF;
            usbEngine.ChangeSendArray(sendArray, 0);
        }


        private void checkBox13_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox13.Checked)
                sendArray[1] |= 0x40;
            else
                sendArray[1] &= 0xBF;
            usbEngine.ChangeSendArray(sendArray, 0);
        }

        private void checkBox14_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox14.Checked)
                sendArray[1] |= 0x80;
            else
                sendArray[1] &= 0x7F;
            usbEngine.ChangeSendArray(sendArray, 0);

        }

        private void checkBox15_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox15.Checked)
                sendArray[1] |= 0x04;
            else
                sendArray[1] &= 0xFB;
            usbEngine.ChangeSendArray(sendArray, checkBox15.Checked ? 2 : -2);

        }

        
        

       




        public unsafe void TrackBar1_Scroll_1(object sender, EventArgs e)
        {
           if (checkBox16.Checked)
            {
                int* deger;
                var adres = 0;

                adres = (int)(trackBar1.Value * 2.5);
                deger = &adres;

                sendArray[2] = Convert.ToByte(*deger);  
                numericUpDown1.Value = trackBar1.Value;
              

            }
            else
            {
                sendArray[2] = 0;
              
            }

            usbEngine.arraycopy2(sendArray);
            

        }


        private unsafe void NumericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            /*  var deger = (double) numericUpDown1.Value * 2.5;
              sendArray[0] = Convert.ToByte(deger);
              usbEngine.ChangeSendArray(sendArray, 0);
              */
            if (checkBox16.Checked)
            {
                int* deger;


                var adres = 0;

                adres = (int)((double)numericUpDown1.Value * 2.5);
                deger = &adres;



                sendArray[2] = Convert.ToByte(*deger);
                trackBar1.Value = (int)numericUpDown1.Value;
             
            }
            else
            {
                sendArray[2] = 0;
               
            }
            usbEngine.arraycopy2(sendArray);
        }

        private unsafe void TrackBar2_Scroll(object sender, EventArgs e)
        {
            if (checkBox17.Checked)
            {
                int* deger;
                var adres = 0;

                adres = (int)(trackBar2.Value * 2.5);
                deger = &adres;

                sendArray[3] = Convert.ToByte(*deger);
                numericUpDown2.Value = trackBar2.Value;


            }
            else
            {
                sendArray[3] = 0;

            }

            usbEngine.arraycopy2(sendArray);
        }

      
        private unsafe void NumericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            if (checkBox17.Checked)

            {

                int* deger;


                var adres = 0;

                adres = (int)((double)numericUpDown2.Value * 2.5);
                deger = &adres;



                sendArray[3] = Convert.ToByte(*deger);
                trackBar2.Value = (int)numericUpDown2.Value;

            }
            else
            {
                sendArray[3] = 0;

            }
            usbEngine.arraycopy2(sendArray);
        }

        private void CheckBox18_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox18.Checked)
            {
                flag = 1;
               
            }
            else
            {
                flag = 0;
                
            }
            sendArray[4] = flag;
            usbEngine.arraycopy2(sendArray);
        }









        /* private void Volt3_CheckedChanged(object sender, EventArgs e)
         {
             if (volt3.Checked)
             {
                 sendArray[1] = 0x99;
             }
           usbEngine.ChangeSendArray(sendArray, 0);
       }*/
    }
    }

  
        
        