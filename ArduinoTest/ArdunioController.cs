using System.Management;
using System.Linq;
using System;
using System.IO.Ports;
using System.Collections;
using System.Collections.Generic;

namespace ArduinoTest
{
    class ArduinoController
    {
        public static List<Microcontroller> AutodetectArduinoPort()
        {
            ManagementScope connectionScope = new ManagementScope();
            SelectQuery serialQuery = new SelectQuery("SELECT * FROM Win32_SerialPort");
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(connectionScope, serialQuery);

            try
            {
                List<Microcontroller> mc = null;
                foreach (ManagementObject item in searcher.Get())
                {
                    string name = item["Name"].ToString();
                    string uname = item["UName"].ToString();
                    string description = item["Description"].ToString();
                    string deviceId = item["DeviceID"].ToString();
                    string PNPdeviceId = item["PNPDeviceID"].ToString();

                    if (description.Contains("Arduino Due") || description.Contains("Arduino Mega 2560") || description.Contains("Arduino One"))
                    //Temp Check. Needs to compare each return against Text file list when moved to VRAGE.
                    {
                        var mcItem = new Microcontroller(name, description, deviceId, PNPdeviceId,11520);
                        mc.Add(mcItem);

                    }

                }
                return mc; //< Needs to return an object list of all deviceIds and total count
            }
            catch (ManagementException e)
            {
                /* Do Nothing */
            }

            return null;
        }




        /* public static List<SerialPort> AutoAssignSerialPort()
         {
        
          try
                 {
                     int portCount = 0;
                     foreach (Microcontroller controller in Microcontrollers)
                         {
                             public void AddSerialPort(string PortName, string BaudRate)
                             {       
                                 var sp = Enumerable.Range(0, portCount).Select(x => new SerialPort(PortName, BaudRate).ToList();
                                 ports.Add(sp);
                                 portCount++;
            
       
                             }      
                         }
    
                 }
                    return sp; //< Needs to return an object list of all deviceIds and total count
         }*/

    }
}

