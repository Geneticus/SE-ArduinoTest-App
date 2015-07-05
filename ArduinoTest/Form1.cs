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
        public Form1()
        {
            InitializeComponent();
            
            comboBox1.SelectedIndex = 0 ;
            serialPort1.PortName = comboBox1.Text;
            //serialPort1.PortName = "COM5";//Check Arduino IDE for what COM port is tied to device
            serialPort1.BaudRate = 115200;
        }

        #region Tab1
        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Open();
            if (serialPort1.IsOpen)
            {
            serialPort1.WriteLine("1");
            }
            serialPort1.Close();
            panel1.BackColor = Color.Lime;
            panel2.BackColor = Color.Transparent;            

        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Open();
            if (serialPort1.IsOpen)
            {
                serialPort1.WriteLine("0");
            }
            serialPort1.Close();
            panel2.BackColor = Color.Red; 
            panel1.BackColor = Color.Transparent;
        }
        #endregion

        #region Tab2
        private void Button_SendSingle_Click(object sender, EventArgs e)
        {
            // http://www.ascii-code.com/

            string textToSend = string.Format("\x02{0}\x03",textBox2.Text);

            serialPort1.Open();
            if (serialPort1.IsOpen)
            {
                serialPort1.WriteLine(textToSend);
            }
            serialPort1.Close();

        }
        #endregion

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = comboBox1.Text;
        }

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
    }
}
