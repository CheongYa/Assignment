using static Minesweeper_main.Minesweeper_main;
using System;
using System.Security.Cryptography.X509Certificates;
using System.Security.Cryptography.Pkcs;
using System.Collections.Specialized;
using System.Transactions;
using static System.Reflection.Metadata.BlobBuilder;

namespace Minesweeper_main
{
	public partial class Minesweeper_main : Form
	{
		// 기본 설정 구간
		private int button_Size = 44;
		private int real_Mine_Count;
		private int mine_count;
		private int timerCount;
		private int boardSize;
		private bool isGameEnd = false;

		// Vector (무한배열)
		public List<List<Block>> blocks = new List<List<Block>>();

		// 좌표 (좌상부터 좌까지 시계방향)
		private int[,] dydx = new int[8, 2]
		{
			{-1, -1},
			{ -1, 0 },
			{-1, 1 },
			{0, 1 },
			{1, 1 },
			{1, 0 },
			{1, -1 },
			{0, -1 }
		};

		public class Block
		{
			public int pos_x;
			public int pos_y;
			public int aroundMineCount;
			public bool isMine;
			public bool status;
			public Button button;

			// 버튼 기본 정보
			public Block()
			{
				pos_x = 0;
				pos_y = 0;
				aroundMineCount = 0;
				isMine = false;
				status = false;
				button = new Button();
				button.Text = "";
			}
		}

		// panel크기와, 지뢰개수 받음
		public Minesweeper_main(int board, int mine)
		{
			InitializeComponent();
			this.mine_panel.Size = new Size(board, board);
			boardSize = board;
			real_Mine_Count = mine;
			this.mine_count = real_Mine_Count;
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			// panel 크기 설정
			int locX = this.Size.Width / 2 - (mine_panel.Size.Width / 2) - 10;
			int locY = this.Size.Height / 2 - (mine_panel.Size.Height / 2) + 10;
			mine_panel.Location = new Point(locX, locY);

			gameStart();
		}

		// 창의 크기 변경에 따라 panel 크기 설정
		private void Minesweeper_main_Resize(object sender, EventArgs e)
		{
			int locX = this.Size.Width / 2 - (mine_panel.Size.Width / 2) - 10;
			int locY = this.Size.Height / 2 - (mine_panel.Size.Height / 2) + 10;
			mine_panel.Location = new Point(locX, locY);
		}

		// 시간 이벤트
		private void timer1_Tick_1(object sender, EventArgs e)
		{
			timerCount++;
			Time_Label.Text = string.Format("{00:00:00}", timerCount / 10);
		}

		// 표정 버튼 이벤트
		private void Status_button_Click(object sender, EventArgs e)
		{
			Init();
		}

		// 게임 시작
		private void gameStart()
		{
			this.Status_button.Text = ":)";
			MakeMap();
			DrawMap();
			BuriedMine();
			CountSurrondingMine();
			timer1.Start();
			timerCount = 0;
			Mine_Label.Text = $"{real_Mine_Count}";
		}

		// 게임 성공
		private void gameClear()
		{
			this.Status_button.Text = ":D";
			this.Time_Label.ForeColor = Color.Blue;
			this.Mine_Label.ForeColor = Color.Blue;
			timer1.Enabled = false;
		}

		// 게임 실패
		private void gameOver()
		{
			this.Status_button.Text = ":(";
			for (int y = 0; y < blocks.Count; y++)
			{
				for (int x = 0; x < blocks.Count; x++)
				{
					if (!blocks[y][x].isMine)
						continue;
					blocks[y][x].button.Text = "※";
					this.Time_Label.ForeColor = Color.Red;
					this.Mine_Label.ForeColor = Color.Red;
					timer1.Enabled = false;
				}
			}
			isGameEnd = true;
		}

		// 초기화
		void Init()
		{
			this.Time_Label.ForeColor = Color.Black;
			this.Mine_Label.ForeColor = Color.Black;

			this.mine_count = real_Mine_Count;

			mine_panel.Controls.Clear();
			blocks.Clear();
			isGameEnd = false;
			gameStart();
		}

		private void MakeMap()
		{
			int lenght = boardSize / button_Size;
			for (int y = 0; y < lenght; y++)
			{
				List<Block> buttonlist = new List<Block>();
				for (int x = 0; x < lenght; x++)
				{
					Block button = new Block();
					button.pos_x = x;
					button.pos_y = y;

					buttonlist.Add(button);
				}
				blocks.Add(buttonlist);
			}
		}

