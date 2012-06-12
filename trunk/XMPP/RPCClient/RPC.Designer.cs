namespace RPCClient
{
    partial class RPC
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnInit = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.btnGetTreeData = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnInit
            // 
            this.btnInit.Location = new System.Drawing.Point(25, 12);
            this.btnInit.Name = "btnInit";
            this.btnInit.Size = new System.Drawing.Size(84, 23);
            this.btnInit.TabIndex = 0;
            this.btnInit.Text = "Init";
            this.btnInit.UseVisualStyleBackColor = true;
            this.btnInit.Click += new System.EventHandler(this.btnInit_Click);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(162, 12);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(84, 23);
            this.btnExit.TabIndex = 0;
            this.btnExit.Text = "Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // btnGetTreeData
            // 
            this.btnGetTreeData.Location = new System.Drawing.Point(25, 62);
            this.btnGetTreeData.Name = "btnGetTreeData";
            this.btnGetTreeData.Size = new System.Drawing.Size(84, 23);
            this.btnGetTreeData.TabIndex = 1;
            this.btnGetTreeData.Text = "GetTreeData";
            this.btnGetTreeData.UseVisualStyleBackColor = true;
            this.btnGetTreeData.Click += new System.EventHandler(this.btnGetTreeData_Click);
            // 
            // RPC
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(261, 273);
            this.Controls.Add(this.btnGetTreeData);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.btnInit);
            this.Name = "RPC";
            this.Text = "RPC";
            this.Load += new System.EventHandler(this.RPC_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnInit;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Button btnGetTreeData;
    }
}

