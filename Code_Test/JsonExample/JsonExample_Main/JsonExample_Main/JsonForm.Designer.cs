namespace JsonExample_Main
{
    partial class JsonForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            jsonUserControl1 = new JsonExample_UC.JsonUserControl();
            SuspendLayout();
            // 
            // jsonUserControl1
            // 
            jsonUserControl1.Location = new Point(304, 60);
            jsonUserControl1.Name = "jsonUserControl1";
            jsonUserControl1.Size = new Size(1079, 665);
            jsonUserControl1.TabIndex = 0;
            // 
            // JsonForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1222, 760);
            Controls.Add(jsonUserControl1);
            Name = "JsonForm";
            Text = "Form1";
            ResumeLayout(false);
        }

        #endregion

        private JsonExample_UC.JsonUserControl jsonUserControl1;
    }
}