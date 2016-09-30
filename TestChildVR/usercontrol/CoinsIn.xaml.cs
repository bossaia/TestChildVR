using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
    /// CoinsIn.xaml 的交互逻辑
    /// </summary>
    public partial class CoinsIn : Window
    {
        public int mycoins = 0;
        public string _passFlag ;
        public CoinsIn()
        {
            InitializeComponent();
            Initlize();
        } 
        public void Initlize()
        {
            getCoins.receiver.StartReceiver();
            getCoins.count.OnReturn += count_OnReturn;
        }
        void count_OnReturn()
        {
            mycoins++;
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Coins.Content = mycoins.ToString();
            }));
        }
        private void Pass_OnClick(object sender, RoutedEventArgs e)
        {
           // throw new NotImplementedException();
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Visibility =Visibility.Hidden;
                _passFlag = "合格";
            }));
        }
        private void NotPass_OnClick(object sender, RoutedEventArgs e)
        {
            //throw new NotImplementedException();
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Visibility = Visibility.Hidden;
                _passFlag = "不合格";
            }));
        }
    }
}
