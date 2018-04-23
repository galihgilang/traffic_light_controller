using System;
using System.ComponentModel;
using System.Collections.Generic;
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
    /// Interaction logic for settingwindow.xaml
    /// </summary>
    public partial class settingwindow : Window
    {
        public settingwindow()
        {
            InitializeComponent();
            this.Closing += new CancelEventHandler(SettingWindow_Closing);
        }

        void SettingWindow_Closing(object sender, CancelEventArgs e)
        {
            MainWindow main = new MainWindow();
            main.Show();
        }

        private void backbutton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.thn++;
            this.Close();
        }
    }
}
