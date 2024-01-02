namespace UseUserControl
{
    partial class Form1
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
            flowLayoutPanel1 = new FlowLayoutPanel();
            ageText = new TextBox();
            nameText = new TextBox();
            okButton = new Button();
            addressText = new TextBox();
            SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            flowLayoutPanel1.AutoScroll = true;
            flowLayoutPanel1.Location = new Point(15, 16);
            flowLayoutPanel1.Margin = new Padding(4);
            flowLayoutPanel1.Name = "flowLayoutPanel1";
            flowLayoutPanel1.Size = new Size(423, 631);
            flowLayoutPanel1.TabIndex = 0;
            // 
            // ageText
            // 
            ageText.Font = new Font("맑은 고딕", 18F, FontStyle.Regular, GraphicsUnit.Point);
            ageText.Location = new Point(492, 156);
            ageText.Margin = new Padding(4);
            ageText.Name = "ageText";
            ageText.Size = new Size(169, 47);
            ageText.TabIndex = 8;
            ageText.Text = "나이";
            ageText.Click += ageText_Click;
            // 
            // nameText
            // 
            nameText.Font = new Font("맑은 고딕", 18F, FontStyle.Regular, GraphicsUnit.Point);
            nameText.Location = new Point(492, 81);
            nameText.Margin = new Padding(4);
            nameText.Name = "nameText";
            nameText.Size = new Size(169, 47);
            nameText.TabIndex = 7;
            nameText.Text = "이름";
            nameText.Click += nameText_Click;
            // 
            // okButton
            // 
            okButton.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            okButton.Location = new Point(696, 125);
            okButton.Margin = new Padding(4);
            okButton.Name = "okButton";
            okButton.Size = new Size(221, 127);
            okButton.TabIndex = 6;
            okButton.Text = "사원등록";
            okButton.UseVisualStyleBackColor = true;
            okButton.Click += okButton_Click;
            // 
            // addressText
            // 
            addressText.Font = new Font("맑은 고딕", 18F, FontStyle.Regular, GraphicsUnit.Point);
            addressText.Location = new Point(492, 235);
            addressText.Margin = new Padding(4);
            addressText.Name = "addressText";
            addressText.Size = new Size(169, 47);
            addressText.TabIndex = 9;
            addressText.Text = "주소";
            addressText.Click += addressText_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(9F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(973, 697);
            Controls.Add(addressText);
            Controls.Add(ageText);
            Controls.Add(nameText);
            Controls.Add(okButton);
            Controls.Add(flowLayoutPanel1);
            Margin = new Padding(4);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private FlowLayoutPanel flowLayoutPanel1;
        private TextBox ageText;
        private TextBox nameText;
        private Button okButton;
        private TextBox addressText;
    }
}