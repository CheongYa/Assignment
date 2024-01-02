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
                MessageBox.Show($"���ڸ� �Է����ּ���.");
                return;
            }
            string address = addressText.Text;

            NameBox namebox = new NameBox(name, age, address);
            flowLayoutPanel1.Controls.Add(namebox);
        }

        private void nameText_Click(object sender, EventArgs e)
        {
            if (nameText.Text == "�̸�")
                nameText.Text = string.Empty;
        }

        private void ageText_Click(object sender, EventArgs e)
        {
            if (ageText.Text == "����")
                ageText.Text = string.Empty;
        }

        private void addressText_Click(object sender, EventArgs e)
        {
            if (addressText.Text == "�ּ�")
                addressText.Text = string.Empty;
        }
    }
}