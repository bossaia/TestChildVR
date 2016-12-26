using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
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

namespace TestChildVR.usercontrol
{
    /// <summary>
    /// PushCard.xaml 的交互逻辑
    /// </summary>
    public partial class PushCard : UserControl
    {
        [DllImport("HMDUSBManager.dll", EntryPoint = "ReceiveScdMessage", CallingConvention = CallingConvention.Cdecl)]
        extern static bool ReceiveScdMessage(int payout, int reset, int callback);
        [DllImport("HMDUSBManager.dll", EntryPoint = "ScdInputPulse", CallingConvention = CallingConvention.Cdecl)]
        extern static bool ScdInputPulse(ScdInputPulseHandler pCallbackFunc);

        [DllImport("HMDUSBManager.dll", EntryPoint = "SCDReceiveMessage", CallingConvention = CallingConvention.Cdecl)]


        extern static bool SCDReceiveMessage(int Massage);

        private bool CanPushCard = false;
        public string result = "不通过"; 

        private int CardTestCount = 0;
        private delegate void ScdInputPulseHandler([MarshalAs(UnmanagedType.I4)]int empty, [MarshalAs(UnmanagedType.I4)]int error, [MarshalAs(UnmanagedType.I4)]int getcard, [MarshalAs(UnmanagedType.I4)]int power);
        private  ScdInputPulseHandler iph;
        public PushCard()
        {
            InitializeComponent();
            StartPushCardThread();
        }

        public bool StartPushCardThread()
        {
            //=8获取上电状态；
            SCDReceiveMessage(8);
            Thread t = new Thread(InitlizePushCardUsb);
            t.Start();
            return true;
        }
        public void InitlizePushCardUsb()
        {
            iph = new ScdInputPulseHandler(ReceiveInputPulseCallBack);
            ScdInputPulse(iph);
        }
        //empty=1卡箱空，error=1卡堵塞或者回收仓满，getcard=0初始化,getcard=1卡到位，getcard=2卡已取走；power=1上电
        private void ReceiveInputPulseCallBack(int empty, int error, int getcard, int power)
        {
            if (power == 0)
            {
                CanPushCard = false;
                PushMsgToRichBox("吐卡器未上电");
                return;
            }
            if (empty == 1)
            {
                CanPushCard = false;
                PushMsgToRichBox("卡箱空");
                return;
            }
            if (error == 1)
            {
                CanPushCard = false;
                PushMsgToRichBox("卡堵塞或者回收仓满");
                return;
            }
            if (getcard == 0 || getcard == 1 || getcard==2)
            {
                switch (getcard)
                {
                    case 0:
                        PushMsgToRichBox("初始化已完成");
                        CanPushCard = true;
                        break;
                    case 1:
                        PushMsgToRichBox("卡到位");
                        break;
                    case 2:
                        PushMsgToRichBox("卡已取走,测试次数："+CardTestCount);
                        CardTestCount++; 
                        CanPushCard = true;
                        if (CardTestCount >= 5)
                        {
                            result = "通过";
                            PushMsgToRichBox("测试通过"); 
                        }
                        break;
                }
            }
            return;
        }

        public void PushMsgToRichBox(string msg)
        {
            if (this.PushCardRText.Document.Blocks.Count > 100)
            {
                this.PushCardRText.Document.Blocks.Clear();
            }
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.PushCardRText.AppendText(msg+"\n");
                this.PushCardRText.ScrollToEnd();
            }));
        }

        private void NotPassBtn_Click(object sender, RoutedEventArgs e)
        {
            result = "不通过";
        }

        public void Clear()
        {
            CardTestCount = 0;
            result = "不通过";
        }

        private void PushCardBtn_Click(object sender, RoutedEventArgs e)
        {
            if (CanPushCard)
            {
                ReceiveScdMessage(1, 0, 0);
            }
            else
            {
                PushMsgToRichBox("请检查当前吐卡器状态");
            }
        }
    }
}
