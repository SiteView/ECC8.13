/********************************************************************
	created:	2008/02/20
	created:	20:2:2008   9:48
	filename: 	H:\SiteView\NNM4.0\GDIPanel\SiteViewPanel\VisioPanel.cs
	file path:	H:\SiteView\NNM4.0\GDIPanel\SiteViewPanel
	file base:	VisioPanel
	file ext:	cs
	author:		wangsheng.che
	
	purpose:	调用visio面板图
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
    /// 面板元素状态
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
    /// 面板元素状态表示类型
    /// </summary>
    public enum Style
    {
        Solid,
        Linear,
        Picture
    }

    //缩放类型
    public enum ScaleType
    {
        Whole,
        Width,
        Height
    }

    /// <summary>
    /// 写日志
    /// </summary>
    public class Log
    {

        /// <summary>
        /// 构造对象
        /// </summary>
        public Log()
        {

        }

        /// <summary>
        /// 构造对象
        /// </summary>
        /// <param name="Path">日志路径</param>
        public Log(string Path)
        {

            _path = Path;

        }

        private static string _path = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "VisioPanel_Log.txt");
        /// <summary>
        /// 保存日志路径
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
        /// 日志信息
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
        /// 写日志
        /// </summary>
        /// <param name="sLog">日志信息</param>
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
    /// 面板元素基类
    /// </summary>
    public class PanelTemplate : Object
    {

        private int _Index;
        /// <summary>
        /// 对象索引号
        /// </summary>
        [Description("获取或设置对象索引号")]
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
        /// 对象名称
        /// </summary>
        [Description("获取或设置对象名称")]
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
        /// 对象Box实例
        /// </summary>
        [Description("获取或设置对象Box实例")]
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
        /// 对象ToolTip信息
        /// </summary>
        [Description("获取或设置对象ToolTip信息")]
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
        /// 与对象关联的用户定义数据
        /// </summary>
        [Description("获取或设置与对象关联的用户定义数据")]
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
    /// 模块
    /// </summary>
    public class Module : PanelTemplate
    {

        //显示模块的FlowChart
        public FlowChart Document;
        //模块Rectangle实例
        public RectangleF Rect;
        //模块端口清单
        public ArrayList Ports;
        //模块指示灯清单
        public ArrayList Lamps;
        //模块Box清单
        public ArrayList Boxes;

        /// <summary>
        /// 构造对象
        /// </summary>
        public Module()
        {

        }

        private string _type = string.Empty;
        /// <summary>
        /// 模块类型(OID号)
        /// </summary>
        [Description("获取或设置模块类型(OID号)")]
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
        /// 模块所在位置
        /// </summary>
        [Description("获取或设置模块所在位置")]
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
        /// 模块原始位置
        /// </summary>
        [Description("获取或设置模块原始位置")]
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
        /// 模块的父面板
        /// </summary>
        [Description("获取或设置模块的父面板")]
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
        /// 模块信息
        /// </summary>
        [Description("获取或设置模块信息")]
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
        /// 关闭当前模块
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
        /// 显示模块
        /// </summary>
        /// <param name="type">模块型号</param>
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
                Log.WriteLog("显示模块失败!错误： " + ex.ToString());
                //MessageBox.Show("显示模块失败!");
            }

        }

    }

    /// <summary>
    /// 端口
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
        /// 构造对象
        /// </summary>
        public Port()
        {

            InitializePort();

        }

        private Style _style = Style.Linear;
        /// <summary>
        /// 端口状态显示样式
        /// </summary>
        [Description("获取或设置端口状态显示样式")]
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
        /// 端口状态
        /// </summary>
        [Description("获取或设置端口状态")]
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
        /// 端口所属的模块编号
        /// </summary>
        [Description("获取或设置端口所属的模块编号")]
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
        /// 流量展示窗口
        /// </summary>
        [Description("获取流量展示窗口")]
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
                _fluxWindow.Text = "端口流量 -- 端口" + this.Index.ToString();
            }*/

        }

        private float _influx = 0.0f;
        /// <summary>
        /// 入流量
        /// </summary>
        [Description("获取或设置端口入流量")]
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
        /// 真实入流量
        /// </summary>
        [Description("获取或设置端口真实入流量")]
        public string FluxIn
        {

            get
            {
                return _fluxin;
            }
            set
            {
                _fluxin = value;
                label_inFlux.Text = "入流量: " + _fluxin;
            }

        }

        private float _outflux = 0.0f;
        /// <summary>
        /// 出流量
        /// </summary>
        [Description("获取或设置端口出流量")]
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
                //label_outFlux.Text = "出流量: ";
                RenderOutFluxShape();
            }

        }

        private string _fluxout = string.Empty;
        /// <summary>
        /// 真实出流量
        /// </summary>
        [Description("获取或设置端口真实出流量")]
        public string FluxOut
        {

            get
            {
                return _fluxout;
            }
            set
            {
                _fluxout = value;
                label_outFlux.Text = "出流量: " + _fluxout;
            }

        }

        /// <summary>
        /// 初始化端口
        /// </summary>
        private void InitializePort()
        {

            //流量窗口
            _fluxWindow = new Form();
            _fluxWindow.FormBorderStyle = FormBorderStyle.FixedToolWindow;
            _fluxWindow.Size = new Size(250, 110);
            _fluxWindow.Opacity = 0.75d;
            _fluxWindow.ShowIcon = false;
            _fluxWindow.ShowInTaskbar = false;
            _fluxWindow.Text = "端口流量 -- 端口" + this.Index.ToString();
            _fluxWindow.FormClosing += new FormClosingEventHandler(_fluxWindow_FormClosing);
            _fluxWindow.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //入流量面板
            panel_inFlux = new System.Windows.Forms.Panel();
            panel_inFlux.BorderStyle = BorderStyle.FixedSingle;
            panel_inFlux.Size = new Size(102, 30);
            panel_inFlux.Location = new Point(10, 10);
            panel_inFlux.BackColor = Color.FromArgb(180, Color.Green);
            panel_inFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //出流量面板
            panel_outFlux = new System.Windows.Forms.Panel();
            panel_outFlux.BorderStyle = BorderStyle.FixedSingle;
            panel_outFlux.Size = new Size(102, 30);
            panel_outFlux.Location = new Point(10, 45);
            panel_outFlux.BackColor = Color.FromArgb(180, Color.Green);
            panel_outFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //入流量标签
            label_inFlux = new Label();
            label_inFlux.AutoSize = false;
            label_inFlux.Size = new Size(130, 12);
            label_inFlux.Location = new Point(120, 20);
            label_inFlux.ForeColor = Color.Red;
            label_inFlux.Text = "入流量: ";
            label_inFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //出流量标签
            label_outFlux = new Label();
            label_outFlux.AutoSize = false;
            label_outFlux.Size = new Size(130, 12);
            label_outFlux.Location = new Point(120, 55);
            label_outFlux.ForeColor = Color.Red;
            label_outFlux.Text = "出流量: ";
            label_outFlux.MouseClick += new MouseEventHandler(_fluxWindow_MouseClick);

            //添加到窗口
            _fluxWindow.SuspendLayout();
            _fluxWindow.Controls.Add(panel_inFlux);
            _fluxWindow.Controls.Add(panel_outFlux);
            _fluxWindow.Controls.Add(label_inFlux);
            _fluxWindow.Controls.Add(label_outFlux);
            _fluxWindow.ResumeLayout(false);

            //初始化入流量和出流量列表
            for (int i = 0; i < 21; i++)
            {
                list_inFlux[i] = 0.0f;
                list_outFlux[i] = 0.0f;
            }

        }

        /// <summary>
        /// 单击右键关闭流量窗口
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
        /// 隐藏流量窗口
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _fluxWindow_FormClosing(object sender, FormClosingEventArgs e)
        {

            e.Cancel = true;
            _fluxWindow.Hide();

        }

        /// <summary>
        /// 绘制入流量图
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
        /// 绘制出流量图
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
        /// 显示端口状态
        /// </summary>
        /// <param name="status">状态</param>
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
    /// 指示灯
    /// </summary>
    public class Lamp : PanelTemplate
    {

        //定时器
        private Timer _timer;

        /// <summary>
        /// 构造对象
        /// </summary>
        public Lamp()
        {

            InitializeTimer();

        }

        private bool flag = true;
        /// <summary>
        /// 动态展示状态
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
        /// 初始化Timer
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
        /// 获取或设置灯光频率
        /// </summary>
        [Description("获取或设置灯光频率")]
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
        /// 获取或设置灯光闪烁最大间隔
        /// </summary>
        [Description("获取或设置灯光闪烁最大间隔")]
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
        /// 指示灯状态
        /// </summary>
        [Description("获取或设置指示灯状态")]
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
        /// 指示灯所属的模块编号
        /// </summary>
        [Description("获取或设置指示灯所属的模块编号")]
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
    /// Visio面板图(包括单模和多模)
    /// </summary>
    public class VisioPanel
    {
        
        //显示面板图的FlowChart控件
        private FlowChart _document;
        //比例
        private float _scale = 1.0f;
        private float _old_scale = 1.0f;
        //设备清单
        private ArrayList _devices = new ArrayList();
        //模块清单
        private ArrayList _modules = new ArrayList();
        //端口清单
        private ArrayList _ports = new ArrayList();
        //指示灯清单
        private ArrayList _lamps = new ArrayList();
        //面板box清单
        private ArrayList _boxes = new ArrayList();
        //vdx文件
        private string _vdxFile = string.Empty;
        //设备oid
        private string _eqoid = string.Empty;
        //面板图位置
        private PointF _panel_location = new PointF(5.0f, 5.0f);
        //面板图大小
        private SizeF _panel_size = new SizeF();
        //缩放类型
        private ScaleType _scaleModel = ScaleType.Whole;
        //激活的端口或指示灯
        private SiteView.Panel.PanelTemplate _selected = null;
        //设备信息
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
        /// 构造对象
        /// </summary>
        public VisioPanel()
        {

            //初始化Timer
            InitializeTimer();

        }

        /// <summary>
        /// 构造对象
        /// </summary>
        /// <param name="document">显示面板的FlowChart控件</param>
        public VisioPanel(FlowChart Document)
            : this()
        {

            _document = Document;

        }

        /// <summary>
        /// 构造对象
        /// </summary>
        /// <param name="EqOid">设备oid</param>
        /// <param name="document">显示面板的FlowChart控件</param>
        public VisioPanel(string EqOid, FlowChart Document)
            : this()
        {

            _document = Document;
            this.EqOid = EqOid;

        }

        /// <summary>
        /// 析构对象
        /// </summary>
        /*~VisioPanel()
        {

            Dispose();

        }*/

        /// <summary>
        /// 显示面板的FlowChart控件
        /// </summary>
        [Description("获取或设置显示面板的FlowChart控件")]
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
        /// 面板图比例
        /// </summary>
        [DefaultValue(1.0f)]
        [Description("获取或设置面板图的缩放比例")]
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
                    //实现缩放
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
        /// 设备清单
        /// </summary>
        [Description("获取或设置设备清单")]
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
        /// 模块清单
        /// </summary>
        [Description("获取或设置模块清单")]
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
        /// 端口清单
        /// </summary>
        [Description("获取或设置端口清单")]
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
        /// 指示灯清单
        /// </summary>
        [Description("获取或设置指示灯清单")]
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
        /// 面板box清单   
        /// </summary>
        [Description("获取或设置面板box清单")]
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
        /// vdx文件
        /// </summary>
        [Description("获取或设置vdx文件")]
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
                    //显示面板图
                    ShowVisioPanel(System.IO.Path.GetFileName(tempVdxFile));
                }
                if (File.Exists(tempVdxFile))
                {
                    File.Delete(tempVdxFile);
                }
            }

        }

        /// <summary>
        /// 设备oid号
        /// </summary>
        [Description("获取或设置设备oid号")]
        public string EqOid
        {

            get
            {
                return _eqoid;
            }
            set
            {
                _eqoid = value;
                //实现面板图展示入口
                LoadVdxFile(_eqoid);
            }

        }

        /// <summary>
        /// 获取或设置面板图显示位置
        /// </summary>
        [Description("获取或设置面板图显示位置")]
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
        /// 获取面板图大小
        /// </summary>
        [Description("获取或设置面板图大小")]
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
        /// 缩放样式
        /// </summary>
        [Description("获取或设置面板图缩放样式")]
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
        /// 激活的端口或指示灯
        /// </summary>
        [Description("获取或设置激活的对象(端口,指示灯...)")]
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
        /// 面板的设备信息
        /// </summary>
        [Description("获取或设置面板的设备信息")]
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
        /// 获取当前对象是否为空
        /// </summary>
        [Description("获取当前对象是否为空")]
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
        /// 动态展示状态
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer_Tick(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// 初始化Timer
        /// </summary>
        private void InitializeTimer()
        {

            _timer = new Timer();
            _timer.Interval = 500;
            _timer.Enabled = false;
            _timer.Tick += new EventHandler(timer_Tick);

        }

        /// <summary>
        /// 显示Visio面板图
        /// </summary>
        /// <param name="VdxFile">面板图Vdx文件</param>
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
                Log.WriteLog("开始装载面板图...");
                this._document.SuspendLayout();                
                VisioImporter.ImportPage(VdxFile, _document, 0, Convert.ToInt32(_panel_location.X), Convert.ToInt32(_panel_location.Y));
                this._document.ResumeLayout(false);
                this._document.PerformLayout();
                _panel_size = new SizeF(Convert.ToSingle(VisioImporter.pEquipmentInfo.Width), Convert.ToSingle(VisioImporter.pEquipmentInfo.Height));
                _eqinfo = VisioImporter.pEquipmentInfo;
                //模块清单 this.GetType().Name.ToString() +
                Log.WriteLog("开始初始化模块清单...");
                foreach (SiteView.VisioImport.VisioImporter.EquipmentContainer i in VisioImporter.pEquipmentContainer) //遍历
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
                Log.WriteLog("初始化模块清单成功!");
                Log.WriteLog("开始初始化端口清单...");
                //端口清单
                foreach (SiteView.VisioImport.VisioImporter.EquipmentPort i in VisioImporter.pEquipmentPort) //遍历
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
                Log.WriteLog("初始化端口清单成功!");
                Log.WriteLog("开始初始化指示灯清单...");
                //指示灯清单
                foreach (SiteView.VisioImport.VisioImporter.EquipmentLamp i in VisioImporter.pEquipmentLamp) //遍历
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
                Log.WriteLog("初始化指示灯清单成功!");
                Log.WriteLog("开始初始化box清单...");
                //面板图box清单
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
                Log.WriteLog("初始化box清单成功!");
                //设备清单
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
                Log.WriteLog("装载面板图成功!");
                this._isnull = false;

            }
            catch (Exception ex)
            {
                this._isnull = true;
                Log.WriteLog("装载面板图失败!原因：" + ex.ToString());
            }

        }

        /// <summary>
        /// 装载Vdx文件并显示面板图
        /// </summary>
        /// <param name="EqOid"></param>
        private void LoadVdxFile(string EqOid)
        {

            string vdxFilePath = string.Empty;
            //从文件目录读取面板图文件
            if (File.Exists(System.IO.Path.Combine(System.IO.Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), ("panel\\" + EqOid + ".vdx"))))
            {
                Log.WriteLog("开始从文件装载面板图...");
                this.VdxFile = System.IO.Path.Combine(System.IO.Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), ("panel\\" + EqOid + ".vdx"));
                return;
            }
            //从图库读取面板图文件
            VdxManager vdxManager = new VdxManager();
            EquipVdx eqVdx = new EquipVdx();
            eqVdx.Sysoid = EqOid;
            if (vdxManager.ReadVdxInfo(ref eqVdx))
            {
                Log.WriteLog("开始从图库装载面板图...");
                if (!File.Exists(eqVdx.tempFileName))
                {
                    Log.WriteLog("装载面板图失败!文件不存在:" + eqVdx.tempFileName);
                    return;
                }               
                
                this.VdxFile = eqVdx.tempFileName;
                //File.Delete(eqVdx.tempFileName);
            }
            else
            {
                this.Document.Text = "面板图文件不存在！";
                this.Document.Font = new Font("", 12.0f, FontStyle.Bold);
                return;
            }

        }

        /// <summary>
        /// 整体缩放面板
        /// </summary>
        /// <param name="scale">缩放比例</param>
        public void ScalePanel(float scale)
        {

            //获取模块原始位置
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
        /// 按宽高比例缩放面板图
        /// </summary>
        /// <param name="scaleW">宽缩放比例</param>
        /// <param name="scaleH">高缩放比例</param>
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
        /// 面板图高度缩放
        /// </summary>
        /// <param name="scale">缩放比例</param>
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
        /// 面板图宽度缩放
        /// </summary>
        /// <param name="scale">缩放比例</param>
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
        /// 释放资源
        /// </summary>
        public void Dispose()
        {

            //删除实例
            foreach (Box box in Boxes)
            {
                this.Document.DeleteObject(box);
            }
            //清空清单
            this.Modules.Clear();
            this.Ports.Clear();
            this.Lamps.Clear();
            this.Boxes.Clear();

        }

    }

}
