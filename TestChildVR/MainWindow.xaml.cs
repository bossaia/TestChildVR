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
        public MainWindow()
        {
            InitializeComponent();
            InitlizeHashtable();
          
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





        private void InitlizeHashtable()
        {
            ht.Add("im001", "aaaaaa");
            ht.Add("im002", "bbbbbb");
            ht.Add("im003", "cccccc");
            ht.Add("im004", "dddddd");
            ht.Add("im005", "eeeeee");
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
