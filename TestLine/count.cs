using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestLine
{
    public class count
    {
        public delegate void ReturnMoneyInformation();

        public static event ReturnMoneyInformation OnReturn;

        public static void issue()
        {
            if (OnReturn != null)
            {
                OnReturn();
            }
        }
    }
}
