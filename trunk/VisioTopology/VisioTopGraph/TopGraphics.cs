using System;
using System.Collections.Generic;
using System.Text;
using MindFusion.FlowChartX;
using System.Windows.Forms;
using SiteView.VisioImport;
using System.Drawing;

namespace SiteView.Panel
{

    /// <summary>
    /// 设备类型
    /// </summary>
    public enum DeviceType
    {

        /// <summary>
        /// 电脑
        /// </summary>
        PC,
        /// <summary>
        /// 服务器
        /// </summary>
        Server,
        /// <summary>
        /// 路由器
        /// </summary>
        Router,
        /// <summary>
        /// 防火墙
        /// </summary>
        FireWall,
        /// <summary>
        /// 两层交换机
        /// </summary>
        Switch2,
        /// <summary>
        /// 三层交换机
        /// </summary>
        Switch3

    };

    /// <summary>
    /// 设备状态
    /// </summary>
    public enum DeviceStatus
    {

        /// <summary>
        /// 运行
        /// </summary>
        Run,
        /// <summary>
        /// 停止
        /// </summary>
        Stop,
        /// <summary>
        /// 告警
        /// </summary>
        Alarm,
        /// <summary>
        /// 测试
        /// </summary>
        Test,
        /// <summary>
        /// 其它
        /// </summary>
        Other,
        /// <summary>
        /// 未知
        /// </summary>
        Unknown

    };

    /// <summary>
    /// 设备(电脑,服务器,路由器,防火墙,两层交换机,三层交换机)
    /// </summary>
    public class Device : PanelTemplate
    {

        /// <summary>
        /// 构造对象
        /// </summary>
        public Device()
        {

        }

        /*private int _index;
        /// <summary>
        /// 设备索引号
        /// </summary>
        public int Index
        {

            get { return _index; }
            set { _index = value; }

        }

        private string _name;
        /// <summary>
        /// 设备名称
        /// </summary>
        public string Name
        {

            get { return _name; }
            set { _name = value; }

        }*/

        private Box _instance;
        /// <summary>
        /// 设备实例对象，以便对设备进行各种状态控制。
        /// </summary>
        public Box Instance
        {

            get { return _instance; }
            set { _instance = value; }

        }

        private DeviceType _type;
        /// <summary>
        /// 设备类型
        /// </summary>
        public DeviceType Type
        {

            get { return _type; }
            set { _type = value; }

        }

        private List<string> _iplist;
        /// <summary>
        /// 设备ip列表
        /// </summary>
        public List<string> IPlist
        {

            get { return _iplist; }
            set { _iplist = value; }

        }

        private string _model;
        /// <summary>
        /// 设备型号
        /// </summary>
        public string Model
        {

            get { return _model; }
            set { _model = value; }

        }

