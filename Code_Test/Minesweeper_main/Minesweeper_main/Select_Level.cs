using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

// 난이도 선택하는 폼
namespace Minesweeper_main
{
    public partial class Select_Level : Form
    {
        public Select_Level()
        {
            InitializeComponent();
        }

        private void Select_Level_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            showForm(220, 5); // 5 * 5
        }

        private void button2_Click(object sender, EventArgs e)
        {
            showForm(352, 10); // 8 * 8
        }

        private void button3_Click(object sender, EventArgs e)
        {
            showForm(440, 15); // 10 * 10
        }

        /// <summary>
        /// panel 사이즈 변경과 main 불러오기
        /// </summary>
        /// <param name="boardsize"></param>
        private void showForm(int boardsize, int mineCount)
        {
            Minesweeper_main main = new Minesweeper_main(boardsize, mineCount);

            main.Show();
        }
    }
}
