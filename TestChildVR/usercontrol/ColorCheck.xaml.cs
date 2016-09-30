using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TestChildVR.usercontrol
{
    /// <summary>
    /// ColorCheck.xaml 的交互逻辑
    /// </summary>
    public partial class ColorCheck : Window
    {
        System.Timers.Timer t = new Timer(1000);
        Random rd = new Random();
        private int left = 0;
        private int up = 0;
        private int right = 0;
        private int down = 0;
        public ColorCheck()
        {
            InitializeComponent();
            this.checkPass.Margin=new Thickness(rd.Next(683),rd.Next(384),rd.Next(683),rd.Next(384));
            InitlizeTimer();
        }

        public void InitlizeTimer()
        {
            t.AutoReset = true;
            t.Enabled = true;
            t.Elapsed += t_Elapsed;
        }

        void t_Elapsed(object sender, ElapsedEventArgs e)
        {
            //throw new NotImplementedException();
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.checkPass.Margin = new Thickness(rd.Next(683), rd.Next(384), rd.Next(683), rd.Next(384));
            }));
        }
        private void CheckPass_OnClick(object sender, RoutedEventArgs e)
        {
            //throw new NotImplementedException();
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Visibility = Visibility.Hidden;
            }));
        }
    }
}
