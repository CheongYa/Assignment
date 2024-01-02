using PhotoViewer_UserControl;
namespace PthotoViewer_Main
{
    partial class PhotoViewer_Form
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
            Viewer_UserControl uc = new();

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
            textBox1 = new TextBox();
            pathBotton = new Button();
            locationButton = new Button();
            xPosText = new TextBox();
            yPosText = new TextBox();
            angleInputBox = new TextBox();
            angleEditButton = new Button();
            panel1 = new Panel();
            SuspendLayout();
            // 
            // textBox1
            // 
            textBox1.Location = new Point(510, 64);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(217, 23);
            textBox1.TabIndex = 1;
            // 
            // pathBotton
            // 
            pathBotton.Location = new Point(510, 93);
            pathBotton.Name = "pathBotton";
            pathBotton.Size = new Size(121, 40);
            pathBotton.TabIndex = 2;
            pathBotton.Text = "주소 입력";
            pathBotton.UseVisualStyleBackColor = true;
            pathBotton.Click += button1_Click;
            // 
            // locationButton
            // 
            locationButton.Location = new Point(510, 176);
            locationButton.Name = "locationButton";
            locationButton.Size = new Size(121, 40);
            locationButton.TabIndex = 3;
            locationButton.Text = "좌표 입력";
            locationButton.UseVisualStyleBackColor = true;
            locationButton.Click += button2_Click;
            // 
            // xPosText
            // 
            xPosText.Location = new Point(510, 147);
            xPosText.Name = "xPosText";
            xPosText.Size = new Size(94, 23);
            xPosText.TabIndex = 4;
            // 
            // yPosText
            // 
            yPosText.Location = new Point(610, 147);
            yPosText.Name = "yPosText";
            yPosText.Size = new Size(94, 23);
            yPosText.TabIndex = 5;
            // 
            // angleInputBox
            // 
            angleInputBox.Location = new Point(510, 231);
            angleInputBox.Name = "angleInputBox";
            angleInputBox.Size = new Size(217, 23);
            angleInputBox.TabIndex = 8;
            // 
            // angleEditButton
            // 
            angleEditButton.Location = new Point(510, 260);
            angleEditButton.Name = "angleEditButton";
            angleEditButton.Size = new Size(121, 40);
            angleEditButton.TabIndex = 7;
            angleEditButton.Text = "각도 입력";
            angleEditButton.UseVisualStyleBackColor = true;
            angleEditButton.Click += angleEditButton_Click;
            // 
            // panel1
            // 
            panel1.Location = new Point(85, 164);
            panel1.Name = "panel1";
            panel1.Size = new Size(315, 238);
            panel1.TabIndex = 9;
            // 
            // PhotoViewer_Form
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(panel1);
            Controls.Add(angleInputBox);
            Controls.Add(angleEditButton);
            Controls.Add(yPosText);
            Controls.Add(xPosText);
            Controls.Add(locationButton);
            Controls.Add(pathBotton);
            Controls.Add(textBox1);
            Name = "PhotoViewer_Form";
            Text = "Form1";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Viewer_UserControl userControl11;
        private TextBox textBox1;
        private Button pathBotton;
        private Button locationButton;
        private TextBox xPosText;
        private TextBox yPosText;
        private TextBox angleInputBox;
        private Button angleEditButton;
        private Panel panel1;
    }
}