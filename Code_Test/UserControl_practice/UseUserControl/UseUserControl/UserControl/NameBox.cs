using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UseUserControl
{
    public partial class NameBox : UserControl
    {
        private readonly string name;
        private readonly int age;
        private readonly string address;

        public NameBox(string name, int age, string address)
        {
            InitializeComponent();
            this.name = name;
            this.age = age;
            this.address = address;

            nameLabel.Text = name;
            ageLabel.Text = age.ToString();
        }

        private void showButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show($"이름: {name}\n나이: {age}\n사는곳: {address}");
        }
    }
}
