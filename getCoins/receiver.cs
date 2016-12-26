using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace getCoins
{
    public class receiver
    {
        private delegate void InputPulseHandler([MarshalAs(UnmanagedType.I4)]int key, [MarshalAs(UnmanagedType.I4)]int money, [MarshalAs(UnmanagedType.I4)]int error);
        private static InputPulseHandler iph;

        private static Thread getValue;

        [DllImport("HMDUSBManager.dll", EntryPoint = "HMDInputPulse", CallingConvention = CallingConvention.Cdecl)]
        extern static bool InputPulse(InputPulseHandler pCallbackFunc);//([MarshalAs(UnmanagedType.FunctionPtr)] InputPulseHandler pCallbackFunc);
        [DllImport("HMDUSBManager.dll", EntryPoint = "ReceiveMessage", CallingConvention = CallingConvention.Cdecl)]
        extern static bool ReceiveMessage(int Message);
         
        private static void ReceiveInputPulseCallBack(int key, int money, int error)
        {
            bool returnMessage = ReceiveMessage(key);
            if (key == 0)
            {
                //count.issue();
                return;
            }
            if (count.oldCount != key)
            {
                count.oldCount = key;
                count.issue();
            }
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
