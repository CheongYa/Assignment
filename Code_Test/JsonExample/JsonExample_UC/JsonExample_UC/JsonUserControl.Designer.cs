namespace JsonExample_UC
{
    partial class JsonUserControl
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
            okButton = new Button();
            numberText = new TextBox();
            nameLabel = new Label();
            categoryLabel = new Label();
            forwardLabel = new Label();
            reverseLabel = new Label();
            forwardDetail = new Label();
            nameDetail = new Label();
            categoryDetail = new Label();
            reverseDetail = new Label();
            SuspendLayout();
            // 
            // okButton
            // 
            okButton.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            okButton.Location = new Point(390, 39);
            okButton.Name = "okButton";
            okButton.Size = new Size(109, 48);
            okButton.TabIndex = 0;
            okButton.Text = "확인";
            okButton.UseVisualStyleBackColor = true;
            okButton.Click += okButton_Click;
            // 
            // numberText
            // 
            numberText.Font = new Font("맑은 고딕", 23F, FontStyle.Regular, GraphicsUnit.Point);
            numberText.ForeColor = SystemColors.WindowText;
            numberText.Location = new Point(60, 39);
            numberText.Name = "numberText";
            numberText.Size = new Size(307, 48);
            numberText.TabIndex = 1;
            numberText.Text = "숫자를 입력해주세요";
            numberText.Click += numberText_Click;
            // 
            // nameLabel
            // 
            nameLabel.AutoSize = true;
            nameLabel.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            nameLabel.Location = new Point(27, 150);
            nameLabel.Name = "nameLabel";
            nameLabel.Size = new Size(81, 36);
            nameLabel.TabIndex = 2;
            nameLabel.Text = "name";
            // 
            // categoryLabel
            // 
            categoryLabel.AutoSize = true;
            categoryLabel.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            categoryLabel.Location = new Point(27, 216);
            categoryLabel.Name = "categoryLabel";
            categoryLabel.Size = new Size(118, 36);
            categoryLabel.TabIndex = 3;
            categoryLabel.Text = "category";
            // 
            // forwardLabel
            // 
            forwardLabel.AutoSize = true;
            forwardLabel.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            forwardLabel.Location = new Point(27, 284);
            forwardLabel.Name = "forwardLabel";
            forwardLabel.Size = new Size(106, 36);
            forwardLabel.TabIndex = 4;
            forwardLabel.Text = "forward";
            // 
            // reverseLabel
            // 
            reverseLabel.AutoSize = true;
            reverseLabel.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            reverseLabel.Location = new Point(27, 477);
            reverseLabel.Name = "reverseLabel";
            reverseLabel.Size = new Size(99, 36);
            reverseLabel.TabIndex = 8;
            reverseLabel.Text = "reverse";
            // 
            // forwardDetail
            // 
            forwardDetail.AutoSize = true;
            forwardDetail.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            forwardDetail.Location = new Point(174, 284);
            forwardDetail.Name = "forwardDetail";
            forwardDetail.Size = new Size(0, 36);
            forwardDetail.TabIndex = 10;
            // 
            // nameDetail
            // 
            nameDetail.AutoSize = true;
            nameDetail.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            nameDetail.Location = new Point(174, 150);
            nameDetail.Name = "nameDetail";
            nameDetail.Size = new Size(0, 36);
            nameDetail.TabIndex = 11;
            // 
            // categoryDetail
            // 
            categoryDetail.AutoSize = true;
            categoryDetail.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            categoryDetail.Location = new Point(174, 216);
            categoryDetail.Name = "categoryDetail";
            categoryDetail.Size = new Size(0, 36);
            categoryDetail.TabIndex = 12;
            // 
            // reverseDetail
            // 
            reverseDetail.AutoSize = true;
            reverseDetail.Font = new Font("맑은 고딕", 19F, FontStyle.Regular, GraphicsUnit.Point);
            reverseDetail.Location = new Point(174, 477);
            reverseDetail.Name = "reverseDetail";
            reverseDetail.Size = new Size(0, 36);
            reverseDetail.TabIndex = 13;
            // 
            // JsonUserControl
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(reverseDetail);
            Controls.Add(categoryDetail);
            Controls.Add(nameDetail);
            Controls.Add(forwardDetail);
            Controls.Add(reverseLabel);
            Controls.Add(forwardLabel);
            Controls.Add(categoryLabel);
            Controls.Add(nameLabel);
            Controls.Add(numberText);
            Controls.Add(okButton);
            Name = "JsonUserControl";
            Size = new Size(1079, 665);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button okButton;
        private TextBox numberText;
        private Label nameLabel;
        private Label categoryLabel;
        private Label forwardLabel;
        private Label reverseLabel;
        private Label forwardDetail;
        private Label nameDetail;
        private Label categoryDetail;
        private Label reverseDetail;
    }
}