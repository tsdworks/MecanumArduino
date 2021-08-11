using System;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;

namespace MecanumController
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private Point moveZeroPosition = new Point(357, 312);
        private readonly int moveMaxRight = 717;
        private readonly int moveMaxTop = 7;
        private readonly int moveMaxLeft = 3;
        private readonly int moveMaxButtom = 629;
        private bool moveFlag = false;
        private int xPos = 0;
        private int yPos = 0;
        private int speedX = 0;
        private int speedY = 0;
        private int radRotate = 0;
        private const int speedXMax = 500;
        private const int speedYMax = 500;
        private const int radRotateMax = 5;
        private double kX = 0;
        private double kY = 0;
        private readonly SerialPort serialSender = new SerialPort();

        private void FormMain_Load(object sender, EventArgs e)
        {
            buttonMove.Location = moveZeroPosition;
            kX = speedXMax * 1.0 / (moveMaxRight - moveMaxLeft) * 2;
            kY = speedYMax * 1.0 / (moveMaxButtom - moveMaxTop) * 2;
            comboBoxSerial.Items.Clear();
            comboBoxSerial.Items.AddRange(SerialPort.GetPortNames());
        }

        private void ButtonMove_MouseMove(object sender, MouseEventArgs e)
        {
            if (moveFlag)
            {
                if (buttonMove.Location.X >= moveMaxLeft && buttonMove.Location.X <= moveMaxRight
                    && buttonMove.Location.Y <= moveMaxButtom && buttonMove.Location.Y >= moveMaxTop)
                {
                    buttonMove.Left += Convert.ToInt16(e.X - xPos);
                    buttonMove.Top += Convert.ToInt16(e.Y - yPos);
                }
            }
        }

        private void ButtonMove_MouseDown(object sender, MouseEventArgs e)
        {
            moveFlag = true;
            xPos = e.X;
            yPos = e.Y;
        }

        private void ButtonMove_MouseUp(object sender, MouseEventArgs e)
        {
            moveFlag = false;
            buttonMove.Location = moveZeroPosition;
        }

        private void TimerEvents_Tick(object sender, EventArgs e)
        {
            double speedXDouble = (buttonMove.Location.X - moveZeroPosition.X) * kX;
            double speedYDouble = -1 * (buttonMove.Location.Y - moveZeroPosition.Y) * kY;
            speedX = Convert.ToInt32(speedXDouble);
            speedY = Convert.ToInt32(speedYDouble);
            textBoxStream.Text = "(1 " + speedY.ToString() + " " + speedX.ToString() + " " + radRotate.ToString() + ")";
            if (serialSender.IsOpen)
            {
                serialSender.Write(textBoxStream.Text);
                buttonConnect.Text = "Close";
            }
            else
            {
                buttonConnect.Text = "Connect";
            }

            if (comboBoxSerial.SelectedIndex == -1)
            {
                buttonConnect.Enabled = false;
            }
            else
            {
                buttonConnect.Enabled = true;
            }
        }

        private void ButtonRotateLeft_MouseDown(object sender, MouseEventArgs e)
        {
            radRotate = radRotateMax;
        }

        private void ButtonRotateLeft_MouseUp(object sender, MouseEventArgs e)
        {
            radRotate = 0;
        }

        private void ButtonRotateRight_MouseUp(object sender, MouseEventArgs e)
        {
            radRotate = 0;
        }

        private void ButtonRotateRight_MouseDown(object sender, MouseEventArgs e)
        {
            radRotate = -1 * radRotateMax;
        }

        private void ButtonConnect_Click(object sender, EventArgs e)
        {
            if (buttonConnect.Text == "Close")
            {
                serialSender.Close();
            }
            else
            {
                try
                {
                    serialSender.PortName = comboBoxSerial.SelectedItem.ToString();
                    serialSender.BaudRate = 19200;
                    serialSender.Open();
                }
                catch (Exception) { };
            }
        }
    }
}
