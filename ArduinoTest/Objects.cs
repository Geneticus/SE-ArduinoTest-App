using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace ArduinoTest
{
    class Microcontroller
    {
        public Microcontroller(string name, string description, string deviceID, string PNPdeviceID, int baudRate)
        {
            Name = name; Description = description; DeviceID = deviceID; PNPDeviceID = PNPdeviceID; BaudRate = baudRate;

            //check to see if all variables are filled before creating port, if no , error.
            //createSerialPort(); //This needs to be moved to form ok, click.
        }
        public string Name { get; set; }
        public string UName { get; set; }
        public string Description { get; set; }
        public string DeviceID { get; set; }
        public string PNPDeviceID { get; set; }
        public int BaudRate { get; set; }
                
        public SerialPort serialPort;

        public void createSerialPort()
        {
            serialPort = new SerialPort(DeviceID, BaudRate);
            serialPort.Open();
        }
    }


}

