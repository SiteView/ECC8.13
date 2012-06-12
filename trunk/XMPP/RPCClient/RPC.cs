using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using RPCClient;
using System.Diagnostics;

namespace RPCClient
{
    public partial class RPC : Form
    {
        public RPC()
        {
            InitializeComponent();
        }

        private void RPC_Load(object sender, EventArgs e)
        {
            this.btnInit.Enabled = true;
            this.btnExit.Enabled = false;
            this.btnGetTreeData.Enabled = false;
        }

        private void btnInit_Click(object sender, EventArgs e)
        {
            RPCWrapper.InitInstance(new agsXMPP.Jid("test@yxd"), "test");

            this.btnInit.Enabled = false;
            this.btnExit.Enabled = true;
            this.btnGetTreeData.Enabled = true;

            this.Text = "";

            watch.Reset();
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            RPCWrapper.ExitInstance();
            this.btnInit.Enabled = true;
            this.btnExit.Enabled = false;
            this.btnGetTreeData.Enabled = false;
        }

        private static Stopwatch watch = new Stopwatch();

        private void btnGetTreeData_Click(object sender, EventArgs e)
        {
            //Stopwatch watch = new Stopwatch();

            watch.Start();

            List<string> ret = MethodWrapper.GetTreeData("test", 100, "description");

            watch.Stop();

            this.Text = watch.ElapsedMilliseconds.ToString();
        }

    }
}