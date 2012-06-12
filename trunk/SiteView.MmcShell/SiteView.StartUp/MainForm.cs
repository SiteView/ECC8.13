using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SiteView.MmcShell;
using System.Configuration;

namespace SiteView.StartUp
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            ShellUserControl shell = new ShellUserControl();
            shell.Dock = DockStyle.Fill;
            shell.ShellSetup = ConfigurationManager.GetSection("SiteViewShell")
                as ShellSetup;
            this.Controls.Add(shell);
        }
    }
}
