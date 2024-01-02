using Microsoft.VisualBasic.ApplicationServices;
using PhotoViewer_UserControl;
namespace PthotoViewer_Main
{
    public partial class PhotoViewer_Form : Form
    {
        private Viewer_UserControl photoViewer_UI;

        public PhotoViewer_Form()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            photoViewer_UI = new Viewer_UserControl(@"C:\Users\chch4\Desktop\c20556fee77525a3.jpg");
            photoViewer_UI.setLocation(new Point(0, 0));
            this.Controls.Add(photoViewer_UI);

            PhotoViewer_UserControl.Viewer_UserControl photoViewer_ = new();
            this.panel1.Contains(photoViewer_);

            photoViewer_.setImage(@"C:\\Users\\chch4\\Desktop\\c20556fee77525a3.jpg");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            photoViewer_UI.setImage(textBox1.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int xPos = int.Parse(xPosText.Text);
            int yPos = int.Parse(yPosText.Text);
            photoViewer_UI.setLocation(new Point(xPos, yPos));
        }

        private void angleEditButton_Click(object sender, EventArgs e)
        {
            float angle = float.Parse(angleInputBox.Text);
            photoViewer_UI.setAngle(angle);
        }
    }
}