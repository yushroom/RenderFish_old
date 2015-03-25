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
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Windows.Forms;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private EditorAppCore _core;

        public MainWindow()
        {
            InitializeComponent();
        }

        public void WindowLoaded(object sender, RoutedEventArgs e)
        {
            IntPtr wnd = editor_wnd.Handle;
            _core = new EditorAppCore(wnd);

            CompositionTarget.Rendering += this.MainWindowIdle;
        }

        void MainWindowUnloaded(object sender, RoutedEventArgs e)
        {
            CompositionTarget.Rendering -= this.MainWindowIdle;
            _core.Destroy();
        }

        private void MainWindowIdle(object sender, EventArgs e)
        {
            _core.Refresh();
        }

        private void EditorWindowSizeChanged(object sender, SizeChangedEventArgs e)
        {
            editor_frame.Width = editor_bg.ActualWidth;
            editor_frame.Height = editor_bg.ActualHeight;

            // unknown bug
            //_core.Resize((uint)editor_frame.Width, (uint)editor_frame.Height);
        }
    }
}
