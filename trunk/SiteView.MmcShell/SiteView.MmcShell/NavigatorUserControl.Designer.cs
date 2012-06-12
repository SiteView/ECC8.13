namespace SiteView.MmcShell
{
    partial class NavigatorUserControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tvNavigator = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // tvNavigator
            // 
            this.tvNavigator.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tvNavigator.Location = new System.Drawing.Point(0, 0);
            this.tvNavigator.Name = "tvNavigator";
            this.tvNavigator.Size = new System.Drawing.Size(268, 379);
            this.tvNavigator.TabIndex = 0;
            // 
            // NavigatorUserControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tvNavigator);
            this.Name = "NavigatorUserControl";
            this.Size = new System.Drawing.Size(268, 379);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView tvNavigator;
    }
}
