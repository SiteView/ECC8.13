using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace SiteView.StartUp
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
#if RELEASE
            LoginForm loginForm = new LoginForm();
            if (DialogResult.OK == loginForm.ShowDialog())
#endif
            Application.Run(new MainForm());
        }
    }
}
