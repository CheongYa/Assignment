namespace UseUserControl
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void okButton_Click(object sender, EventArgs e)
        {
            string name = nameText.Text;
            int age;
            if (!int.TryParse(ageText.Text, out age))
            {
                MessageBox.Show($"숫자만 입력해주세요.");
                return;
            }
            string address = addressText.Text;

            NameBox namebox = new NameBox(name, age, address);
            flowLayoutPanel1.Controls.Add(namebox);
        }

        private void nameText_Click(object sender, EventArgs e)
        {
            if (nameText.Text == "이름")
                nameText.Text = string.Empty;
        }

        private void ageText_Click(object sender, EventArgs e)
        {
            if (ageText.Text == "나이")
                ageText.Text = string.Empty;
        }

        private void addressText_Click(object sender, EventArgs e)
        {
            if (addressText.Text == "주소")
                addressText.Text = string.Empty;
        }
    }
}