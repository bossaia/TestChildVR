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
    /// MusicCheck.xaml 的交互逻辑
    /// </summary>
    public partial class MusicCheck : Window
    {
        private static bool _isfirstload = true;
        public  string leftVoiceCheck ="不合格";
        public  string rightVoiceCheck = "不合格";
        private MediaPlayer mediaPlayer = new MediaPlayer();
        public MusicCheck()
        {
            InitializeComponent();
        }

        private void InitlizeMusic()
        {
            if (_isfirstload)
            {
                mediaPlayer.Open(new Uri(AppDomain.CurrentDomain.BaseDirectory + "music/test.mp3", UriKind.Absolute));
                mediaPlayer.MediaEnded += mediaPlayer_MediaEnded;
                mediaPlayer.Play();
                _isfirstload = false;
            }
            else
            {
                mediaPlayer.Play();
            }
        }

        void mediaPlayer_MediaEnded(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
            mediaPlayer.Position =TimeSpan.Zero;
            mediaPlayer.Play();
        }

        private void MusicCheck_OnIsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if (this.Visibility == Visibility.Visible)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.leftvoice.IsChecked = false;
                    this.rightvoice.IsChecked = false;
                    leftVoiceCheck = "不合格";
                    rightVoiceCheck = "不合格";
                }));
                InitlizeMusic();
            }
            if (this.Visibility == Visibility.Hidden)
            {
                mediaPlayer.Pause();
            }
            // throw new NotImplementedException();
        }

        private void Leftvoice_OnIsCheckedChanged(object sender, EventArgs e)
        {
          //  throw new NotImplementedException();
            // Console.WriteLine(this.leftvoice.IsChecked.Value);
            if (this.leftvoice.IsChecked.Value)
            {
                leftVoiceCheck = "合格";
            }
        }

        private void Rightvoice_OnIsCheckedChanged(object sender, EventArgs e)
        {
           // throw new NotImplementedException();
            if (this.rightvoice.IsChecked.Value)
            {
                rightVoiceCheck = "合格";
            }
        }

        private void Done_OnClick(object sender, RoutedEventArgs e)
        {
            //
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Visibility=Visibility.Hidden;
            }));
        }

        private void Left_button_OnClick(object sender, RoutedEventArgs e)
        {
          //  throw new NotImplementedException();
            mediaPlayer.Balance = -1000;
        }

        private void Right_button_OnClick(object sender, RoutedEventArgs e)
        {
           // throw new NotImplementedException();
            mediaPlayer.Balance = 1000;
        }
    }
}
