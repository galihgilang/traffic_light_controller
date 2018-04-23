using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Threading;
using System.Threading;
using System.Windows.Shapes;

namespace lampu_lalu_lintas
{
    public partial class MainWindow : Window
    {
        public static int thn=2000, bln=1, tgl=1, hr=1, jam=0, mnt=0, dtk=0;
        string sthn, sbln, stgl, shr, sjam, smnt, sdtk;

        string rxs;
        char[] rx = new char[30];
        char[] temp = new char[30];
        
        public static SerialPort ser;
        string[] ports = SerialPort.GetPortNames();

        SolidColorBrush grey = new SolidColorBrush();
        SolidColorBrush red = new SolidColorBrush();
        SolidColorBrush yellow = new SolidColorBrush();
        SolidColorBrush green = new SolidColorBrush();

        delegate void updatedisplay();
        
        public MainWindow()
        {
            InitializeComponent();
            init();
            initserial();           // koneksikan dgn port hardware

            Console.WriteLine("init serial selesai");
        }

        // **************************** Event Handler ***************************
        void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            ser.Write("n");
        }

        void RX_Interrupt(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            rxs = sp.ReadExisting();
            temp = rxs.ToCharArray();
            if (((temp[0] == 'a') || (temp[0] == 'b') || (temp[0] == 'c') || (temp[0] == 'd')) && (temp[(temp.Length) - 1] == 'z'))
            {
                rx = temp;
                state();
            }
            else if (((temp[0] == 'a') || (temp[0] == 'b') || (temp[0] == 'c') || (temp[0] == 'd')) && (temp[(temp.Length) - 1] != 'z'))
                rx = temp;
            else if ((temp[0] != 'a') && (temp[0] != 'b') && (temp[0] != 'c') && (temp[0] != 'd') && (temp[(temp.Length) - 1] != 'z'))
                rx = rx.Concat(temp).ToArray();
            else if ((temp[0] != 'a') && (temp[0] != 'b') && (temp[0] != 'c') && (temp[0] != 'd') && (temp[(temp.Length) - 1] == 'z'))
            {
                rx = rx.Concat(temp).ToArray();
                state();
            }
        }
        

        // ****************************** Prosedur ******************************
        private void init()
        {
            grey.Color = Color.FromArgb(255, 85, 85, 85);
            red.Color = Color.FromArgb(255, 242, 31, 31);
            yellow.Color = Color.FromArgb(255, 242, 242, 40);
            green.Color = Color.FromArgb(255, 60, 239, 28);

            this.Closing += new CancelEventHandler(MainWindow_Closing);
        }

        private void state()
        {
            switch(rx[0])
            {
                case 'a':
                    break;
                case 'b':
                    Console.WriteLine(rx);
                    tglwktstr2int();
                    tglwktint2display();
                    Dispatcher.Invoke(DispatcherPriority.Normal, new updatedisplay(display));
                    break;
            }
        }
        
        private void initserial()
        {
            int connect = 0;
            string com="COM40";

            foreach (string port in ports)
            {
                ser = new SerialPort(port, 9600, Parity.None, 8, StopBits.One);
                ser.DataReceived += new SerialDataReceivedEventHandler(RX_Interrupt);
                ser.Open();
                ser.Write("t");
                Thread.Sleep(500);  // delay 500ms
                if (rx[0] == 'a')
                {
                    connect = 1;
                    com = port;
                }
                ser.Close();
                if (connect == 1) break;
            }

            if (connect == 0)
            {
                comportwindow comport_window = new comportwindow();
                comport_window.Show();
                this.Close();
            }
            else if (connect == 1)
            {
                ser = new SerialPort(com, 9600, Parity.None, 8, StopBits.One);
                ser.DataReceived += new SerialDataReceivedEventHandler(RX_Interrupt);
                ser.Open();
                Console.WriteLine(com);
            }
        }               // state A

        private void tglwktstr2int()
        {
            thn = (Convert.ToInt32(rx[1] - 48) * 1000) + (Convert.ToInt32(rx[2] - 48) * 100) + (Convert.ToInt32(rx[3] - 48) * 10) + Convert.ToInt32(rx[4] - 48);
            bln = (Convert.ToInt32(rx[5] - 48) * 10) + Convert.ToInt32(rx[6] - 48);
            tgl = (Convert.ToInt32(rx[7] - 48) * 10) + Convert.ToInt32(rx[8] - 48);
            hr = Convert.ToInt32(rx[9] - 48);
            jam = (Convert.ToInt32(rx[10] - 48) * 10) + Convert.ToInt32(rx[11] - 48);
            mnt = (Convert.ToInt32(rx[12] - 48) * 10) + Convert.ToInt32(rx[13] - 48);
            dtk = (Convert.ToInt32(rx[14] - 48) * 10) + Convert.ToInt32(rx[15] - 48);
        }            // state B

        private void tglwktint2display()
        {
            sthn = thn.ToString();

            switch (bln)
            { 
                case 1:
                    sbln = "Januari";
                    break;
                case 2:
                    sbln = "Februari";
                    break;
                case 3:
                    sbln = "Maret";
                    break;
                case 4:
                    sbln = "April";
                    break;
                case 5:
                    sbln = "Mei";
                    break;
                case 6:
                    sbln = "Juni";
                    break;
                case 7:
                    sbln = "Juli";
                    break;
                case 8:
                    sbln = "Agustus";
                    break;
                case 9:
                    sbln = "September";
                    break;
                case 10:
                    sbln = "Oktober";
                    break;
                case 11:
                    sbln = "November";
                    break;
                case 12:
                    sbln = "Desember";
                    break;
            }

            stgl = tgl.ToString();
            
            switch (hr)
            {
                case 1:
                    shr = "Minggu";
                    break;
                case 2:
                    shr = "Senin";
                    break;
                case 3:
                    shr = "Selasa";
                    break;
                case 4:
                    shr = "Rabu";
                    break;
                case 5:
                    shr = "Kamis";
                    break;
                case 6:
                    shr = "Jumat";
                    break;
                case 7:
                    shr = "Sabtu";
                    break;
            }

            if (jam < 10)
                sjam = string.Concat("0", jam.ToString());
            else
                sjam = jam.ToString();

            if (mnt < 10)
                smnt = string.Concat("0", mnt.ToString());
            else
                smnt = mnt.ToString();

            if (dtk < 10)
                sdtk = string.Concat("0", dtk.ToString());
            else
                sdtk = dtk.ToString();
        }

        void display()
        {
            textwkt.Text = string.Concat(sjam, ":", smnt, ":", sdtk);
            texttgl.Text = string.Concat(shr, ", ", stgl, " ", sbln, " ", sthn);
        }
    }
}
