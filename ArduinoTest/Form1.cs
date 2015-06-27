﻿using System;
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
            serialPort1.PortName = "COM5";//Check Arduino IDE for what COM port is tied to device
            serialPort1.BaudRate = 9600;
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

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void Button_SendSingle_Click(object sender, EventArgs e)
        {
            // http://www.ascii-code.com/

        }
    }
}
