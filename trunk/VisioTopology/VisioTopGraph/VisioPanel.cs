/********************************************************************
	created:	2008/02/20
	created:	20:2:2008   9:48
	filename: 	H:\SiteView\NNM4.0\GDIPanel\SiteViewPanel\VisioPanel.cs
	file path:	H:\SiteView\NNM4.0\GDIPanel\SiteViewPanel
	file base:	VisioPanel
	file ext:	cs
	author:		wangsheng.che
	
	purpose:	����visio���ͼ
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
using System.ComponentModel;
using System.Runtime.InteropServices;
using SiteView.VisioImport;
using MindFusion.FlowChartX;
using MindFusion.FlowChartX.Commands;
using MindFusion.FlowChartX.LayoutSystem;

namespace SiteView.Panel
{

    /// <summary>
    /// ���Ԫ��״̬
    /// </summary>
    public enum PortStatus
    {
        Down,
        Up,
        Testing,
        Alarm,
        Other,
        Unknown
    }

    /// <summary>
    /// ���Ԫ��״̬��ʾ����
    /// </summary>
    public enum Style
    {
        Solid,
        Linear,
        Picture
    }

    //��������
    public enum ScaleType
    {
        Whole,
        Width,
        Height
    }

    /// <summary>
    /// д��־
    /// </summary>
    public class Log
    {

        /// <summary>
        /// �������
        /// </summary>
        public Log()
        {

        }

        /// <summary>
        /// �������
        /// </summary>
        /// <param name="Path">��־·��</param>
        public Log(string Path)
        {

            _path = Path;

        }

        private static string _path = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "VisioPanel_Log.txt");
        /// <summary>
        /// ������־·��
        /// </summary>
        public string Path
        {

            get
            {
                return _path;
            }
            set
            {
                _path = value;
                if (!File.Exists(_path))
                {
                    File.Create(_path);
                }
            }

        }

        private string _logInfo = string.Empty;
        /// <summary>
        /// ��־��Ϣ
        /// </summary>
        public string LogInfo
        {

            get
            {
                return _logInfo;
            }
            set
            {
                _logInfo = value;
                WriteLog(_logInfo);
            }

        }

        /// <summary>
        /// д��־
        /// </summary>
        /// <param name="sLog">��־��Ϣ</param>
        public static void WriteLog(string sLog)
        {

            try
            {
                StringBuilder sbLog = new StringBuilder();
                sbLog.Append("[" + DateTime.Now.ToString() + "]" + "  " + sLog + "\r\n");

                if (!File.Exists(_path))
                {
                    File.Create(_path);
                }

                using (StreamReader sr = new StreamReader(_path, Encoding.UTF8))
                {
                    StringBuilder sb = new StringBuilder(sr.ReadToEnd().ToString());
                    sr.Close();
                    if (sb.Length > 1024 * 5)
                    {
                        sb.Remove(0, sb.Length);
                    }
                    sb.Append(sbLog.ToString());
                    using (StreamWriter sw = new StreamWriter(_path))
                    {
                        sw.Write(sb.ToString());
                        sw.Flush();
                        sw.Close();
                    }
                    sr.Close();
                }
            }
            catch (Exception ex)
            {

            }

        }

    }

    /// <summary>
    /// ���Ԫ�ػ���
    /// </summary>
    public class PanelTemplate : Object
    {

        private int _Index;
        /// <summary>
        /// ����������
        /// </summary>
        [Description("��ȡ�����ö���������")]
        public int Index
        {

            get
            {
                return _Index;
            }
            set
            {
                _Index = value;
            }

        }

        private string _Name;
        /// <summary>
        /// ��������
        /// </summary>
        [Description("��ȡ�����ö�������")]
        public string Name
        {

            get
            {
                return _Name;
            }
            set
            {
                _Name = value;
            }

        }

        private Box _Instance;
        /// <summary>
        /// ����Boxʵ��
        /// </summary>
        [Description("��ȡ�����ö���Boxʵ��")]
        public Box Instance
        {

            get
            {
                return _Instance;
            }
            set
            {
                _Instance = value;
            }

        }

        private string _tooltip = string.Empty;
        /// <summary>
        /// ����ToolTip��Ϣ
        /// </summary>
        [Description("��ȡ�����ö���ToolTip��Ϣ")]
        public string ToolTip
        {

            get
            {
                return _tooltip;
            }
            set
            {
                _tooltip = value;
                this.Instance.ToolTip = _tooltip;
            }

        }

        private object _tag = null;
        /// <summary>
        /// �����������û���������
        /// </summary>
        [Description("��ȡ�����������������û���������")]
        public object Tag
        {

            get
            {
                return _tag;
            }
            set
            {
                _tag = value;
            }

        }

    }

    /// <summary>
    /// ģ��
    /// </summary>
    public class Module : PanelTemplate
    {

        //��ʾģ���FlowChart
        public FlowChart Document;
        //ģ��Rectangleʵ��
        public RectangleF Rect;
        //ģ��˿��嵥
        public ArrayList Ports;
        //ģ��ָʾ���嵥
        public ArrayList Lamps;
        //ģ��Box�嵥
        public ArrayList Boxes;

        /// <summary>
        /// �������
        /// </summary>
        public Module()
        {

        }

        private string _type = string.Empty;
        /// <summary>
        /// ģ������(OID��)
        /// </summary>
        [Description("��ȡ������ģ������(OID��)")]
        public string Type
        {

            get
            {
                return _type;
            }
            set
            {
                this.Close();
                _type = value;
                ShowModule(_type);
            }

        }

        private PointF _location = new PointF(0, 0);
        /// <summary>
        /// ģ������λ��
        /// </summary>
        [Description("��ȡ������ģ������λ��")]
        public PointF Location
        {

            get
            {
                return _location;
            }
            set
            {
                _location = value;
            }

        }

        private PointF _old_location = new PointF(0, 0);
        /// <summary>
        /// ģ��ԭʼλ��
        /// </summary>
        [Description("��ȡ������ģ��ԭʼλ��")]
        public PointF OldLocation
        {

            get
            {
                return _old_location;
            }
            set
            {
                _old_location = value;
            }

        }

        private VisioPanel _parent = null;
        /// <summary>
        /// ģ��ĸ����
        /// </summary>
        [Description("��ȡ������ģ��ĸ����")]
        public VisioPanel Parent
        {

            get
            {
                return _parent;
            }
            set
            {
                _parent = value;
            }

        }

        private VisioImporter.EquipmentInfo _moduleinfo;
        /// <summary>
        /// ģ����Ϣ
        /// </summary>
        [Description("��ȡ������ģ����Ϣ")]
        public VisioImporter.EquipmentInfo ModuleInfo
        {

            get
            {
                return _moduleinfo;
            }
            set
            {
                _moduleinfo = value;
            }

        }

        /// <summary>
        /// �رյ�ǰģ��
        /// </summary>
        public void Close()
        {

            if (Boxes != null)
            {
                foreach (Box box in Boxes)
                {
                    Document.DeleteObject(box);
                    this.Parent.Boxes.Remove(box);
                }
                _type = string.Empty;
                Ports.Clear();
                Lamps.Clear();
                Boxes.Clear();
            }

        }

        /// <summary>
        /// ��ʾģ��
        /// </summary>
        /// <param name="type">ģ���ͺ�</param>
        private void ShowModule(string type)
        {

            try
            {
                VisioPanel visioPanel = new VisioPanel(this.Document);
                visioPanel.Location = this.Instance.BoundingRect.Location;
                visioPanel.EqOid = type;
                visioPanel.ScalePanel(this.Instance.BoundingRect.Width / visioPanel.Size.Width, this.Instance.BoundingRect.Height / visioPanel.Size.Height);

                this.ModuleInfo = visioPanel.EqInfo;
                this.Boxes = visioPanel.Boxes;
                this.Ports = visioPanel.Ports;
                this.Lamps = visioPanel.Lamps;
                /*foreach(Box box in this.Boxes)
                {
                    this.Parent.Boxes.Add(box);
                }*/
                foreach (Port port in this.Ports)
                {
                    port.Module = this.Index;
                    this.Parent.Ports.Add(port);
                }
                foreach (Lamp lamp in this.Lamps)
                {
                    lamp.Module = this.Index;
                    this.Parent.Lamps.Add(lamp);
                }
            }
            catch (Exception ex)
            {
                Log.WriteLog("��ʾģ��ʧ��!���� " + ex.ToString());
                //MessageBox.Show("��ʾģ��ʧ��!");
            }

        }

    }

    /// <summary>
    /// �˿�
    /// </summary>
    public class Port : PanelTemplate
    {

        private System.Windows.Forms.Panel panel_inFlux;
        private System.Windows.Forms.Panel panel_outFlux;

        private Label label_inFlux;
        private Label label_outFlux;

        private float[] list_inFlux = new float[21];
        private float[] list_outFlux = new float[21];
        /// <summary>
        /// �������
        /// </summary>
        public Port()
        {

            InitializePort();

        }

        private Style _style = Style.Linear;
        /// <summary>
        /// �˿�״̬��ʾ��ʽ
        /// </summary>
        [Description("��ȡ�����ö˿�״̬��ʾ��ʽ")]
        public Style Style
        {

            get
            {
                return _style;
            }
            set
            {
                if (_style != value)
                {
                    _style = value;
                    ShowStatusStyle();
                }
            }

        }

        private PortStatus _status = PortStatus.Unknown;
        /// <summary>
        /// �˿�״̬
        /// </summary>
        [Description("��ȡ�����ö˿�״̬")]
        public PortStatus Status
        {

            get
            {
                return _status;
            }
            set
            {
                if (_status != value)
                {
                    _status = value;
                    ShowStatusStyle();
                }
            }

        }

        private int _module = 0;
        /// <summary>
        /// �˿�������ģ����
        /// </summary>
        [Description("��ȡ�����ö˿�������ģ����")]
        public int Module
        {

            get
            {
                return _module;
            }
            set
            {
                _module = value;
            }

        }

        private Form _fluxWindow;
        /// <summary>
        /// ����չʾ����
        /// </summary>
        [Description("��ȡ����չʾ����")]
        public Form FluxWindow
        {

            get
            {
                return _fluxWindow;
            }
            /*set
            {
                _fluxWindow = value;
                _fluxWindow.FormBorderStyle = FormBorderStyle.FixedToolWindow;
                _fluxWindow.Size = new Size(180, 120);
                _fluxWindow.Opacity = 0.75d;
                _fluxWindow.ShowIcon = false;
                _fluxWindow.ShowInTaskbar = false;
                _fluxWindow.Text = "�˿����� -- �˿�" + this.Index.ToString();
            }*/

        }

        private float _influx = 0.0f;
        /// <summary>
        /// ������
        /// </summary>
        [Description("��ȡ�����ö˿�������")]
        public float Influx
        {

            get
            {
                return _influx;
            }
            set
            {
                if (value > 1.0f)
                {
                    value = 1.0f;
                }
                if (value < 0.1f)
                {
                    if (value == 0.0f)
                    {
                        value = 0.0f;
                    }
                    else
                    {
                        value = 0.1f;
                    }
                }
                _influx = value;

                RenderInFluxShape();
            }

        }

        private string _fluxin = string.Empty;
        /// <summary>
        /// ��ʵ������
        /// </summary>
        [Description("��ȡ�����ö˿���ʵ������")]
        public string FluxIn
        {

            get
            {
                return _fluxin;
            }
            set
            {
                _fluxin = value;
                label_inFlux.Text = "������: " + _fluxin;
            }

        }

        private float _outflux = 0.0f;
        /// <summary>
        /// ������
        /// </summary>
        [Description("��ȡ�����ö˿ڳ�����")]
        public float Outflux
        {

            get
            {
                return _outflux;
            }
            set
            {
                if (value > 1.0f)
                {
                    value = 1.0f;
                }
                if (value < 0.1f)
                {
                    if (value == 0.0f)
                    {
                        value = 0.0f;
                    }
                    else
                    {
                        value = 0.1f;
                    }
                }
                _outflux = value;
                //label_outFlux.Text = "������: ";
                RenderOutFluxShape();
            }

        }

        private string _fluxout = string.Empty;
        /// <summary>
        /// ��ʵ������
        /// </summary>
        [Description("��ȡ�����ö˿���ʵ������")]
        public string FluxOut
        {

            get
            {
                return _fluxout;
            }
            set
            {
                _fluxout = value;
                label_outFlux.Text = "������: " + _fluxout;
            }

        }

        /// <summary>
        /// ��ʼ���˿�
        /// </summary>
        private void InitializePort()
        {

            //��������
            _fluxWindow = new Form();
            _fluxWindow.FormBorderStyle = FormBorderStyle.FixedToolWindow;
            _fluxWindow.Size = new Size(250, 110);
            _fluxWindow.Opacity = 0.75d;
            _fluxWindow.ShowIcon = false;
            _fluxWindow.ShowInTaskbar = false;
            _fluxWindow.Text = "�˿����� -- �˿�" + this.Index.ToString();
            _fluxWindow.FormClosing += new FormClosingEventHandler(_fluxWindow_FormClosing);
            _fluxWindow.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //���������
            panel_inFlux = new System.Windows.Forms.Panel();
            panel_inFlux.BorderStyle = BorderStyle.FixedSingle;
            panel_inFlux.Size = new Size(102, 30);
            panel_inFlux.Location = new Point(10, 10);
            panel_inFlux.BackColor = Color.FromArgb(180, Color.Green);
            panel_inFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //���������
            panel_outFlux = new System.Windows.Forms.Panel();
            panel_outFlux.BorderStyle = BorderStyle.FixedSingle;
            panel_outFlux.Size = new Size(102, 30);
            panel_outFlux.Location = new Point(10, 45);
            panel_outFlux.BackColor = Color.FromArgb(180, Color.Green);
            panel_outFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //��������ǩ
            label_inFlux = new Label();
            label_inFlux.AutoSize = false;
            label_inFlux.Size = new Size(130, 12);
            label_inFlux.Location = new Point(120, 20);
            label_inFlux.ForeColor = Color.Red;
            label_inFlux.Text = "������: ";
            label_inFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //��������ǩ
            label_outFlux = new Label();
            label_outFlux.AutoSize = false;
            label_outFlux.Size = new Size(130, 12);
            label_outFlux.Location = new Point(120, 55);
            label_outFlux.ForeColor = Color.Red;
            label_outFlux.Text = "������: ";
            label_outFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //��ӵ�����
            _fluxWindow.SuspendLayout();
            _fluxWindow.Controls.Add(panel_inFlux);
            _fluxWindow.Controls.Add(panel_outFlux);
            _fluxWindow.Controls.Add(label_inFlux);
            _fluxWindow.Controls.Add(label_outFlux);
            _fluxWindow.ResumeLayout(false);

            //��ʼ���������ͳ������б�
            for (int i = 0; i < 21; i++)
            {
                list_inFlux[i] = 0.0f;
                list_outFlux[i] = 0.0f;
            }

        }

        /// <summary>
        /// �����Ҽ��ر���������
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void _fluxWindow_MouseClick(object sender, MouseEventArgs e)
        {

            if (e.Button == MouseButtons.Right)
            {
                _fluxWindow.Hide();
            }

        }

        /// <summary>
        /// ������������
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _fluxWindow_FormClosing(object sender, FormClosingEventArgs e)
        {

            e.Cancel = true;
            _fluxWindow.Hide();

        }

        /// <summary>
        /// ����������ͼ
        /// </summary>
        private void RenderInFluxShape()
        {

            for (int i = 20; i > 0; i--)
            {
                list_inFlux[i] = list_inFlux[i - 1];
            }
            list_inFlux[0] = _influx;

            //panel_inFlux.Refresh();
            Bitmap bitmap = new Bitmap(panel_inFlux.Width, panel_inFlux.Height);
            using (Graphics g = Graphics.FromImage(bitmap))
            using (System.Drawing.Pen pen = new System.Drawing.Pen(Color.Red, 1.5f))
            using (System.Drawing.Pen pen1 = new System.Drawing.Pen(Color.FromArgb(175, Color.Silver), 1.0f))
            {
                PointF[] point_inFlux = new PointF[21];
                for (int i = 0; i < 21; i++)
                {
                    point_inFlux[i] = new PointF(5.0f * i, 30.0f * (1.0f - list_inFlux[20 - i]));
                }
                for (int i = 1; i < 20; i++)
                {
                    g.DrawLine(pen1, new PointF(5.0f * i, 0), new PointF(5.0f * i, 30.0f));
                }
                //g.FillPolygon(new System.Drawing.SolidBrush(Color.FromArgb(175, Color.Red)), point_inFlux);
                //g.FillClosedCurve(new System.Drawing.SolidBrush(Color.FromArgb(175, Color.Red)), point_inFlux, System.Drawing.Drawing2D.FillMode.Alternate);
                g.DrawLines(pen, point_inFlux);
            }
            panel_inFlux.BackgroundImage = bitmap;

        }

        /// <summary>
        /// ���Ƴ�����ͼ
        /// </summary>
        private void RenderOutFluxShape()
        {

            for (int i = 20; i > 0; i--)
            {
                list_outFlux[i] = list_outFlux[i - 1];
            }
            list_outFlux[0] = _outflux;

            //panel_outFlux.Refresh();
            Bitmap bitmap = new Bitmap(panel_outFlux.Width, panel_outFlux.Height);
            using (Graphics g = Graphics.FromImage(bitmap))
            using (System.Drawing.Pen pen = new System.Drawing.Pen(Color.Red, 1.5f))
            using (System.Drawing.Pen pen1 = new System.Drawing.Pen(Color.FromArgb(175, Color.Silver), 1.0f))
            {
                PointF[] point_outFlux = new PointF[21];
                for (int i = 0; i < 21; i++)
                {
                    point_outFlux[i] = new PointF(5.0f * i, 30.0f * (1.0f - list_outFlux[20 - i]));
                }
                for (int i = 1; i < 20; i++)
                {
                    g.DrawLine(pen1, new PointF(5.0f * i, 0), new PointF(5.0f * i, 30.0f));
                }
                //g.FillPolygon(new System.Drawing.SolidBrush(Color.FromArgb(175, Color.Red)), point_outFlux);
                //g.FillClosedCurve(new System.Drawing.SolidBrush(Color.FromArgb(175, Color.Red)), point_outFlux,System.Drawing.Drawing2D.FillMode.Winding);
                g.DrawLines(pen, point_outFlux);
            }
            panel_outFlux.BackgroundImage = bitmap;

        }

        /// <summary>
        /// ��ʾ�˿�״̬
        /// </summary>
        /// <param name="status">״̬</param>
        private void ShowStatusStyle()
        {

            switch (_style)
            {
                case Style.Solid:
                    {
                        Color color1 = Color.LightGreen;
                        switch (_status)
                        {
                            case PortStatus.Up:
                                color1 = Color.LightGreen;
                                break;
                            case PortStatus.Down:
                                color1 = Color.Gray;
                                break;
                            case PortStatus.Testing:
                                color1 = Color.Yellow;
                                break;
                            case PortStatus.Alarm:
                                color1 = Color.Red;
                                break;
                            case PortStatus.Other:
                                color1 = Color.Blue;
                                break;
                            case PortStatus.Unknown:
                                color1 = Color.Gray;
                                break;
                            default:
                                color1 = Color.Gray;
                                break;
                        }
                        if (this.Instance != null)
                        {
                            this.Instance.Brush = new MindFusion.FlowChartX.SolidBrush(color1);
                        }
                        break;
                    }
                case Style.Linear:
                    {
                        Color color1 = Color.DarkGreen;
                        Color color2 = Color.LightGreen;
                        switch (_status)
                        {
                            case PortStatus.Up:
                                color1 = Color.DarkGreen;
                                color2 = Color.LightGreen;
                                break;
                            case PortStatus.Down:
                                color1 = Color.DarkGray;
                                color2 = Color.LightGray;
                                break;
                            case PortStatus.Testing:
                                color1 = Color.Yellow;
                                color2 = Color.LightYellow;
                                break;
                            case PortStatus.Alarm:
                                color1 = Color.DarkRed;
                                color2 = Color.Red;
                                break;
                            case PortStatus.Other:
                                color1 = Color.DarkBlue;
                                color2 = Color.LightBlue;
                                break;
                            case PortStatus.Unknown:
                                color1 = Color.DarkGray;
                                color2 = Color.LightGray;
                                break;
                            default:
                                color1 = Color.DarkGray;
                                color2 = Color.LightGray;
                                break;
                        }
                        if (Instance != null)
                        {
                            this.Instance.Brush = new MindFusion.FlowChartX.LinearGradientBrush(color1, color2, 90.0f);
                        } break;
                    }
                case Style.Picture:
                    {
                        switch (_status)
                        {
                            case PortStatus.Up:
                                break;
                            case PortStatus.Down:
                                break;
                            case PortStatus.Testing:
                                break;
                            case PortStatus.Alarm:
                                break;
                            case PortStatus.Other:
                                break;
                            case PortStatus.Unknown:
                                break;
                            default:
                                break;
                        }
                        break;
                    }
            }

        }

    }

    /// <summary>
    /// ָʾ��
    /// </summary>
    public class Lamp : PanelTemplate
    {

        //��ʱ��
        private Timer _timer;

        /// <summary>
        /// �������
        /// </summary>
        public Lamp()
        {

            InitializeTimer();

        }

        private bool flag = true;
        /// <summary>
        /// ��̬չʾ״̬
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer_Tick(object sender, EventArgs e)
        {

            if (flag)
            {
                this.Instance.Brush = new MindFusion.FlowChartX.SolidBrush(Color.LightGreen);
                flag = false;
            }
            else
            {
                this.Instance.Brush = new MindFusion.FlowChartX.SolidBrush(Color.DarkGreen);
                flag = true;
            }

        }

        /// <summary>
        /// ��ʼ��Timer
        /// </summary>
        private void InitializeTimer()
        {

            _timer = new Timer();
            _timer.Interval = _Interval;
            _timer.Enabled = false;
            _timer.Tick += new EventHandler(timer_Tick);

        }

        private float _freq = 0f;
        /// <summary>
        /// ��ȡ�����õƹ�Ƶ��
        /// </summary>
        [Description("��ȡ�����õƹ�Ƶ��")]
        public float Freq
        {

            get
            {
                return _freq;
            }
            set
            {
                _freq = value;
                if (_Interval * (1.0f - _freq) > 100f)
                {
                    _timer.Interval = Convert.ToInt32(_Interval * (1.0f - _freq));
                }
                else
                {
                    _timer.Interval = 100;
                }
            }

        }

        private int _Interval = 1000;
        /// <summary>
        /// ��ȡ�����õƹ���˸�����
        /// </summary>
        [Description("��ȡ�����õƹ���˸�����")]
        public int Interval
        {

            get
            {
                return _Interval;
            }
            set
            {
                _Interval = value;
            }

        }

        private PortStatus _status = PortStatus.Unknown;
        /// <summary>
        /// ָʾ��״̬
        /// </summary>
        [Description("��ȡ������ָʾ��״̬")]
        public PortStatus Status
        {

            get
            {
                return _status;
            }
            set
            {
                if (_status != value)
                {
                    _status = value;
                    Color color1 = Color.LightGreen;
                    switch (_status)
                    {
                        case PortStatus.Up:
                            _timer.Enabled = true;
                            //color1 = Color.LightGreen;
                            break;
                        case PortStatus.Down:
                            _timer.Enabled = false;
                            color1 = Color.Gray;
                            break;
                        case PortStatus.Testing:
                            _timer.Enabled = false;
                            color1 = Color.Yellow;
                            break;
                        case PortStatus.Alarm:
                            _timer.Enabled = false;
                            color1 = Color.Red;
                            break;
                        case PortStatus.Other:
                            _timer.Enabled = false;
                            color1 = Color.Blue;
                            break;
                        case PortStatus.Unknown:
                            _timer.Enabled = false;
                            color1 = Color.Gray;
                            break;
                        default:
                            _timer.Enabled = false;
                            color1 = Color.Gray;
                            break;
                    }
                    if (this.Instance != null)
                    {
                        this.Instance.Brush = new MindFusion.FlowChartX.SolidBrush(color1);
                    }
                }
            }

        }

        private int _module = 0;
        /// <summary>
        /// ָʾ��������ģ����
        /// </summary>
        [Description("��ȡ������ָʾ��������ģ����")]
        public int Module
        {

            get
            {
                return _module;
            }
            set
            {
                _module = value;
            }

        }

    }

    /// <summary>
    /// Visio���ͼ(������ģ�Ͷ�ģ)
    /// </summary>
    public class VisioPanel
    {
        
        //��ʾ���ͼ��FlowChart�ؼ�
        private FlowChart _document;
        //����
        private float _scale = 1.0f;
        private float _old_scale = 1.0f;
        //�豸�嵥
        private ArrayList _devices = new ArrayList();
        //ģ���嵥
        private ArrayList _modules = new ArrayList();
        //�˿��嵥
        private ArrayList _ports = new ArrayList();
        //ָʾ���嵥
        private ArrayList _lamps = new ArrayList();
        //���box�嵥
        private ArrayList _boxes = new ArrayList();
        //vdx�ļ�
        private string _vdxFile = string.Empty;
        //�豸oid
        private string _eqoid = string.Empty;
        //���ͼλ��
        private PointF _panel_location = new PointF(5.0f, 5.0f);
        //���ͼ��С
        private SizeF _panel_size = new SizeF();
        //��������
        private ScaleType _scaleModel = ScaleType.Whole;
        //����Ķ˿ڻ�ָʾ��
        private SiteView.Panel.PanelTemplate _selected = null;
        //�豸��Ϣ
        private VisioImporter.EquipmentInfo _eqinfo;

        //Timer
        private Timer _timer;

        //
        private MindFusion.FlowChartX.SolidBrush upBrush = new MindFusion.FlowChartX.SolidBrush(Color.LightGreen);
        private MindFusion.FlowChartX.SolidBrush downBrush = new MindFusion.FlowChartX.SolidBrush(Color.DarkGreen);
        private MindFusion.FlowChartX.SolidBrush alarmBrush = new MindFusion.FlowChartX.SolidBrush(Color.Red);
        private MindFusion.FlowChartX.SolidBrush testBrush = new MindFusion.FlowChartX.SolidBrush(Color.Yellow);
        private MindFusion.FlowChartX.SolidBrush otherBrush = new MindFusion.FlowChartX.SolidBrush(Color.Blue);

        /// <summary>
        /// �������
        /// </summary>
        public VisioPanel()
        {

            //��ʼ��Timer
            InitializeTimer();

        }

        /// <summary>
        /// �������
        /// </summary>
        /// <param name="document">��ʾ����FlowChart�ؼ�</param>
        public VisioPanel(FlowChart Document)
            : this()
        {

            _document = Document;

        }

        /// <summary>
        /// �������
        /// </summary>
        /// <param name="EqOid">�豸oid</param>
        /// <param name="document">��ʾ����FlowChart�ؼ�</param>
        public VisioPanel(string EqOid, FlowChart Document)
            : this()
        {

            _document = Document;
            this.EqOid = EqOid;

        }

        /// <summary>
        /// ��������
        /// </summary>
        /*~VisioPanel()
        {

            Dispose();

        }*/

        /// <summary>
        /// ��ʾ����FlowChart�ؼ�
        /// </summary>
        [Description("��ȡ��������ʾ����FlowChart�ؼ�")]
        public FlowChart Document
        {

            get
            {
                return _document;
            }
            set
            {
                _document = value;
            }

        }
        /// <summary>
        /// ���ͼ����
        /// </summary>
        [DefaultValue(1.0f)]
        [Description("��ȡ���������ͼ�����ű���")]
        public float Scale
        {

            get
            {
                return _scale;
            }
            set
            {
                _old_scale = Scale;
                if (_scale != value)
                {
                    _scale = value;
                    //ʵ������
                    switch (_scaleModel)
                    {
                        case ScaleType.Whole:
                            ScalePanel(_scale / _old_scale);
                            this.Size = new SizeF(this.Size.Width * _scale / _old_scale, this.Size.Height * _scale / _old_scale);
                            break;
                        case ScaleType.Width:
                            ScalePanelW(_scale / _old_scale);
                            break;
                        case ScaleType.Height:
                            ScalePanelH(_scale / _old_scale);
                            break;
                        default:
                            break;
                    }
                }
            }

        }

        /// <summary>
        /// �豸�嵥
        /// </summary>
        [Description("��ȡ�������豸�嵥")]
        public ArrayList Devices
        {

            get
            {
                return _devices;
            }
            set
            {
                _devices = value;
            }

        }

        /// <summary>
        /// ģ���嵥
        /// </summary>
        [Description("��ȡ������ģ���嵥")]
        public ArrayList Modules
        {

            get
            {
                return _modules;
            }
            set
            {
                _modules = value;
            }

        }

        /// <summary>
        /// �˿��嵥
        /// </summary>
        [Description("��ȡ�����ö˿��嵥")]
        public ArrayList Ports
        {

            get
            {
                return _ports;
            }
            set
            {
                _ports = value;
            }

        }

        /// <summary>
        /// ָʾ���嵥
        /// </summary>
        [Description("��ȡ������ָʾ���嵥")]
        public ArrayList Lamps
        {

            get
            {
                return _lamps;
            }
            set
            {
                _lamps = value;
            }

        }

        /// <summary>
        /// ���box�嵥   
        /// </summary>
        [Description("��ȡ���������box�嵥")]
        public ArrayList Boxes
        {

            get
            {
                return _boxes;
            }
            set
            {
                _boxes = value;
            }

        }

        /// <summary>
        /// vdx�ļ�
        /// </summary>
        [Description("��ȡ������vdx�ļ�")]
        public string VdxFile
        {

            get
            {
                return _vdxFile;
            }
            set
            {
                _vdxFile = value;
                string tempVdxFile = System.IO.Path.Combine(System.IO.Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "VisioPanel.vdx");
                if (_vdxFile != string.Empty || _vdxFile != "")
                {
                    File.Copy(_vdxFile, tempVdxFile, true);
                    //_vdxFile = System.IO.Path.GetFileName(tempVdxFile);
                    //��ʾ���ͼ
                    ShowVisioPanel(System.IO.Path.GetFileName(tempVdxFile));
                }
                if (File.Exists(tempVdxFile))
                {
                    File.Delete(tempVdxFile);
                }
            }

        }

        /// <summary>
        /// �豸oid��
        /// </summary>
        [Description("��ȡ�������豸oid��")]
        public string EqOid
        {

            get
            {
                return _eqoid;
            }
            set
            {
                _eqoid = value;
                //ʵ�����ͼչʾ���
                LoadVdxFile(_eqoid);
            }

        }

        /// <summary>
        /// ��ȡ���������ͼ��ʾλ��
        /// </summary>
        [Description("��ȡ���������ͼ��ʾλ��")]
        public PointF Location
        {

            get
            {
                return _panel_location;
            }
            set
            {
                _panel_location = value;
            }

        }

        /// <summary>
        /// ��ȡ���ͼ��С
        /// </summary>
        [Description("��ȡ���������ͼ��С")]
        public SizeF Size
        {

            get
            {
                return _panel_size;
            }
            set
            {
                _panel_size = value;
            }

        }

        /// <summary>
        /// ������ʽ
        /// </summary>
        [Description("��ȡ���������ͼ������ʽ")]
        public ScaleType ScaleModel
        {

            get
            {
                return _scaleModel;
            }
            set
            {
                _scaleModel = value;
            }

        }

        /// <summary>
        /// ����Ķ˿ڻ�ָʾ��
        /// </summary>
        [Description("��ȡ�����ü���Ķ���(�˿�,ָʾ��...)")]
        public SiteView.Panel.PanelTemplate Selected
        {

            get
            {
                return _selected;
            }
            set
            {
                _selected = value;
            }

        }

        /// <summary>
        /// �����豸��Ϣ
        /// </summary>
        [Description("��ȡ�����������豸��Ϣ")]
        public VisioImporter.EquipmentInfo EqInfo
        {

            get
            {
                return _eqinfo;
            }
            set
            {
                _eqinfo = value;
            }

        }

        private bool _isnull = true;
        /// <summary>
        /// ��ȡ��ǰ�����Ƿ�Ϊ��
        /// </summary>
        [Description("��ȡ��ǰ�����Ƿ�Ϊ��")]
        public bool IsNull
        {

            get
            {
                return _isnull;
            }

        }

        /// <summary>
        /// Timer
        /// </summary>
        private Timer Timer
        {

            get
            {
                return _timer;
            }

        }

        /// <summary>
        /// ��̬չʾ״̬
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer_Tick(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// ��ʼ��Timer
        /// </summary>
        private void InitializeTimer()
        {

            _timer = new Timer();
            _timer.Interval = 500;
            _timer.Enabled = false;
            _timer.Tick += new EventHandler(timer_Tick);

        }

        /// <summary>
        /// ��ʾVisio���ͼ
        /// </summary>
        /// <param name="VdxFile">���ͼVdx�ļ�</param>
        private void ShowVisioPanel(string VdxFile)
        {

            try
            {
                this.Ports.Clear();
                this.Modules.Clear();
                this.Lamps.Clear();

                VisioImporter VisioImporter = new VisioImporter();
                VisioImporter.pFlowChartBox.Clear();
                //Scale = 1.0f;
                Log.WriteLog("��ʼװ�����ͼ...");
                this._document.SuspendLayout();                
                VisioImporter.ImportPage(VdxFile, _document, 0, Convert.ToInt32(_panel_location.X), Convert.ToInt32(_panel_location.Y));
                this._document.ResumeLayout(false);
                this._document.PerformLayout();
                _panel_size = new SizeF(Convert.ToSingle(VisioImporter.pEquipmentInfo.Width), Convert.ToSingle(VisioImporter.pEquipmentInfo.Height));
                _eqinfo = VisioImporter.pEquipmentInfo;
                //ģ���嵥 this.GetType().Name.ToString() +
                Log.WriteLog("��ʼ��ʼ��ģ���嵥...");
                foreach (SiteView.VisioImport.VisioImporter.EquipmentContainer i in VisioImporter.pEquipmentContainer) //����
                {
                    foreach (Box box in _document.Boxes)
                    {
                        if (box.Tag == (object)i.Alias)
                        {
                            Module module = new Module();
                            module.Document = this.Document;
                            module.Index = i.ContainerIndex;
                            //module.Name = i.Alias;
                            module.Name = "module" + i.ContainerIndex.ToString();
                            module.Instance = box;
                            module.Rect = i.rect;
                            module.Location = i.rect.Location;
                            module.Parent = this;
                            _modules.Add(module);
                        }
                    }
                }
                Log.WriteLog("��ʼ��ģ���嵥�ɹ�!");
                Log.WriteLog("��ʼ��ʼ���˿��嵥...");
                //�˿��嵥
                foreach (SiteView.VisioImport.VisioImporter.EquipmentPort i in VisioImporter.pEquipmentPort) //����
                {
                    foreach (Box box in _document.Boxes)
                    {
                        if (box.Tag == (object)i.Alias)
                        {
                            Port port = new Port();
                            port.Index = i.PhysicsPortIndex;
                            //port.Name = i.Alias;
                            port.Name = "port" + i.PhysicsPortIndex;
                            port.Instance = box;
                            _ports.Add(port);
                        }
                    }
                }
                Log.WriteLog("��ʼ���˿��嵥�ɹ�!");
                Log.WriteLog("��ʼ��ʼ��ָʾ���嵥...");
                //ָʾ���嵥
                foreach (SiteView.VisioImport.VisioImporter.EquipmentLamp i in VisioImporter.pEquipmentLamp) //����
                {
                    foreach (Box box in _document.Boxes)
                    {
                        if (box.Tag == (object)i.Alias)
                        {
                            Lamp lamp = new Lamp();
                            lamp.Index = i.PhysicsPortLampIndex;
                            //lamp.Name = i.Alias;
                            lamp.Name = "lamp" + i.PhysicsPortLampIndex;
                            lamp.Instance = box;
                            _lamps.Add(lamp);
                        }
                    }
                }
                Log.WriteLog("��ʼ��ָʾ���嵥�ɹ�!");
                Log.WriteLog("��ʼ��ʼ��box�嵥...");
                //���ͼbox�嵥
                foreach (SiteView.VisioImport.VisioImporter.FlowChartBox i in VisioImporter.pFlowChartBox)
                {
                    foreach (Box box in _document.Boxes)
                    {
                        if (box.Tag == (object)i.Alias)
                        {
                            box.Locked = true;
                            _boxes.Add(box);
                        }
                    }
                }
                Log.WriteLog("��ʼ��box�嵥�ɹ�!");
                //�豸�嵥
                /*foreach(SiteView.VisioImport.VisioImporter.EquipmentPort i in VisioImporter.pEquipmentPort)
                {
                    foreach(Box box in _document.Boxes)
                    {
                        if(box.Tag == (object)i.Alias)
                        {
                            Device device = new Device();
                            device.Index = i.PhysicsPortIndex;
                            device.Name = "device" + i.PhysicsPortIndex;
                            device.Instance = box;
                            _devices.Add(device);
                        }
                    }
                }*/
                System.Threading.Thread.Sleep(2000);
                Log.WriteLog("װ�����ͼ�ɹ�!");
                this._isnull = false;

            }
            catch (Exception ex)
            {
                this._isnull = true;
                Log.WriteLog("װ�����ͼʧ��!ԭ��" + ex.ToString());
            }

        }

        /// <summary>
        /// װ��Vdx�ļ�����ʾ���ͼ
        /// </summary>
        /// <param name="EqOid"></param>
        private void LoadVdxFile(string EqOid)
        {

            string vdxFilePath = string.Empty;
            //���ļ�Ŀ¼��ȡ���ͼ�ļ�
            if (File.Exists(System.IO.Path.Combine(System.IO.Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), ("panel\\" + EqOid + ".vdx"))))
            {
                Log.WriteLog("��ʼ���ļ�װ�����ͼ...");
                this.VdxFile = System.IO.Path.Combine(System.IO.Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), ("panel\\" + EqOid + ".vdx"));
                return;
            }
            //��ͼ���ȡ���ͼ�ļ�
            VdxManager vdxManager = new VdxManager();
            EquipVdx eqVdx = new EquipVdx();
            eqVdx.Sysoid = EqOid;
            if (vdxManager.ReadVdxInfo(ref eqVdx))
            {
                Log.WriteLog("��ʼ��ͼ��װ�����ͼ...");
                if (!File.Exists(eqVdx.tempFileName))
                {
                    Log.WriteLog("װ�����ͼʧ��!�ļ�������:" + eqVdx.tempFileName);
                    return;
                }               
                
                this.VdxFile = eqVdx.tempFileName;
                //File.Delete(eqVdx.tempFileName);
            }
            else
            {
                this.Document.Text = "���ͼ�ļ������ڣ�";
                this.Document.Font = new Font("", 12.0f, FontStyle.Bold);
                return;
            }

        }

        /// <summary>
        /// �����������
        /// </summary>
        /// <param name="scale">���ű���</param>
        public void ScalePanel(float scale)
        {

            //��ȡģ��ԭʼλ��
            foreach (Module module in this.Modules)
            {
                module.OldLocation = module.Instance.BoundingRect.Location;
            }

            float scaleW = scale;
            float scaleH = scale;
            ScalePanel(scaleW, scaleH);

            /*foreach(Module module in this.Modules)
            {
                if (module.Boxes != null)
                {
                    float i = module.Instance.BoundingRect.X;
                    float x = module.Location.X;
                    foreach (Box box in module.Boxes)
                    {
                        RectangleF recBox = box.BoundingRect;
                        box.BoundingRect = new RectangleF((recBox.X * scaleW + module.Location.X * (1.0f - scaleW)), (recBox.Y * scaleH + module.Location.Y * (1.0f - scaleH)),
                                                          recBox.Width * scaleW, recBox.Height * scaleH);                        
                    }
                }
            }

            /*foreach (Module module in this.Modules)
            {
                if (module.Boxes != null)
                {
                    foreach (Box box in module.Boxes)
                    {
                        RectangleF recBox = box.BoundingRect;
                        box.BoundingRect = new RectangleF(recBox.X + (module.Instance.BoundingRect.Location.X - module.OldLocation.X),
                                                            recBox.Y + (module.Instance.BoundingRect.Location.Y - module.OldLocation.Y), 
                                                                recBox.Width, recBox.Height);
                    }
                }
            }*/

            foreach (Module module in this.Modules)
            {
                module.Rect.X = module.Instance.BoundingRect.X;
                module.Rect.Y = module.Instance.BoundingRect.Y;
                module.Rect.Width = module.Instance.BoundingRect.Width;
                module.Rect.Height = module.Instance.BoundingRect.Height;

                if (module.Boxes != null)
                {
                    string ModuleType = module.Type;
                    module.Type = ModuleType;
                }
            }

        }

        /// <summary>
        /// ����߱����������ͼ
        /// </summary>
        /// <param name="scaleW">�����ű���</param>
        /// <param name="scaleH">�����ű���</param>
        public void ScalePanel(float scaleW, float scaleH)
        {

            foreach (Box box in _boxes)
            {
                RectangleF recBox = box.BoundingRect;
                box.BoundingRect = new RectangleF(recBox.X * scaleW + _panel_location.X * (1.0f - scaleW), recBox.Y * scaleH + _panel_location.Y * (1.0f - scaleH),
                                                  recBox.Width * scaleW, recBox.Height * scaleH);
            }

        }

        /// <summary>
        /// ���ͼ�߶�����
        /// </summary>
        /// <param name="scale">���ű���</param>
        private void ScalePanelH(float scaleH)
        {

            foreach (Box box in _boxes)
            {
                RectangleF recBox = box.BoundingRect;
                box.BoundingRect = new RectangleF(recBox.X, recBox.Y * scaleH + _panel_location.Y * (1.0f - scaleH),
                                                    recBox.Width, recBox.Height * scaleH);
            }

        }

        /// <summary>
        /// ���ͼ�������
        /// </summary>
        /// <param name="scale">���ű���</param>
        private void ScalePanelW(float scaleW)
        {

            foreach (Box box in _boxes)
            {
                RectangleF recBox = box.BoundingRect;
                box.BoundingRect = new RectangleF(recBox.X * scaleW + _panel_location.X * (1.0f - scaleW), recBox.Y,
                                                    recBox.Width * scaleW, recBox.Height);
            }

        }

        /// <summary>
        /// �ͷ���Դ
        /// </summary>
        public void Dispose()
        {

            //ɾ��ʵ��
            foreach (Box box in Boxes)
            {
                this.Document.DeleteObject(box);
            }
            //����嵥
            this.Modules.Clear();
            this.Ports.Clear();
            this.Lamps.Clear();
            this.Boxes.Clear();

        }

    }

}
