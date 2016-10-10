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
    public partial class LineTest : UserControl
    {
        public int lineTest = 0;
        public string result = "不合格";

        public delegate void LineStatusChanged();

        public LineStatusChanged StatusChanged;
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
            lineTest++;
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.lines.Content = lineTest;
            }));
            if (lineTest >= 5)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.lineResult.Content="通过";
                }));
                result = "合格";
            }
            StatusChanged();
        }

        public void clear()
        {
            lineTest = 0;
            result = "不合格";
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.lineResult.Content = "";
                this.lines.Content = "0";
            }));
        }
    }
}
