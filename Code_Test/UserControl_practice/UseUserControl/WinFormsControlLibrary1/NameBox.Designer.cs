namespace UseUserControl
{
    partial class NameBox
    {
        /// <summary> 
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 구성 요소 디자이너에서 생성한 코드

        /// <summary> 
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            showButton = new Button();
            ageLabel = new Label();
            nameLabel = new Label();
            SuspendLayout();
            // 
            // showButton
            // 
            showButton.Font = new Font("맑은 고딕", 21F, FontStyle.Regular, GraphicsUnit.Point);
            showButton.Location = new Point(147, 35);
            showButton.Name = "showButton";
            showButton.Size = new Size(138, 95);
            showButton.TabIndex = 0;
            showButton.Text = "상세보기";
            showButton.UseVisualStyleBackColor = true;
            showButton.Click += showButton_Click;
            // 
            // ageLabel
            // 
            ageLabel.AutoSize = true;
            ageLabel.Font = new Font("맑은 고딕", 21F, FontStyle.Regular, GraphicsUnit.Point);
            ageLabel.Location = new Point(47, 92);
            ageLabel.Name = "ageLabel";
            ageLabel.Size = new Size(64, 38);
            ageLabel.TabIndex = 1;
            ageLabel.Text = "age";
            // 
            // nameLabel
            // 
            nameLabel.AutoSize = true;
            nameLabel.Font = new Font("맑은 고딕", 21F, FontStyle.Regular, GraphicsUnit.Point);
            nameLabel.Location = new Point(37, 35);
            nameLabel.Name = "nameLabel";
            nameLabel.Size = new Size(88, 38);
            nameLabel.TabIndex = 2;
            nameLabel.Text = "name";
            // 
            // NameBox
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(nameLabel);
            Controls.Add(ageLabel);
            Controls.Add(showButton);
            Name = "NameBox";
            Size = new Size(304, 163);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button showButton;
        private Label ageLabel;
        private Label nameLabel;
    }
}
