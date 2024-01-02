using Microsoft.VisualBasic.ApplicationServices;
using System.Security.Cryptography.X509Certificates;
using System.Windows.Forms;

namespace PhotoViewer_UserControl
{
    public partial class Viewer_UserControl : UserControl
    {
        private string? _path;
        private int _angle;
        private Bitmap _picture;

        public Viewer_UserControl() // 생성자
        {
            InitializeComponent();
        }

        /// <summary>
        /// 오버로딩 사용
        /// </summary>
        /// <param name="path"></param>
        public Viewer_UserControl(string path)
        {
            InitializeComponent();
            setImage(path); 
        }

        // ~Viewer_UserControl() { } // 소멸자

        private void button1_Click(object sender, EventArgs e)
        {
            route_Text.Text = String.Empty;
            string filePath = "";

            if (openFileDialog.ShowDialog() != DialogResult.OK)
                return;

            filePath = openFileDialog.FileName;
            route_Text.Text = filePath;
            openFileDialog.Dispose();
            setImage(filePath);
        }

        /// <summary>
        /// 경로를 입력받아 사진을 띄우는 함수
        /// </summary>
        /// <param name="path"></param>
        public void setImage(string path)
        {
            this._path = path;
            this.route_Text.Text = path;
            try
            {
                _picture = new Bitmap(path);
                pictureBox.Image = (Image)_picture.Clone();
            }
            catch
            {
                MessageBox.Show("이미지 파일이 아니거나 파일이 잘못되었습니다.");
            }
        }

        /// <summary>
        /// 위치를 변경해주는 함수
        /// </summary>
        /// <param name="location"></param>
        public void setLocation(Point location)
        {
            this.Location = location;
        }

        /// <summary>
        /// 각도를 변경해주는 함수
        /// </summary>
        public void setAngle(float angle)
        {
            Bitmap oldBitmap = (Bitmap)_picture.Clone();    // pictureBox에 저장되어 있는 이미지를 Bitmap으로 강제변환 시켜 oldBitmap에 넣어준다.
            Bitmap newBitmap = new Bitmap(oldBitmap.Width, oldBitmap.Height);   // oldBitmap의 가로, 세로의 크기를 newBitmap에 넣어준다.
            Graphics graphics = Graphics.FromImage(newBitmap);  // newBitmap의 그림을 그리기 위해 Graphics 클래스를 선언해 메소드를 한다.

            graphics.TranslateTransform(newBitmap.Width / 2, newBitmap.Height / 2); // 중심축을 변경해준다.
            graphics.RotateTransform(angle);    // 외부에서 입력받은 각도 만큼 돌려준다.
            // graphics 즉, newBitmap에 oldBitmap을 그려준다.
            graphics.DrawImage(oldBitmap, -oldBitmap.Width / 2, -oldBitmap.Height / 2, oldBitmap.Width, oldBitmap.Height);

            pictureBox.Image = newBitmap;   // pictureBox에 newBitmap의 결과물을 덮어 씌운다.
            this.Refresh();
        }
    }
}