        private DeviceStatus _status = DeviceStatus.Unknown;
        /// <summary>
        /// 设备状态
        /// </summary>
        public DeviceStatus Status
        {

            get { return _status; }
            set
            {
                if (_status != value)
                {
                    _status = value;
                    switch (_status)
                    {
                        //运行
                        case DeviceStatus.Run:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.LightGreen), 1.0f);
                            break;
                        //告警
                        case DeviceStatus.Alarm:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.Red), 1.0f);
                            break;
                        //测试
                        case DeviceStatus.Test:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.Yellow), 1.0f);
                            break;
                        //停止
                        case DeviceStatus.Stop:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.DarkGray), 1.0f);
                            break;
                        //其它
                        case DeviceStatus.Other:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.Blue), 1.0f);
                            break;
                        //未知
                        case DeviceStatus.Unknown:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.DarkGray), 1.0f);
                            break;
                    }
                }
            }

        }

        /*private string _tooltip = string.Empty;
        /// <summary>
        /// 设备tooltip信息
        /// </summary>
        public string Tooltip
        {

            get { return _tooltip; }
            set
            {
                if (!_tooltip.Equals(value))
                {
                    _tooltip = value;
                    this.Instance.ToolTip = _tooltip;
                }
            }

        }*/

    };

    /// <summary>
    /// 拓扑图
    /// </summary>
    public class TopGraphics
    {

        //显示拓扑图的FlowChart控件
        private FlowChart _document;
        //显示整个拓扑图的父控件
        private Control _parent;
        //拓扑图Vdx文件
        private string _vdx;
        //拓扑图设备列表
        private List<Device> _devices = new List<Device>();
        //当前选择的设备
        private Device _selected;
        //右键快捷菜单
        private ContextMenuStrip _menuStrip = new ContextMenuStrip();

        /// <summary>
        /// 构造对象
        /// </summary>
        public TopGraphics()
        {

            InitializeDocument();

        }

        /// <summary>
        /// 构造对象
        /// </summary>
        /// <param name="Vdx">拓扑图Vdx文件</param>
        /// <param name="Document">显示拓扑图的FlowChart控件</param>
        public TopGraphics(string Vdx, FlowChart Document)
        {

            this.Document = Document;
            this.Vdx = Vdx;

        }

        /// <summary>
        /// 构造对象
        /// </summary>
        /// <param name="Vdx">拓扑图Vdx文件</param>
        /// <param name="Parent">显示整个拓扑图的父控件</param>
        public TopGraphics(string Vdx, Control Parent)
            : this()
        {

            this.Parent = Parent;
            this.Vdx = Vdx;

        }

        /// <summary>
        /// 显示拓扑图的FlowChart控件
        /// </summary>
        public FlowChart Document
        {

            get { return _document; }
            set { _document = value; }

        }

        /// <summary>
        /// 显示整个拓扑图的父控件
        /// </summary>
        public Control Parent
        {

            get { return _parent; }
            set
            {
                _parent = value;
                _parent.Controls.Add(this.Document);
            }

        }

        /// <summary>
        /// 拓扑图vdx文件
        /// </summary>
        public string Vdx
        {

            get { return _vdx; }
            set
            {
                _vdx = value;
                //显示拓扑图
                ShowTopGraphics();
            }

        }

        /// <summary>
        /// 拓扑图设备列表
        /// </summary>
        public List<Device> Devices
        {

            get { return _devices; }
            set { _devices = value; }

        }

        /// <summary>
        /// 当前选择的设备对象
        /// </summary>
        public Device Selected
        {

            get { return _selected; }
            set
            {
                Device old = _selected;
                _selected = value;
                if (_selected != null)
                {
                    if (old != _selected)
                    {
                        //绘制选择状态
                        DrawSelectedStatus(_selected.Instance.BoundingRect);
                    }
                }
            }

        }

        /// <summary>
        /// 右键快捷菜单
        /// </summary>
        public ContextMenuStrip MenuStrip
        {

            get { return _menuStrip; }
            set { _menuStrip = value; }

        }

        /// <summary>
        /// 初始化Document
        /// </summary>
        private void InitializeDocument()
        {

            this._document = new FlowChart();
            //this._document.ShowGrid = true;
            this._document.Behavior = BehaviorType.DoNothing;
            this._document.AllowRefLinks = false;
            this._document.AllowInplaceEdit = false;
            this._document.AutoScroll = false;
            this._document.AutoSizeDoc = MindFusion.FlowChartX.AutoSize.AllDirections;
            this._document.BackBrush = new MindFusion.FlowChartX.SolidBrush(Color.White);
            //this._document.BoxBrush = new MindFusion.FlowChartX.SolidBrush("#FFFFFFFF");
            this._document.DefaultControlType = typeof(System.Windows.Forms.Button);
            //this._document.DocExtents = ((System.Drawing.RectangleF)(resources.GetObject("m_flowChart.DocExtents")));
            this._document.Dock = System.Windows.Forms.DockStyle.Fill;
            this._document.InplaceEditFont = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this._document.BringToFront();
            this._document.MouseClick += new MouseEventHandler(_document_MouseClick);
            this._document.MouseMove += new MouseEventHandler(_document_MouseMove);

        }

        private string _caption = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        public string Caption
        {
            get { return _caption; }
            set { _caption = value; }
        }

        /// <summary>
        /// Document鼠标移动事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _document_MouseMove(object sender, MouseEventArgs e)
        {

            _caption = "坐标： ";
            _caption += e.X.ToString().PadRight(5, ' ');
            _caption += e.Y.ToString().PadRight(5, ' ');

        }

        /// <summary>
        /// Document鼠标单击事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _document_MouseClick(object sender, MouseEventArgs e)
        {

            /*//显示右键菜单
            if (e.Button == MouseButtons.Right)
            {
                _menuStrip.Show(_document, e.Location);
            }*/
            if (Devices != null)
            {
                foreach (Device device in Devices)
                {
                    if (device.Instance.Selected)
                    //if (device.Instance.BoundingRect.Contains(new PointF(Convert.ToSingle(e.X), Convert.ToSingle(e.Y))))
                    {
                        //设置当前选择设备
                        this.Selected = device;
                        //显示右键菜单
                        if (e.Button == MouseButtons.Right)
                        {
                            _menuStrip.Show(_document, e.Location);
                        }
                        return;
                    }
                }
                _selected = null;
                _document.Refresh();
            }

        }

        /// <summary>
        /// 绘制选择状态
        /// </summary>
        /// <param name="rec">需要绘制的矩形区域</param>
        private void DrawSelectedStatus(RectangleF rec)
        {

            float scale = _document.ZoomFactor / 100f;
            RectangleF recf = new RectangleF((rec.X - _document.ScrollX) * scale, (rec.Y - _document.ScrollY) * scale, rec.Width * scale, rec.Height * scale);
            using (Graphics g = _document.CreateGraphics())
            using (System.Drawing.SolidBrush brush = new System.Drawing.SolidBrush(Color.FromArgb(125, Color.BlueViolet)))
            using (System.Drawing.Pen pen = new System.Drawing.Pen(Color.Silver))
            {
                _document.Refresh();
                pen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;
                g.DrawRectangle(pen, recf.X, recf.Y, recf.Width, recf.Height);
                g.FillRectangle(brush, recf);
            }

        }

        /// <summary>
        /// 显示拓扑图
        /// </summary>
        private void ShowTopGraphics()
        {

            string vdxFileName = System.IO.Path.GetFileName(Vdx);
            this.Devices.Clear();
            VisioImporter VisioImporter = new VisioImporter();
            VisioImporter.ImportPage(vdxFileName, _document, 0, 5, 5);

        }

    }
}
