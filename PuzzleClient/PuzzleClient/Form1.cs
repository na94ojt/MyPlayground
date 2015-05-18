using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PuzzleClient
{
    struct PUZZLE
    {
        public int num;
        public Bitmap puzzlePeace;
    };

    public partial class Form1 : Form
    {
        Size PEACESIZE = new Size(100, 100);
        Size TABLEPEACESIZE = new Size(50, 50);
        int Blank = PEACEQUANTITY-1;
        const int PEACEQUANTITY = 9;
        const int MAXX = 3;
        const int MAXY = 3;

        PUZZLE[] Table = new PUZZLE[PEACEQUANTITY];
        PUZZLE[] Current = new PUZZLE[PEACEQUANTITY];

        PictureBox [] currentPeace = new PictureBox[9];
        PictureBox[] tablePeace = new PictureBox[9];

        private void LoadImage()
        {
            for (int i = 0; i < PEACEQUANTITY; i++ )
            {
                Image Temp = Image.FromFile(@".\peace\peace" + i + ".bmp", true);

                Table[i].num = i;
                Table[i].puzzlePeace = new Bitmap(Temp,TABLEPEACESIZE);

                Current[i].num = i;
                Current[i].puzzlePeace = new Bitmap(Temp, PEACESIZE);
            }
        }

        private void CreatePictureBox()
        {
            int i = 0;

            for (int y = 0; y < MAXY; y++)
            {
                for (int x = 0; x < MAXX; x++ )
                {
                    currentPeace[i] = new PictureBox();
                    currentPeace[i].Location = new System.Drawing.Point(12 + (x * PEACESIZE.Width), 12 + (y * PEACESIZE.Height));
                    currentPeace[i].Name = "peace"+i;
                    currentPeace[i].Image = Current[i].puzzlePeace;
                    currentPeace[i].Size = new System.Drawing.Size(PEACESIZE.Width,PEACESIZE.Height);
                    currentPeace[i].Parent = this;

                    tablePeace[i] = new PictureBox();
                    tablePeace[i].Location = new System.Drawing.Point(575 + (x * TABLEPEACESIZE.Width), 87 + (y * TABLEPEACESIZE.Height));
                    tablePeace[i].Name = "table" + i;
                    tablePeace[i].Image = Table[i].puzzlePeace;
                    tablePeace[i].Size = new System.Drawing.Size(TABLEPEACESIZE.Width,TABLEPEACESIZE.Height);
                    tablePeace[i].Parent = this;
                    i++;
                }
            }
            currentPeace[0].Click += new System.EventHandler(this.OnClickPeace0);
            currentPeace[1].Click += new System.EventHandler(this.OnClickPeace1);
            currentPeace[2].Click += new System.EventHandler(this.OnClickPeace2);
            currentPeace[3].Click += new System.EventHandler(this.OnClickPeace3);
            currentPeace[4].Click += new System.EventHandler(this.OnClickPeace4);
            currentPeace[5].Click += new System.EventHandler(this.OnClickPeace5);
            currentPeace[6].Click += new System.EventHandler(this.OnClickPeace6);
            currentPeace[7].Click += new System.EventHandler(this.OnClickPeace7);
            currentPeace[8].Click += new System.EventHandler(this.OnClickPeace8);
        }
        private void InsertToPictureBox()
        {
            for (int i = 0; i < PEACEQUANTITY; i++ )
            {
                currentPeace[i].Image = Current[i].puzzlePeace;
            }
        }
        private void shupple()
        {
            Random randomize = new Random();

            for (int i = 0; i < 5; i++)
            {
                int n = randomize.Next(4);

                switch (n)
                {
                    case 0:
                        if (Blank % 3 != Blank)
                        {
                            /*Bitmap temp = new Bitmap(Current[Blank - 3].puzzlePeace);
                            Current[Blank].puzzlePeace = temp;
                            Current[Blank - 3].puzzlePeace = null;*/
                            PUZZLE temp = Current[Blank];
                            Current[Blank] = Current[Blank - 3];
                            Current[Blank - 3] = temp;
                            Blank -= 3;
                        }
                        break;
                    case 1:
                        if (0 != Blank % 3)
                        {
                            /*Bitmap temp = new Bitmap(Current[Blank - 1].puzzlePeace);
                            Current[Blank].puzzlePeace = temp;
                            Current[Blank - 1].puzzlePeace = null;*/
                            PUZZLE temp = Current[Blank];
                            Current[Blank] = Current[Blank - 1];
                            Current[Blank - 1] = temp;
                            Blank -= 1;
                        }
                        break;
                    case 2:
                        if (Blank % 3 < 2)
                        {
                            /*Bitmap temp = new Bitmap(Current[Blank + 1].puzzlePeace);
                            Current[Blank].puzzlePeace = temp;
                            Current[Blank + 1].puzzlePeace = null;*/
                            PUZZLE temp = Current[Blank];
                            Current[Blank] = Current[Blank + 1];
                            Current[Blank + 1] = temp;
                            Blank += 1;
                        }
                        break;
                    case 3:
                        if (Blank + 3 < 8)
                        {
                            /*Bitmap temp = new Bitmap(Current[Blank + 3].puzzlePeace);
                            Current[Blank].puzzlePeace = temp;
                            Current[Blank + 3].puzzlePeace = null;*/
                            PUZZLE temp = Current[Blank];
                            Current[Blank] = Current[Blank + 3];
                            Current[Blank + 3] = temp;
                            Blank += 3;
                        }
                        break;
                    default:
                        break;
                }
            }

            InsertToPictureBox();

        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadImage();
            CreatePictureBox();
            shupple();
        }

        /////////////////////////////////////////////////////////////////////////////
        private void OnClickPeace0(object sender, EventArgs e)
        {
            peaceMove(0);
        }
        private void OnClickPeace1(object sender, EventArgs e)
        {
            peaceMove(1);
        }
        private void OnClickPeace2(object sender, EventArgs e)
        {
            peaceMove(2);
        }
        private void OnClickPeace3(object sender, EventArgs e)
        {
            peaceMove(3);
        }
        private void OnClickPeace4(object sender, EventArgs e)
        {
            peaceMove(4);
        }
        private void OnClickPeace5(object sender, EventArgs e)
        {
            peaceMove(5);
        }
        private void OnClickPeace6(object sender, EventArgs e)
        {
            peaceMove(6);
        }
        private void OnClickPeace7(object sender, EventArgs e)
        {
            peaceMove(7);
        }
        private void OnClickPeace8(object sender, EventArgs e)
        {
            peaceMove(8);
        }

        private void peaceMove(int index)
        {
            if (index != Blank)
            {
                if (Blank == index - 3)
                {
                    PUZZLE temp = Current[Blank];
                    Current[Blank] = Current[Blank + 3];
                    Current[Blank + 3] = temp;
                    Blank += 3;
                }
                else if (Blank == index - 1)
                {
                    PUZZLE temp = Current[Blank];
                    Current[Blank] = Current[Blank + 1];
                    Current[Blank + 1] = temp;
                    Blank += 1;
                }
                else if (Blank == index + 1)
                {
                    PUZZLE temp = Current[Blank];
                    Current[Blank] = Current[Blank - 1];
                    Current[Blank - 1] = temp;
                    Blank -= 1;
                }
                else if (Blank == index + 3)
                {
                    PUZZLE temp = Current[Blank];
                    Current[Blank] = Current[Blank - 3];
                    Current[Blank - 3] = temp;
                    Blank -= 3;
                }

                InsertToPictureBox();

                if (true == GameOverCheck())
                {
                    this.GameOver(true);
                    //this.Close();
                }
            }
        }

        private bool GameOverCheck()
        {
            int i;

            for (i = 0; i < PEACEQUANTITY; i++ )
            {
                if (Current[i].num != Table[i].num)
                {
                    return false;
                }
            }
            return true;
        }
        private void GameOver(bool win)
        {
            if (true == win)
            {
                MessageBox.Show("You Win","Result");
                this.Close();
            }
            else
            {
                MessageBox.Show("You Lose","Result");
                this.Close();
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            SendMessage(e.KeyChar);
        }

        private void Enter_Click(object sender, EventArgs e)
        {
            //this.textBox2_KeyPress(e);
            SendMessage('\r');
            
        }

        private void SendMessage(char EnterKey)
        {
            if (EnterKey == '\r')
            {
                this.textBox1.AppendText("Me : " + this.textBox2.Text + "\r\n");
                this.textBox1.ScrollToCaret();
                this.textBox2.Clear();
            }
        }
        
    }
}