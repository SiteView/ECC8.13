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
    /// �豸����
    /// </summary>
    public enum DeviceType
    {

        /// <summary>
        /// ����
        /// </summary>
        PC,
        /// <summary>
        /// ������
        /// </summary>
        Server,
        /// <summary>
        /// ·����
        /// </summary>
        Router,
        /// <summary>
        /// ����ǽ
        /// </summary>
        FireWall,
        /// <summary>
        /// ���㽻����
        /// </summary>
        Switch2,
        /// <summary>
        /// ���㽻����
        /// </summary>
        Switch3

    };

    /// <summary>
    /// �豸״̬
    /// </summary>
    public enum DeviceStatus
    {

        /// <summary>
        /// ����
        /// </summary>
        Run,
        /// <summary>
        /// ֹͣ
        /// </summary>
        Stop,
        /// <summary>
        /// �澯
        /// </summary>
        Alarm,
        /// <summary>
        /// ����
        /// </summary>
        Test,
        /// <summary>
        /// ����
        /// </summary>
        Other,
        /// <summary>
        /// δ֪
        /// </summary>
        Unknown

    };

    /// <summary>
    /// �豸(����,������,·����,����ǽ,���㽻����,���㽻����)
    /// </summary>
    public class Device : PanelTemplate
    {

        /// <summary>
        /// �������
        /// </summary>
        public Device()
        {

        }

        /*private int _index;
        /// <summary>
        /// �豸������
        /// </summary>
        public int Index
        {

            get { return _index; }
            set { _index = value; }

        }

        private string _name;
        /// <summary>
        /// �豸����
        /// </summary>
        public string Name
        {

            get { return _name; }
            set { _name = value; }

        }*/

        private Box _instance;
        /// <summary>
        /// �豸ʵ�������Ա���豸���и���״̬���ơ�
        /// </summary>
        public Box Instance
        {

            get { return _instance; }
            set { _instance = value; }

        }

        private DeviceType _type;
        /// <summary>
        /// �豸����
        /// </summary>
        public DeviceType Type
        {

            get { return _type; }
            set { _type = value; }

        }

        private List<string> _iplist;
        /// <summary>
        /// �豸ip�б�
        /// </summary>
        public List<string> IPlist
        {

            get { return _iplist; }
            set { _iplist = value; }

        }

        private string _model;
        /// <summary>
        /// �豸�ͺ�
        /// </summary>
        public string Model
        {

            get { return _model; }
            set { _model = value; }

        }

        private DeviceStatus _status = DeviceStatus.Unknown;
        /// <summary>
        /// �豸״̬
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
                        //����
                        case DeviceStatus.Run:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.LightGreen), 1.0f);
                            break;
                        //�澯
                        case DeviceStatus.Alarm:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.Red), 1.0f);
                            break;
                        //����
                        case DeviceStatus.Test:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.Yellow), 1.0f);
                            break;
                        //ֹͣ
                        case DeviceStatus.Stop:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.DarkGray), 1.0f);
                            break;
                        //����
                        case DeviceStatus.Other:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.Blue), 1.0f);
                            break;
                        //δ֪
                        case DeviceStatus.Unknown:
                            this.Instance.Pen = new MindFusion.FlowChartX.Pen(Color.FromArgb(120, Color.DarkGray), 1.0f);
                            break;
                    }
                }
            }

        }

        /*private string _tooltip = string.Empty;
        /// <summary>
        /// �豸tooltip��Ϣ
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
    /// ����ͼ
    /// </summary>
    public class TopGraphics
    {

        //��ʾ����ͼ��FlowChart�ؼ�
        private FlowChart _document;
        //��ʾ��������ͼ�ĸ��ؼ�
        private Control _parent;
        //����ͼVdx�ļ�
        private string _vdx;
        //����ͼ�豸�б�
        private List<Device> _devices = new List<Device>();
        //��ǰѡ����豸
        private Device _selected;
        //�Ҽ���ݲ˵�
        private ContextMenuStrip _menuStrip = new ContextMenuStrip();

        /// <summary>
        /// �������
        /// </summary>
        public TopGraphics()
        {

            InitializeDocument();

        }

        /// <summary>
        /// �������
        /// </summary>
        /// <param name="Vdx">����ͼVdx�ļ�</param>
        /// <param name="Document">��ʾ����ͼ��FlowChart�ؼ�</param>
        public TopGraphics(string Vdx, FlowChart Document)
        {

            this.Document = Document;
            this.Vdx = Vdx;

        }

        /// <summary>
        /// �������
        /// </summary>
        /// <param name="Vdx">����ͼVdx�ļ�</param>
        /// <param name="Parent">��ʾ��������ͼ�ĸ��ؼ�</param>
        public TopGraphics(string Vdx, Control Parent)
            : this()
        {

            this.Parent = Parent;
            this.Vdx = Vdx;

        }

        /// <summary>
        /// ��ʾ����ͼ��FlowChart�ؼ�
        /// </summary>
        public FlowChart Document
        {

            get { return _document; }
            set { _document = value; }

        }

        /// <summary>
        /// ��ʾ��������ͼ�ĸ��ؼ�
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
        /// ����ͼvdx�ļ�
        /// </summary>
        public string Vdx
        {

            get { return _vdx; }
            set
            {
                _vdx = value;
                //��ʾ����ͼ
                ShowTopGraphics();
            }

        }

        /// <summary>
        /// ����ͼ�豸�б�
        /// </summary>
        public List<Device> Devices
        {

            get { return _devices; }
            set { _devices = value; }

        }

        /// <summary>
        /// ��ǰѡ����豸����
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
                        //����ѡ��״̬
                        DrawSelectedStatus(_selected.Instance.BoundingRect);
                    }
                }
            }

        }

        /// <summary>
        /// �Ҽ���ݲ˵�
        /// </summary>
        public ContextMenuStrip MenuStrip
        {

            get { return _menuStrip; }
            set { _menuStrip = value; }

        }

        /// <summary>
        /// ��ʼ��Document
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
            this._document.InplaceEditFont = new System.Drawing.Font("����", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
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
        /// Document����ƶ��¼�
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _document_MouseMove(object sender, MouseEventArgs e)
        {

            _caption = "���꣺ ";
            _caption += e.X.ToString().PadRight(5, ' ');
            _caption += e.Y.ToString().PadRight(5, ' ');

        }

        /// <summary>
        /// Document��굥���¼�
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _document_MouseClick(object sender, MouseEventArgs e)
        {

            /*//��ʾ�Ҽ��˵�
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
                        //���õ�ǰѡ���豸
                        this.Selected = device;
                        //��ʾ�Ҽ��˵�
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
        /// ����ѡ��״̬
        /// </summary>
        /// <param name="rec">��Ҫ���Ƶľ�������</param>
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
        /// ��ʾ����ͼ
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
