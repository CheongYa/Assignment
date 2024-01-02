namespace Minesweeper_main
{
    partial class Select_Level
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            level_Label = new Label();
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            SuspendLayout();
            // 
            // level_Label
            // 
            level_Label.AutoSize = true;
            level_Label.Font = new Font("맑은 고딕", 30F, FontStyle.Regular, GraphicsUnit.Point);
            level_Label.Location = new Point(98, 42);
            level_Label.Name = "level_Label";
            level_Label.Size = new Size(143, 54);
            level_Label.TabIndex = 0;
            level_Label.Text = "난이도";
            // 
            // button1
            // 
            button1.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            button1.Location = new Point(62, 116);
            button1.Name = "button1";
            button1.Size = new Size(210, 85);
            button1.TabIndex = 1;
            button1.Text = "easy";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            button2.Location = new Point(62, 207);
            button2.Name = "button2";
            button2.Size = new Size(210, 85);
            button2.TabIndex = 2;
            button2.Text = "normal";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // button3
            // 
            button3.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            button3.Location = new Point(62, 298);
            button3.Name = "button3";
            button3.Size = new Size(210, 85);
            button3.TabIndex = 3;
            button3.Text = "hard";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // Select_Level
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(343, 450);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(level_Label);
            Name = "Select_Level";
            Text = "Select_Level";
            Load += Select_Level_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label level_Label;
        private Button button1;
        private Button button2;
        private Button button3;
    }
}