		private void DrawMap()
		{
			foreach (var btn in blocks)
			{
				foreach (var b in btn)
				{
					Button mineButton = b.button;

					mineButton.Size = new Size(button_Size, button_Size);
					mineButton.Location = new Point(b.pos_x * button_Size, b.pos_y * button_Size);

					mineButton.MouseUp += Panel1_MouseUp;

					this.mine_panel.Controls.Add(b.button);
				}
			}
		}

		public void BuriedMine()
		{
			Random random = new Random();

			int width = blocks[0].Count;
			int height = blocks.Count;
			int plantCount = 0;

			while (plantCount != real_Mine_Count)
			{
				int randomX = random.Next(0, blocks[0].Count);
				int randomY = random.Next(0, height);
				Block block = blocks[randomY][randomX];
				if (block.isMine != true)
				{
					block.isMine = true;
					plantCount++;
				}
			}
		}

		private void CountSurrondingMine()
		{
			int max_x = blocks[0].Count;
			int max_y = blocks.Count;

			for (int y = 0; y < max_y; y++)
			{
				for (int x = 0; x < max_x; x++)
				{
					if (!blocks[y][x].isMine) continue;
					// 주변의 count 1씩 늘림
					for (int t = 0; t < dydx.GetLength(0); t++)
					{
						int dy = dydx[t, 0];
						int dx = dydx[t, 1];

						// 범위를 넘어가면 스킵
						if (x + dx < 0 || max_x <= x + dx) continue;
						if (y + dy < 0 || max_y <= y + dy) continue;

						Button a = blocks[y + dy][x + dx].button;

						blocks[y + dy][x + dx].aroundMineCount++;

						if (blocks[y][x].button.Text == " ")
						{
							blocks[y + dy][x + dx].button.Text = blocks[y + dy][x + dx].aroundMineCount.ToString();
						}
					}
				}
			}
		}

		// 마우스 이벤트
		private void Panel1_MouseUp(object sender, MouseEventArgs e)
		{
			CountRightMine();
			if (this.isGameEnd) return;

			if (e.Button == MouseButtons.Right)
			{
				int x = 0, y = 0;

				if (!FindButton(sender, ref x, ref y)) return;
				if (blocks[y][x].button.Enabled == false) return;

				if ((sender as Control).Text == "¶")
				{
					(sender as Control).Text = " ";
					mine_count += 1;
				}
				else
				{
					(sender as Control).Text = "¶";
					mine_count -= 1;
				}
				Mine_Label.Text = string.Format("{00}", mine_count);
				CountRightMine();
			}
			else if (e.Button == MouseButtons.Left)
			{
				int x = 0, y = 0;

				if (!FindButton(sender, ref x, ref y)) return;
				if (blocks[y][x].button.Enabled == false) return;

				if (!blocks[y][x].isMine)
				{
					blocks[y][x].button.Text = blocks[y][x].aroundMineCount.ToString();
					blocks[y][x].button.BackColor = Color.LightGray;
					OpenButton(x, y);
				}
				else
				{
					blocks[y][x].button.Text = "※";
					gameOver();
					return;
				}
			}
			CountRightMine();
		}

		public void CountRightMine()
		{
			int flagCount = 0;
			int countright = 0;

			for (int y = 0; y < blocks.Count; y++)
			{
				for (int x = 0; x < blocks[0].Count; x++)
				{
					if (blocks[y][x].button.Text != "¶") continue;
					flagCount++;

					if (!blocks[y][x].isMine) continue;
					countright++;
				}
			}

			// 지뢰를 전부 찾은 경우
			if (real_Mine_Count == flagCount && real_Mine_Count == countright)
			{
				gameClear();
			}
		}

		public void OpenButton(int x, int y)
		{
			int max_x = blocks[0].Count;
			int max_y = blocks.Count;

			if (!blocks[y][x].button.Enabled) return;

			blocks[y][x].button.Enabled = false;
			blocks[y][x].button.Text = blocks[y][x].aroundMineCount.ToString();

			if (blocks[y][x].aroundMineCount == 0)
			{
				for (int t = 0; t < dydx.GetLength(0); t++)
				{
					int dy = dydx[t, 0];
					int dx = dydx[t, 1];

					if (x + dx < 0 || max_x <= x + dx) continue;
					if (y + dy < 0 || max_y <= y + dy) continue;

					OpenButton(x + dx, y + dy);
				}
			}
		}

		public bool FindButton(object sender, ref int x, ref int y)
		{
			for (y = 0; y < blocks.Count; y++)
			{
				for (x = 0; x < blocks[0].Count; x++)
				{
					if ((sender as Control) == blocks[y][x].button) return true;
				}
			}
			return false;
		}
	}
}