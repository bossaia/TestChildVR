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
    /// 
    public partial class CoinsIn : UserControl
    {
        public int mycoins = 0;
        public string _passFlag ="不合格";
        public delegate void coinsInStatusChanged();

        public event coinsInStatusChanged statusChanged;
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
            if (mycoins >= 5)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.result.Content = "通过";
                }));
                _passFlag = "合格";
            }
            statusChanged();
        }

        public void clear()
        {
            mycoins = 0;
            _passFlag = "不合格";
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.result.Content = "";
                this.Coins.Content = "0";
            }));
        }
    }
}
