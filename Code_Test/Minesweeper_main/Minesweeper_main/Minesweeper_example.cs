using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace Minesweeper
{
	// Form1�� Form�� ��� �޴´�.
	public partial class Form1 : Form
	{
		// �⺻ ���� ����
		private int BTN_SIZE = 23;
		private int MARGINE = 2;
		private int BUTTON_COUNT = 220;
		private int MINE_COUNT = 0;
		private int mine_count = 0;
		private int timerCount;
		// Vector (���ѹ迭)
		public List<List<BTN>> btns = new ();

		// ��ǥ
		private readonly int[,] dydx = new int[8, 2]
		{
			{-1, -1 },  // �»�
			{ -1, 0 },  // ��
			{-1, 1 },   // ���
			{0, 1 },    // ��
			{1, 1 },    // ����
			{1, 0 },    // ��
			{1, -1 },   // ����
			{0, -1 },   // ��
		};  // 71������ �̵�

		public class BTN
		{
			// pos_x, pos_y ��ǥ
			public int pos_x;
			public int pos_y;
			// flase : ������ ��
			// true : ���� ��
			public bool status;
			// �����ΰ�?
			public bool isMine;
			// �ֺ��� ���� ����
			public int count;

			public Button button;

			// ��ư �⺻ ����
			public BTN()
			{
				pos_x = 0;
				pos_y = 0;
				status = false;
				count = 0;
				isMine = false;

				button = new Button();
				button.Text = "";
			}
		};

		// ���� ����
		// �����̳� �ܿ� ��������Ʈ ���Ǹ� ȣ��
		public Form1()
		{
			InitializeComponent();
		}

		// �� �⺻ Ʋ�� �����Ű�� ����
		private void Form1_Load(object sender, EventArgs e)
		{
			gameStart(sender, e);   // 120������ �̵�
		}

		// mine_count label�� ����Ǵ� ����
		private void label1_Click(object sender, EventArgs e)
		{

		}

		// time_count label�� ����Ǵ� ����
		private void label2_Click(object sender, EventArgs e)
		{

		}

		// mine_panel�� ����Ǵ� ����
		private void panel1_Paint(object sender, PaintEventArgs e)
		{

		}

		// timer�� ����Ǵ� ����
		private void timer1_Tick(object sender, EventArgs e)
		{
			// timer �ð��� ������Ų��.
			timerCount++;
			// time_label�� 00:00:00 ǥ�� �������� timerCount / 10 �� �� ������� ����Ѵ�.
			time_label.Text = string.Format("{00:00:00}", timerCount / 10);
		}

		// button�� ����Ǵ� ����
		private void button1_Click(object sender, EventArgs e)
		{

		}

		private void Easy_box_CheckedChanged(object sender, EventArgs e)
		{

		}

		private void Normal_box_CheckedChanged(object sender, EventArgs e)
		{

        }

		private void Hard_box_CheckedChanged(object sender, EventArgs e)
		{

        }

	// ���� ���� �� ���� ����
	// ���� ����
	private void gameStart(object sender, EventArgs e)
		{
			// pos�� idx�� x, y ���� 0���� �ʱ�ȭ
			int pos_x = 0, pos_y = 0;
			int idx_x = 0, idx_y = 0;
			List<BTN> templist = new();

			// panel�� �ʱ�ȭ ��Ų �� ���� ���� �ʱⰪ���� �־���
			this.mine_panel.Controls.Clear();
			this.mine_count = MINE_COUNT;

			// init
			foreach (var tmp in btns)
			{
				tmp.Clear();
			}
			btns.Clear();


			// ��ư�� ����� :) ���� �ٲ۴�.
			this.status_button.Text = ":)";

			for (int i = 0; i <= BUTTON_COUNT; i++)
			{
				BTN temp = new();   // 57������ �̵�

				// ���� �ٷ� �ѱ��
				if (pos_x >= (this.mine_panel.Width - BTN_SIZE))
				{
					// ���ο� �� ��ǥ ����
					idx_x = 0;
					pos_x = 0;
					idx_y++;
					pos_y = pos_y + BTN_SIZE + MARGINE;

					// �ϼ��� ���� ���
					btns.Add(templist);

					// ���ο� �� ����
					templist = new List<BTN>();
				}

				// �ε��� �� ����
				temp.pos_x = idx_x;
				temp.pos_y = idx_y;

				temp.button.Size = new Size(BTN_SIZE, BTN_SIZE);
				temp.button.Location = new Point(pos_x, pos_y);

				// ���Ŀ� �Լ��� ����� ��������� �� 
				temp.button.Click += button1_Click; // �̺�Ʈ ó��
				temp.button.MouseUp += mine_panel_MouseUp;

				//temp.�������Լ�...��¼��

				templist.Add(temp);
				this.mine_panel.Controls.Add(temp.button);

				idx_x++;
				pos_x = ((pos_x + BTN_SIZE + MARGINE) % this.mine_panel.Width);
			}
			btns.Add(templist);
			timer1.Start();
			timerCount = 0;

			plantMine();
			countSurrondingMine();
			mine_label.Text = string.Format("{00}", mine_count);
		}

		private void plantMine()
		{
			Random random = new Random();
			int max_x = btns[0].Count;
			int max_y = btns.Count;
			int i = 0;
			while (i < MINE_COUNT)
			{
				int x = random.Next(0, max_x);
				int y = random.Next(0, max_y);

				// ���ڰ� �ƴ϶��
				if (!btns[y][x].isMine)
				{
					btns[y][x].isMine = true;
					i++;
				}
			}
		}

		private void countSurrondingMine()
		{
			int max_x = btns[0].Count;
			int max_y = btns.Count;

			for (int y = 0; y < max_y; y++)
			{
				for (int x = 0; x < max_x; x++)
				{
					if (!btns[y][x].isMine) continue;
					// �ֺ��� count 1�� �ø�
					for (int t = 0; t < dydx.GetLength(0); t++)
					{
						int dy = dydx[t, 0];
						int dx = dydx[t, 1];

						// ������ �Ѿ�� ��ŵ
						if (x + dx < 0 || max_x <= x + dx) continue;
						if (y + dy < 0 || max_y <= y + dx) continue;

						Button a = btns[y + dy][x + dx].button;

						btns[y + dy][x + dx].count++;

						if (btns[y][x].button.Text == " ")
						{
							btns[y + dy][x + dx].button.Text = btns[y + dy][x + dx].count.ToString();
						}
					}
				}
			}
		}

		private void gameOver()
		{
			this.status_button.Text = ":(";
			for (int y = 0; y < btns.Count; y++)
			{
				for (int x = 0; x < btns.Count; x++)
				{
					if (btns[y][x].isMine)
					{
						btns[y][x].button.Text = "��";
						this.time_label.ForeColor = Color.Red;
						this.mine_label.ForeColor = Color.Red;
						this.timer1.Enabled = false;

					}
				}
			}
		}

		public void gameClear()
		{
			this.status_button.Text = ":D";
			this.time_label.ForeColor = Color.Blue;
			this.mine_label.ForeColor = Color.Blue;
			this.timer1.Enabled = false;
		}

		// ���콺 ���� ����
		// mine_panel�� ���콺�� Ŭ������ �� �Ͼ�� �ൿ
		private void mine_panel_MouseDown(object sender, MouseEventArgs e)
		{
			// ���� ���콺 ���������� ������ ��
			if (e.Button == MouseButtons.Right)
			{
				//this.main_pan.Location.X;
				//���⿡ �ֺ� 8�� ǥ���ϱ�
			}

		}

		// mine_panel���� ���콺�� ������� �� �Ͼ�� �ൿ
		private void mine_panel_MouseUp(object sender, MouseEventArgs e)
		{
			// countrightmien() �Լ��� ȣ���Ѵ�.
			countrightmine();

			// ��Ŭ���� �ؼ� ��ư�� ������ ��
			if (e.Button == MouseButtons.Right)
			{
				int x = 0, y = 0;

				// findButton �Լ����� �޾ƿ� ���� false ��� return �Ѵ�.
				if (!findButton(sender, ref x, ref y)) return;
				// btns[y][x] ��ư�� �Ӽ� Enabled�� false ��� return �Ѵ�.
				if (btns[y][x].button.Enabled == false) return;

				// sender ��ü�� ����Ǿ� �ִ� ���� Control�� ������ȯ ��Ų �� ����Ǿ� �ִ� ���� �Ҷ��
				if ((sender as Control).Text == "��")
				{
					// " " ��, �������� �ٲ� �� mine_count�� ���� 1 ���Ѵ�.
					(sender as Control).Text = " ";
					mine_count += 1;
				}
				else
				{
					// �ƴ϶�� �ҷ� ��ȯ�ϰ� ���� 1 ������.
					(sender as Control).Text = "��";
					mine_count -= 1;
				}
				// mine_label�� mine_count�� ������ ����Ѵ�.
				mine_label.Text = string.Format("{00}", mine_count);
				// countrightmine() �Լ��� ȣ���Ѵ�.
				countrightmine();
			}
			// ���� ���콺�� Ŭ���� �Ǿ��� ���
			else if (e.Button == MouseButtons.Left)
			{
				int x = 0, y = 0;

				// ��ư ã��
				// ��ư�� ã�� ���ߴٸ� ����
				if (!findButton(sender, ref x, ref y)) return;

				// �̹� ��ư�� ���ȴ� ��� ����
				if (btns[y][x].button.Enabled == false) return;

				// �ش� ��ü�� �������� Ȯ��
				// isMine�� ���� false�� ���
				if (!btns[y][x].isMine)
				{
					btns[y][x].button.Text = btns[y][x].count.ToString();
					btns[y][x].button.BackColor = Color.LightGray;
					openButton(x, y);
				}
				// ������ ���
				else
				{
					//btns[y][x]�� ���� �ط� �ٲٰ� ������ �����Ų��.
					btns[y][x].button.Text = "��";
					gameOver();
					return;
				}
				countrightmine();
			}
		}

		public void countrightmine()
		{
			int countflage = 0;
			int countright = 0;

			for (int y = 0; y < btns.Count; y++)
			{
				for (int x = 0; x < btns[0].Count; x++)
				{
					if (btns[y][x].button.Text != "��") continue;
					countflage++;

					if (!btns[y][x].isMine) continue;
					countright++;
				}
			}

			// ���ڸ� ���� ã�� ���
			if (MINE_COUNT == countflage && MINE_COUNT == countright)
			{
				gameClear();
			}
		}

		public void openButton(int x, int y)
		{
			// ����, ���� ����
			int max_x = btns[0].Count;
			int max_y = btns.Count;

			if (!btns[y][x].button.Enabled) return;

			// ��ư�� ��Ȱ��ȭ ��Ų��.
			btns[y][x].button.Enabled = false;
			// �ֺ� ���� ���ڸ� ��ư�� �ؽ�Ʈ�� ǥ���Ѵ�.
			btns[y][x].button.Text = btns[y][x].count.ToString();

			// �ֺ� ���ڰ� ���� ��
			if (btns[y][x].count == 0)
			{
				// dydx�� ��ü �迭 ������ ��ȯ�Ͽ� t�� �׺��� ���� �� �ݺ��Ѵ�.
				for (int t = 0; t < dydx.GetLength(0); t++)
				{
					// dy, dx������ ���� ���� �����Ѵ�.
					int dy = dydx[t, 0];
					int dx = dydx[t, 1];

					// �־��� ��ǥ�� �Ѿ�� ��ŵ�Ѵ�. / Out Of Range ������ ����ֱ� ���Ͽ� �����Ѵ�.
					if (x + dx < 0 || max_x <= x + dx) continue;
					if (y + dy < 0 || max_y <= y + dy) continue;

					// DFS ����Լ��� ���ƴ�.
					openButton(x + dx, y + dy);
				}
			}
		}

		public bool findButton(object sender, ref int x, ref int y)
		{
			for (y = 0; y < btns.Count; y++)
			{
				for (x = 0; x < btns[0].Count; x++)
				{
					if ((sender as Control) == btns[y][x].button) return true;
				}
			}
			return false;
		}
	}
}