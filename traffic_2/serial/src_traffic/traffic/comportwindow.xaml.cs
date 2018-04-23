using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;

namespace lampu_lalu_lintas
{
    /// <summary>
    /// Interaction logic for comportwindow.xaml
    /// </summary>
    public partial class comportwindow : Window
    {
        public comportwindow()
        {
            InitializeComponent();
        }
        
        private void button1_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
