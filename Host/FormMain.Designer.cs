namespace MecanumController
{
    partial class FormMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.textBoxStream = new System.Windows.Forms.TextBox();
            this.comboBoxSerial = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.panelSpeedFrame = new System.Windows.Forms.Panel();
            this.buttonRotateRight = new System.Windows.Forms.Button();
            this.buttonRotateLeft = new System.Windows.Forms.Button();
            this.buttonMove = new System.Windows.Forms.Button();
            this.timerEvents = new System.Windows.Forms.Timer(this.components);
            this.panelSpeedFrame.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxStream
            // 
            this.textBoxStream.Location = new System.Drawing.Point(12, 700);
            this.textBoxStream.Multiline = true;
            this.textBoxStream.Name = "textBoxStream";
            this.textBoxStream.ReadOnly = true;
            this.textBoxStream.Size = new System.Drawing.Size(562, 25);
            this.textBoxStream.TabIndex = 0;
            this.textBoxStream.Text = "(0 0 0 0)";
            // 
            // comboBoxSerial
            // 
            this.comboBoxSerial.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSerial.FormattingEnabled = true;
            this.comboBoxSerial.Location = new System.Drawing.Point(580, 700);
            this.comboBoxSerial.Name = "comboBoxSerial";
            this.comboBoxSerial.Size = new System.Drawing.Size(121, 25);
            this.comboBoxSerial.TabIndex = 1;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(707, 700);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 25);
            this.buttonConnect.TabIndex = 2;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.ButtonConnect_Click);
            // 
            // panelSpeedFrame
            // 
            this.panelSpeedFrame.BackColor = System.Drawing.Color.Black;
            this.panelSpeedFrame.BackgroundImage = global::MecanumController.Properties.Resources.Background;
            this.panelSpeedFrame.Controls.Add(this.buttonRotateRight);
            this.panelSpeedFrame.Controls.Add(this.buttonRotateLeft);
            this.panelSpeedFrame.Controls.Add(this.buttonMove);
            this.panelSpeedFrame.Location = new System.Drawing.Point(12, 12);
            this.panelSpeedFrame.Name = "panelSpeedFrame";
            this.panelSpeedFrame.Size = new System.Drawing.Size(770, 682);
            this.panelSpeedFrame.TabIndex = 3;
            // 
            // buttonRotateRight
            // 
            this.buttonRotateRight.Location = new System.Drawing.Point(728, 656);
            this.buttonRotateRight.Name = "buttonRotateRight";
            this.buttonRotateRight.Size = new System.Drawing.Size(39, 23);
            this.buttonRotateRight.TabIndex = 2;
            this.buttonRotateRight.Text = ">>";
            this.buttonRotateRight.UseVisualStyleBackColor = true;
            this.buttonRotateRight.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ButtonRotateRight_MouseDown);
            this.buttonRotateRight.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ButtonRotateRight_MouseUp);
            // 
            // buttonRotateLeft
            // 
            this.buttonRotateLeft.Location = new System.Drawing.Point(688, 656);
            this.buttonRotateLeft.Name = "buttonRotateLeft";
            this.buttonRotateLeft.Size = new System.Drawing.Size(39, 23);
            this.buttonRotateLeft.TabIndex = 1;
            this.buttonRotateLeft.Text = "<<";
            this.buttonRotateLeft.UseVisualStyleBackColor = true;
            this.buttonRotateLeft.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ButtonRotateLeft_MouseDown);
            this.buttonRotateLeft.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ButtonRotateLeft_MouseUp);
            // 
            // buttonMove
            // 
            this.buttonMove.Location = new System.Drawing.Point(357, 312);
            this.buttonMove.Name = "buttonMove";
            this.buttonMove.Size = new System.Drawing.Size(50, 50);
            this.buttonMove.TabIndex = 0;
            this.buttonMove.Text = "Move";
            this.buttonMove.UseVisualStyleBackColor = true;
            this.buttonMove.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ButtonMove_MouseDown);
            this.buttonMove.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ButtonMove_MouseMove);
            this.buttonMove.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ButtonMove_MouseUp);
            // 
            // timerEvents
            // 
            this.timerEvents.Enabled = true;
            this.timerEvents.Interval = 60;
            this.timerEvents.Tick += new System.EventHandler(this.TimerEvents_Tick);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(794, 737);
            this.Controls.Add(this.panelSpeedFrame);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.comboBoxSerial);
            this.Controls.Add(this.textBoxStream);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Mecanum Controller";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.panelSpeedFrame.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxStream;
        private System.Windows.Forms.ComboBox comboBoxSerial;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Panel panelSpeedFrame;
        private System.Windows.Forms.Button buttonMove;
        private System.Windows.Forms.Button buttonRotateRight;
        private System.Windows.Forms.Button buttonRotateLeft;
        private System.Windows.Forms.Timer timerEvents;
    }
}

