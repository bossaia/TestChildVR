using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TestLine
{
    public class TestLine
    {
        private delegate void InputPulseHandler([MarshalAs(UnmanagedType.I4)]int money);
        private static InputPulseHandler iph;

        private static Thread getValue;


        [DllImport("LineUSBManager.dll", EntryPoint = "InputPulse", CallingConvention = CallingConvention.Cdecl)]
        extern static bool InputPulse(InputPulseHandler pCallbackFunc);//([MarshalAs(UnmanagedType.FunctionPtr)] InputPulseHandler pCallbackFunc);
        [DllImport("LineUSBManager.dll", EntryPoint = "ReceiveMessage", CallingConvention = CallingConvention.Cdecl)]
        extern static bool ReceiveMessage(int Message);

        [DllImport("LineUSBManager.dll", EntryPoint = "TestLight", CallingConvention = CallingConvention.Cdecl)]
        public extern static bool TestLight(int message);

        private static void ReceiveInputPulseCallBack(int money)
        {
            bool returnMessage = ReceiveMessage(money);
            count.issue();
        }
        public static void GetUsb()//把其放入线程
        {
            try
            {
                iph = new InputPulseHandler(ReceiveInputPulseCallBack);
                InputPulse(iph);
                //loghelper.Instance.WriteLog(null,"Enter Enter");
            }
            catch (Exception exc)
            {
            }
        }
        public static void StartReceiver()
        {
            try
            {
                //Count.oldCount = SaveInfomachin.readMoneyText();
                getValue = new Thread(new ThreadStart(GetUsb));
                getValue.Start();
            }
            catch (Exception exc)
            {
                //  loghelper.Instance.WriteLog(exc.GetType(), "加载硬件出错***"+exc.ToString());
            }
        }
    }
}
