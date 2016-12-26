using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Printing;
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
using draw = System.Drawing;

namespace TestChildVR
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        Hashtable ht = new Hashtable();
        ColorCheck colorcheck = new ColorCheck();
        PrintDocument pd = new PrintDocument();
        private string handlers;
        public MainWindow()
        {
            InitializeComponent();
            InitlizeHashtable();
            colorcheck.IsVisibleChanged += colorcheck_IsVisibleChanged;
            coinsCheck.statusChanged += coinsCheck_statusChanged;
            lineCheck.StatusChanged += coinsCheck_statusChanged;
        }

        void coinsCheck_statusChanged()
        {
            //throw new NotImplementedException();
            if (this.coinsCheck.mycoins >= 5 && this.lineCheck.lineTest >= 5)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.printResult.Visibility = Visibility.Visible;
                }));
            }
            if (this.coinsCheck.notpass)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.printResult.Visibility = Visibility.Visible;
                })); 
            }
            if (this.lineCheck.notpass)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.printResult.Visibility = Visibility.Visible;
                })); 
            }
        }

        void colorcheck_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            //throw new NotImplementedException();
            if (this.colorcheck.Visibility == Visibility.Visible)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.Visibility = Visibility.Hidden;
                }));
            }
            else
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.Visibility = Visibility.Visible;
                }));
            }
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
                handlers = this.Username.Text;
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
            
            //this.Dispatcher.BeginInvoke(new Action(() =>
            //{
            //    if (this.myRichTextBox.Document.Blocks.Count > 100)
            //    {
            //        this.myRichTextBox.Document.Blocks.Clear();
            //    }
            //    this.myRichTextBox.AppendText(msg);
            //    this.myRichTextBox.ScrollToEnd();
            //}));
        }

        private void StartCheck_OnClick(object sender, RoutedEventArgs e)
        {
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.colorcheck.Visibility = Visibility.Visible;
                this.Visibility = Visibility.Hidden;
            }));
        }

        private void PrintResult_OnClick(object sender, RoutedEventArgs e)
        {
            //throw new NotImplementedException();
            PaperSize ps = new PaperSize("First custom size", 160, 120);
            pd.DefaultPageSettings.PaperSize = ps;
            pd.PrintPage += pd_PrintPage;
            pd.Print();
            this.coinsCheck.clear();
            this.lineCheck.clear();
            this.musicCheck.clear();
            this.pushcard.Clear();
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.printResult.Visibility = Visibility.Hidden;
            }));
        }
        public StringBuilder GetPrintSW()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("映墨科技");
            sb.AppendLine("操作者："+handlers);
            sb.AppendLine("屏幕  :"+this.colorcheck.CheckResult);
            sb.AppendLine("左声道："+this.musicCheck.leftVoiceCheck);
            sb.AppendLine("右声道：" + this.musicCheck.rightVoiceCheck);
            sb.AppendLine("投币  ：" + this.coinsCheck._passFlag);
            sb.AppendLine("按键  ：" + this.lineCheck.result);
            sb.AppendLine("吐卡   :"+this.pushcard.result);
            sb.AppendLine(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
            return sb; 
        }


        void pd_PrintPage(object sender, PrintPageEventArgs e)
        {
            draw.Font titleFont = new draw.Font("宋体", 9, draw.FontStyle.Bold);//标题字体           

            draw.Font fntTxt = new draw.Font("宋体", 9, draw.FontStyle.Regular);//正文文字           

            draw.Brush brush = new draw.SolidBrush(draw.Color.Black);//画刷           

            draw.Pen pen = new draw.Pen(draw.Color.Black);           //线条颜色           

            draw.Point po = new draw.Point(0, 0);

            try
            {

                e.Graphics.DrawString(GetPrintSW().ToString(), titleFont, brush, po);   //DrawString方式进行打印。        

            }

            catch (Exception ex)
            {

                MessageBox.Show(ex.ToString());
            }
        }

        private void ColorNotAllow_OnClick(object sender, RoutedEventArgs e)
        {
            //throw new NotImplementedException();
            this.colorcheck.CheckResult = "不合格";
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.printResult.Visibility = Visibility.Visible;
            }));
            
        }
    }
}
