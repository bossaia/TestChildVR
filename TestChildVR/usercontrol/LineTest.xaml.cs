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
    /// LineTest.xaml 的交互逻辑
    /// </summary>
    public partial class LineTest : Window
    {
        public int lineTest = 0;
        public string result = "";
        public LineTest()
        {
            InitializeComponent();
            initlize();
        }

        public void initlize()
        {
            TestLine.TestLine.StartReceiver();
            TestLine.count.OnReturn += count_OnReturn;
        }

        void count_OnReturn()
        {
            //throw new NotImplementedException();
            //Console.WriteLine(@"aaaa");
            lineTest++;
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.lines.Content = lineTest;
            }));
        }

        private void Pass_OnClick(object sender, RoutedEventArgs e)
        {
           // throw new NotImplementedException();
            result = "合格";
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Visibility = Visibility.Hidden;
            }));
        }

        private void NotPass_OnClick(object sender, RoutedEventArgs e)
        {
           // throw new NotImplementedException();
            result = "不合格";
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Visibility = Visibility.Hidden;
            }));
        }
    }
}
