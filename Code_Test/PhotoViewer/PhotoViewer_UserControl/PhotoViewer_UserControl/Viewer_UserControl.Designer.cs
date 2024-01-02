namespace PhotoViewer_UserControl
{
    partial class Viewer_UserControl : UserControl
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
            select_Button = new Button();
            route_Text = new TextBox();
            pictureBox = new PictureBox();
            openFileDialog = new OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)pictureBox).BeginInit();
            SuspendLayout();
            // 
            // select_Button
            // 
            select_Button.Location = new Point(264, 47);
            select_Button.Name = "select_Button";
            select_Button.Size = new Size(139, 44);
            select_Button.TabIndex = 0;
            select_Button.Text = "사진 추가";
            select_Button.UseVisualStyleBackColor = true;
            select_Button.Click += button1_Click;
            // 
            // route_Text
            // 
            route_Text.Location = new Point(214, 18);
            route_Text.Name = "route_Text";
            route_Text.Size = new Size(226, 23);
            route_Text.TabIndex = 1;
            // 
            // pictureBox
            // 
            pictureBox.Location = new Point(3, 3);
            pictureBox.Name = "pictureBox";
            pictureBox.Size = new Size(200, 250);
            pictureBox.SizeMode = PictureBoxSizeMode.Zoom;
            pictureBox.TabIndex = 2;
            pictureBox.TabStop = false;
            // 
            // openFileDialog
            // 
            openFileDialog.FileName = "openFileDialog1";
            openFileDialog.Filter = "사진 파일 (*.jpg)|*.jpg|텍스트 파일 (*.txt)|*.txt|모든 파일 (*.*)|*.*";
            openFileDialog.FilterIndex = 3;
            openFileDialog.InitialDirectory = "C:\\\\";
            openFileDialog.RestoreDirectory = true;
            // 
            // UserControl1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(pictureBox);
            Controls.Add(route_Text);
            Controls.Add(select_Button);
            Name = "UserControl1";
            Size = new Size(461, 260);
            ((System.ComponentModel.ISupportInitialize)pictureBox).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button select_Button;
        private TextBox route_Text;
        private PictureBox pictureBox;
        private OpenFileDialog openFileDialog;
    }
}