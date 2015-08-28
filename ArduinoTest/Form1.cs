using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ArduinoTest
{
    public partial class Form1 : Form
    {
        public delegate void SetTextCallback(string text);
        public Form1()
        {
            InitializeComponent();
            serialPort1.PortName = ArduinoController.AutodetectArduinoPort();
            serialPort1.BaudRate = 115200;
            serialPort1.DataReceived += serialPort1_DataReceived;
            serialPort1.Open();

        }

        #region Tab1
        private void button1_Click(object sender, EventArgs e)      {
            //serialPort1.Open();
            if (serialPort1.IsOpen)
            {
            serialPort1.WriteLine("1");
            }
            //serialPort1.Close();
            panel1.BackColor = Color.Lime;
            panel2.BackColor = Color.Transparent;            

        }

        private void button2_Click(object sender, EventArgs e)
        {
            //serialPort1.Open();
            if (serialPort1.IsOpen)
            {
                serialPort1.WriteLine("0");
            }
            //serialPort1.Close();
            panel2.BackColor = Color.Red; 
            panel1.BackColor = Color.Transparent;
        }
        #endregion

        #region Tab2
        private void Button_SendSingle_Click(object sender, EventArgs e)
        {
            // http://www.ascii-code.com/

            string textToSend = string.Format("\x02{0}\x03",textBox2.Text);

            //serialPort1.Open();
            if (serialPort1.IsOpen)
            {
                serialPort1.WriteLine(textToSend);
            }
            //serialPort1.Close();

        }
        #endregion

        private void button3_Click(object sender, EventArgs e)
        {
            //Serial String Format (StartBit)(DataType,Item,CurrentValue,MaxValue)(StopBit)
            //StartBit = "\x02"
            //DataType = Integer value starting from 1. Indicates if values are Int, Float, Bool, etc.                      
            //Item = Number begining with 1. Indicates what the value is i.e. Health, speed, dampers.
            //CurrentValue = can be any type as indicated by DataType
            //MaxValue = can be any numeric as indicated by DataType
            //StopBit = "\x03"
        }

        private void button6_Click(object sender, EventArgs e)
        {
            //Serial String Format (StartBit)(DataType,Item,CurrentValue,MaxValue)(StopBit)
            //StartBit = "\x02"
            //DataType = Integer value starting from 1. Indicates if values are Int, Float, Bool, etc.                      
            //Item = Number begining with 1. Indicates what the value is i.e. Health, speed, dampers.
            //CurrentValue = can be any type as indicated by DataType
            //MaxValue = can be any numeric as indicated by DataType
            //StopBit = "\x03"
        }

        void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            var incoming = serialPort1.ReadExisting();
            dataRecieved(incoming);
        }

        private void dataRecieved(string text)
        {
           
            // InvokeRequired required compares the thread ID of
            // the calling thread to the thread ID of the 
            // creating thread.  If these threads are different, 
            // it returns true
            if (this.textBox3.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(dataRecieved);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.textBox3.Text = text;
            }
        }
    }
}
