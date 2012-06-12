namespace Logistics
{
    namespace SubServer
    {
        partial class Main
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
                this.tabClientConn = new System.Windows.Forms.TabControl();
                this.btnStart = new System.Windows.Forms.Button();
                this.btnStop = new System.Windows.Forms.Button();
                this.SuspendLayout();
                // 
                // tabClientConn
                // 
                this.tabClientConn.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                            | System.Windows.Forms.AnchorStyles.Left)
                            | System.Windows.Forms.AnchorStyles.Right)));
                this.tabClientConn.Location = new System.Drawing.Point(12, 28);
                this.tabClientConn.Name = "tabClientConn";
                this.tabClientConn.SelectedIndex = 0;
                this.tabClientConn.Size = new System.Drawing.Size(640, 317);
                this.tabClientConn.TabIndex = 0;
                // 
                // btnStart
                // 
                this.btnStart.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
                this.btnStart.Location = new System.Drawing.Point(149, 352);
                this.btnStart.Name = "btnStart";
                this.btnStart.Size = new System.Drawing.Size(75, 23);
                this.btnStart.TabIndex = 1;
                this.btnStart.Text = "Start";
                this.btnStart.UseVisualStyleBackColor = true;
                this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
                // 
                // btnStop
                // 
                this.btnStop.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
                this.btnStop.Enabled = false;
                this.btnStop.Location = new System.Drawing.Point(293, 351);
                this.btnStop.Name = "btnStop";
                this.btnStop.Size = new System.Drawing.Size(75, 23);
                this.btnStop.TabIndex = 2;
                this.btnStop.Text = "Stop";
                this.btnStop.UseVisualStyleBackColor = true;
                this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
                // 
                // Main
                // 
                this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
                this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
                this.ClientSize = new System.Drawing.Size(664, 392);
                this.Controls.Add(this.btnStop);
                this.Controls.Add(this.btnStart);
                this.Controls.Add(this.tabClientConn);
                this.Name = "Main";
                this.Text = "Main";
                this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Main_FormClosing);
                this.ResumeLayout(false);

            }

            #endregion

            private System.Windows.Forms.TabControl tabClientConn;
            private System.Windows.Forms.Button btnStart;
            private System.Windows.Forms.Button btnStop;

        }
    }
}