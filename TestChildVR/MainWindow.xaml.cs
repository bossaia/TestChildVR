using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using TestChildVR.usercontrol;

namespace TestChildVR
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        Hashtable ht = new Hashtable();
        ColorCheck colorcheck = new ColorCheck();
        MusicCheck musiccheck = new MusicCheck();
        CoinsIn conisIn = new CoinsIn();
        LineTest linetest = new LineTest();
        public MainWindow()
        {
            InitializeComponent();
            InitlizeHashtable();
            Initlize();
        }

        private void Login_OnClick(object sender, RoutedEventArgs e)
        {
            //throw new NotImplementedException();
            if (string.IsNullOrWhiteSpace(this.Username.Text))
            {
                MessageBox.Show(@"请输入用户名");
                return;
            }
            if (string.IsNullOrWhiteSpace(this.password.Password))
            {
                MessageBox.Show(@"请输入密码");
                return;
            }
            if (ht[this.Username.Text].Equals(this.password.Password))
            {
                Console.WriteLine(@"登入成功");
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.loginGrid.Visibility=Visibility.Hidden;
                    this.testGrid.Visibility=Visibility.Visible;
                }));
            }
        }

        private void Initlize()
        {
            colorcheck.IsVisibleChanged += colorcheck_IsVisibleChanged;
            musiccheck.IsVisibleChanged += musiccheck_IsVisibleChanged;
            conisIn.IsVisibleChanged += conisIn_IsVisibleChanged;
            linetest.IsVisibleChanged += linetest_IsVisibleChanged;
        }

        void linetest_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            //throw new NotImplementedException();
            if (linetest.Visibility == Visibility.Visible)
            {
                this.linetest.lineTest = 0;
            }
            else
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.Visibility = Visibility.Visible;
                    Flushmsg("总共连通:" + this.linetest.lineTest + "次，测试结果：" + this.linetest.result + "\n");
                }));
            }
        }

        void conisIn_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            //throw new NotImplementedException();
            if (conisIn.Visibility == Visibility.Hidden)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    //this.Visibility = Visibility.Visible;
                    Flushmsg("总投币共" + this.conisIn.mycoins + "个,检测结果：" + this.conisIn._passFlag + "\n");
                    this.linetest.Visibility = Visibility.Visible;
                }));
            }
            if (conisIn.Visibility == Visibility.Visible)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.Visibility = Visibility.Hidden;
                    this.conisIn._passFlag = "不通过";
                    this.conisIn.mycoins = 0;
                }));
            }
        }

        void musiccheck_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            //throw new NotImplementedException();
            if (musiccheck.Visibility == Visibility.Hidden)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.Visibility = Visibility.Visible;
                    Flushmsg("声道检测结果,左声道：" + musiccheck.leftVoiceCheck + ",右声道：" + musiccheck.rightVoiceCheck + "\n");
                    conisIn.Visibility=Visibility.Visible;
                }));
            }
        }

        void colorcheck_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            //throw new NotImplementedException();
            if (colorcheck.Visibility == Visibility.Hidden)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    Flushmsg("色彩检测完成" + DateTime.Now.ToString("F") + "\n");
                    musiccheck.Visibility = Visibility.Visible;
                    this.Visibility = Visibility.Hidden;
                }));
            }
        }

        private void InitlizeHashtable()
        {
            ht.Add("im001", "aaaaaa");
            ht.Add("im002", "bbbbbb");
            ht.Add("im003", "cccccc");
            ht.Add("im004", "dddddd");
            ht.Add("im005", "eeeeee");
        }

        private void StartCheck_OnClick(object sender, RoutedEventArgs e)
        {
            //
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                colorcheck.Visibility = Visibility.Visible;
            }));
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            Environment.Exit(0);
        }

        public void Flushmsg(string msg)
        {
            
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                if (this.myRichTextBox.Document.Blocks.Count > 100)
                {
                    this.myRichTextBox.Document.Blocks.Clear();
                }
                this.myRichTextBox.AppendText(msg);
                this.myRichTextBox.ScrollToEnd();
            }));
        }
    }
}
