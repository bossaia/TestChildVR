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
    public partial class MusicCheck : UserControl
    {
        private static bool _isfirstload = true;
        public string leftVoiceCheck = "不合格";
        public string rightVoiceCheck = "不合格";
        private MediaPlayer mediaPlayer = new MediaPlayer();
        private bool isplaying = false;
        private Brush b;

        public MusicCheck()
        {
            InitializeComponent();
            b = this.left_button.Background.Clone();
        }

        private void InitlizeMusic()
        {
            mediaPlayer.Open(new Uri(AppDomain.CurrentDomain.BaseDirectory + "music/test.mp3", UriKind.Absolute));
            mediaPlayer.MediaEnded += mediaPlayer_MediaEnded;
            _isfirstload = false;
        }

        void mediaPlayer_MediaEnded(object sender, EventArgs e)
        {
            mediaPlayer.Position = TimeSpan.Zero;
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
        }

        private void Leftvoice_OnIsCheckedChanged(object sender, EventArgs e)
        {
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
            if (!isplaying)
            {
                isplaying = true;
                mediaPlayer.Play();
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    this.leftvoice.Visibility = Visibility.Visible;
                    this.rightvoice.Visibility = Visibility.Visible;
                }));
            }
            else
            {
                mediaPlayer.Pause();
                isplaying = false;
            }
        }

        private void Left_button_OnClick(object sender, RoutedEventArgs e)
        {
            mediaPlayer.Balance = 1000;
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.right_button.Background = b;
                this.left_button.Background=new SolidColorBrush(Colors.Olive);
            }));
        }

        private void Right_button_OnClick(object sender, RoutedEventArgs e)
        {
            mediaPlayer.Balance = -1000;
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.left_button.Background = b;
                this.right_button.Background = new SolidColorBrush(Colors.Olive);
            }));
        }

        public void clear()
        {
            leftVoiceCheck = "不合格";
            rightVoiceCheck = "不合格";
            mediaPlayer.Balance = 0;
            mediaPlayer.Stop();
            this.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.leftvoice.Visibility = Visibility.Hidden;
                this.rightvoice.Visibility = Visibility.Hidden;
                this.leftvoice.IsChecked = false;
                this.rightvoice.IsChecked = false;
            }));
        }
    }
}
