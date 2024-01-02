using Newtonsoft.Json;

namespace JsonExample_UC
{
    public partial class JsonUserControl : UserControl
    {
        string jsonString = System.IO.File.ReadAllText(@"C:\Users\chch4\Desktop\Universal Waite Major.json");
        Json json;
        public JsonUserControl()
        {
            InitializeComponent();
        }

        private void numberText_Click(object sender, EventArgs e)
        {
            if (numberText.Text == "숫자를 입력해주세요")
            {
                textClear();
            }
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            findJson();
        }

        public void findJson()
        {
            Setting setting = JsonConvert.DeserializeObject<Setting>(jsonString);

            string consoleInput = numberText.Text;
            int x;
            bool isnum = int.TryParse(consoleInput, out x);
            if (!isnum)
            {
                MessageBox.Show("정수만 입력해주세요.", "오류 발생");
                textClear();
                return;
            }
            if (setting.cards.Count < x)
            {
                MessageBox.Show("카드의 수를 초과하였습니다. 다시 입력해주세요.", "오류 발생");
                textClear();
                return;
            }
            else if (x <= 0)
            {
                MessageBox.Show("1 이상의 값을 입력해주세요.", "오류 발생");
                textClear();
                return;
            }

            Card card = setting.cards[x - 1];
            textClear();
            nameDetail.Text = card.name;
            categoryDetail.Text = card.category;

            int i = 1;
            foreach (string forward in card.forward)
            {
                forwardDetail.Text += forward + ", ";
                if (i % 3 == 0)
                {
                    forwardDetail.Text += "\r";
                }
                i++;
            }
            foreach (string reverse in card.reverse)
            {
                reverseDetail.Text += reverse + ", ";
                if (i % 3 == 0)
                {
                    reverseDetail.Text += "\r";
                }
                i++;
            }
        }

        public void textClear()
        {
            numberText.Text = String.Empty;
            nameDetail.Text = String.Empty;
            categoryDetail.Text = String.Empty;
            forwardDetail.Text = String.Empty;
            reverseDetail.Text = String.Empty;
        }
    }
}