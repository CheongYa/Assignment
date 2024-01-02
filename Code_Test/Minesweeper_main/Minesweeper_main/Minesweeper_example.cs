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
	// Form1에 Form을 상속 받는다.
	public partial class Form1 : Form
	{
		// 기본 설정 구간
		private int BTN_SIZE = 23;
		private int MARGINE = 2;
		private int BUTTON_COUNT = 220;
		private int MINE_COUNT = 0;
		private int mine_count = 0;
		private int timerCount;
		// Vector (무한배열)
		public List<List<BTN>> btns = new ();

		// 좌표
		private readonly int[,] dydx = new int[8, 2]
		{
			{-1, -1 },  // 좌상
			{ -1, 0 },  // 상
			{-1, 1 },   // 우상
			{0, 1 },    // 우
			{1, 1 },    // 우하
			{1, 0 },    // 하
			{1, -1 },   // 좌하
			{0, -1 },   // 좌
		};  // 71행으로 이동

		public class BTN
		{
			// pos_x, pos_y 좌표
			public int pos_x;
			public int pos_y;
			// flase : 눌리기 전
			// true : 눌린 후
			public bool status;
			// 지뢰인가?
			public bool isMine;
			// 주변의 지뢰 숫자
			public int count;

			public Button button;

			// 버튼 기본 정보
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

		// 실행 구간
		// 디자이너 단에 폼컴포넌트 정의를 호출
		public Form1()
		{
			InitializeComponent();
		}

		// 폼 기본 틀에 적용시키는 공간
		private void Form1_Load(object sender, EventArgs e)
		{
			gameStart(sender, e);   // 120행으로 이동
		}

		// mine_count label에 적용되는 공간
		private void label1_Click(object sender, EventArgs e)
		{

		}

		// time_count label에 적용되는 공간
		private void label2_Click(object sender, EventArgs e)
		{

		}

		// mine_panel에 적용되는 공간
		private void panel1_Paint(object sender, PaintEventArgs e)
		{

		}

		// timer에 적용되는 공간
		private void timer1_Tick(object sender, EventArgs e)
		{
			// timer 시간을 증가시킨다.
			timerCount++;
			// time_label에 00:00:00 표기 형식으로 timerCount / 10 을 한 결과값을 출력한다.
			time_label.Text = string.Format("{00:00:00}", timerCount / 10);
		}

		// button에 적용되는 공간
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

	// 게임 진행 및 종료 구간
	// 게임 시작
	private void gameStart(object sender, EventArgs e)
		{
			// pos와 idx의 x, y 값을 0으로 초기화
			int pos_x = 0, pos_y = 0;
			int idx_x = 0, idx_y = 0;
			List<BTN> templist = new();

			// panel을 초기화 시킨 후 지뢰 갯수 초기값으로 넣어줌
			this.mine_panel.Controls.Clear();
			this.mine_count = MINE_COUNT;

			// init
			foreach (var tmp in btns)
			{
				tmp.Clear();
			}
			btns.Clear();


			// 버튼의 출력을 :) 으로 바꾼다.
			this.status_button.Text = ":)";

			for (int i = 0; i <= BUTTON_COUNT; i++)
			{
				BTN temp = new();   // 57행으로 이동

				// 다음 줄로 넘기기
				if (pos_x >= (this.mine_panel.Width - BTN_SIZE))
				{
					// 새로운 줄 좌표 갱신
					idx_x = 0;
					pos_x = 0;
					idx_y++;
					pos_y = pos_y + BTN_SIZE + MARGINE;

					// 완성된 줄을 등록
					btns.Add(templist);

					// 새로운 줄 생성
					templist = new List<BTN>();
				}

				// 인덱스 값 저장
				temp.pos_x = idx_x;
				temp.pos_y = idx_y;

				temp.button.Size = new Size(BTN_SIZE, BTN_SIZE);
				temp.button.Location = new Point(pos_x, pos_y);

				// 이후에 함수를 만들어 변경해줘야 함 
				temp.button.Click += button1_Click; // 이벤트 처리
				temp.button.MouseUp += mine_panel_MouseUp;

				//temp.릴리즈함수...어쩌고

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

				// 지뢰가 아니라면
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
					// 주변의 count 1씩 늘림
					for (int t = 0; t < dydx.GetLength(0); t++)
					{
						int dy = dydx[t, 0];
						int dx = dydx[t, 1];

						// 범위를 넘어가면 스킵
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
						btns[y][x].button.Text = "※";
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

		// 마우스 동작 구간
		// mine_panel을 마우스로 클릭했을 때 일어나는 행동
		private void mine_panel_MouseDown(object sender, MouseEventArgs e)
		{
			// 만약 마우스 오른쪽으로 눌렀을 때
			if (e.Button == MouseButtons.Right)
			{
				//this.main_pan.Location.X;
				//여기에 주변 8개 표시하기
			}

		}

		// mine_panel에서 마우스를 떼어냈을 때 일어나는 행동
		private void mine_panel_MouseUp(object sender, MouseEventArgs e)
		{
			// countrightmien() 함수를 호출한다.
			countrightmine();

			// 우클릭을 해서 버튼을 눌렀을 때
			if (e.Button == MouseButtons.Right)
			{
				int x = 0, y = 0;

				// findButton 함수에서 받아온 값이 false 라면 return 한다.
				if (!findButton(sender, ref x, ref y)) return;
				// btns[y][x] 버튼의 속성 Enabled이 false 라면 return 한다.
				if (btns[y][x].button.Enabled == false) return;

				// sender 객체에 저장되어 있는 값을 Control로 강제변환 시킨 후 저장되어 있는 값이 ¶라면
				if ((sender as Control).Text == "¶")
				{
					// " " 즉, 공백으로 바꾼 후 mine_count의 값을 1 더한다.
					(sender as Control).Text = " ";
					mine_count += 1;
				}
				else
				{
					// 아니라면 ¶로 변환하고 값을 1 빼낸다.
					(sender as Control).Text = "¶";
					mine_count -= 1;
				}
				// mine_label에 mine_count의 갯수를 출력한다.
				mine_label.Text = string.Format("{00}", mine_count);
				// countrightmine() 함수를 호출한다.
				countrightmine();
			}
			// 왼쪽 마우스가 클릭이 되었을 경우
			else if (e.Button == MouseButtons.Left)
			{
				int x = 0, y = 0;

				// 버튼 찾기
				// 버튼을 찾지 못했다면 종료
				if (!findButton(sender, ref x, ref y)) return;

				// 이미 버튼이 눌렸던 경우 종료
				if (btns[y][x].button.Enabled == false) return;

				// 해당 객체가 지뢰인지 확인
				// isMine의 값이 false일 경우
				if (!btns[y][x].isMine)
				{
					btns[y][x].button.Text = btns[y][x].count.ToString();
					btns[y][x].button.BackColor = Color.LightGray;
					openButton(x, y);
				}
				// 지뢰인 경우
				else
				{
					//btns[y][x]의 값을 ※로 바꾸고 게임을 종료시킨다.
					btns[y][x].button.Text = "※";
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
					if (btns[y][x].button.Text != "¶") continue;
					countflage++;

					if (!btns[y][x].isMine) continue;
					countright++;
				}
			}

			// 지뢰를 전부 찾은 경우
			if (MINE_COUNT == countflage && MINE_COUNT == countright)
			{
				gameClear();
			}
		}

		public void openButton(int x, int y)
		{
			// 가로, 세로 갯수
			int max_x = btns[0].Count;
			int max_y = btns.Count;

			if (!btns[y][x].button.Enabled) return;

			// 버튼을 비활성화 시킨다.
			btns[y][x].button.Enabled = false;
			// 주변 지뢰 숫자를 버튼의 텍스트로 표시한다.
			btns[y][x].button.Text = btns[y][x].count.ToString();

			// 주변 지뢰가 없을 때
			if (btns[y][x].count == 0)
			{
				// dydx의 전체 배열 갯수를 반환하여 t가 그보다 작을 때 반복한다.
				for (int t = 0; t < dydx.GetLength(0); t++)
				{
					// dy, dx변수에 변위 값을 대입한다.
					int dy = dydx[t, 0];
					int dx = dydx[t, 1];

					// 주어진 좌표를 넘어가면 스킵한다. / Out Of Range 오류를 잡아주기 위하여 생략한다.
					if (x + dx < 0 || max_x <= x + dx) continue;
					if (y + dy < 0 || max_y <= y + dy) continue;

					// DFS 재귀함수가 사용됐다.
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