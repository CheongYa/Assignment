namespace Minesweeper_main
{
    partial class Minesweeper_main
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
            components = new System.ComponentModel.Container();
            Status_button = new Button();
            Mine_Label = new Label();
            timer1 = new System.Windows.Forms.Timer(components);
            mine_panel = new Panel();
            Time_Label = new Label();
            SuspendLayout();
            // 
            // Status_button
            // 
            Status_button.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            Status_button.Location = new Point(213, 27);
            Status_button.Margin = new Padding(2);
            Status_button.Name = "Status_button";
            Status_button.Size = new Size(73, 68);
            Status_button.TabIndex = 0;
            Status_button.Text = ":)";
            Status_button.UseVisualStyleBackColor = true;
            Status_button.Click += Status_button_Click;
            // 
            // Mine_Label
            // 
            Mine_Label.AutoSize = true;
            Mine_Label.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            Mine_Label.Location = new Point(92, 40);
            Mine_Label.Margin = new Padding(2, 0, 2, 0);
            Mine_Label.Name = "Mine_Label";
            Mine_Label.Size = new Size(89, 42);
            Mine_Label.TabIndex = 1;
            Mine_Label.Text = "Mine";
            // 
            // timer1
            // 
            timer1.Tick += timer1_Tick_1;
            // 
            // mine_panel
            // 
            mine_panel.Location = new Point(23, 113);
            mine_panel.Margin = new Padding(2);
            mine_panel.Name = "mine_panel";
            mine_panel.Size = new Size(440, 440);
            mine_panel.TabIndex = 3;
            mine_panel.MouseUp += Panel1_MouseUp;
            // 
            // Time_Label
            // 
            Time_Label.AutoSize = true;
            Time_Label.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            Time_Label.Location = new Point(327, 40);
            Time_Label.Margin = new Padding(2, 0, 2, 0);
            Time_Label.Name = "Time_Label";
            Time_Label.Size = new Size(87, 42);
            Time_Label.TabIndex = 4;
            Time_Label.Text = "Time";
            // 
            // Minesweeper_main
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(484, 661);
            Controls.Add(Time_Label);
            Controls.Add(mine_panel);
            Controls.Add(Mine_Label);
            Controls.Add(Status_button);
            Name = "Minesweeper_main";
            Text = "지뢰찾기";
            Load += Form1_Load;
            Resize += Minesweeper_main_Resize;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button Status_button;
        private Label Mine_Label;
        private System.Windows.Forms.Timer timer1;
        public Panel mine_panel;
        private Label Time_Label;
    }
}