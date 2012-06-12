using System;
using System.Net;
using System.Web;
using System.IO;
using System.Xml;

namespace SiteView.WindowsService.Common
{
	/// <summary>
	/// SmsSendWebRequest ��ժҪ˵����
	/// </summary>
	public class SmsSendWebRequest
	{
		public SmsSendWebRequest()
		{
			//
			// TODO: �ڴ˴���ӹ��캯���߼�
			//
		}

		/// <summary>
		/// ����
		/// </summary>
		string _context;
		public string context
		{
			get{return _context;}
			set{_context = value;}
		}

		/// <summary>
		/// �����ֻ�����
		/// </summary>
		string _MobileNumber;
		public string MobileNumber
		{
			get{return _MobileNumber;}
			set{_MobileNumber = value;}
		}

		public void WebRequestSendMessage()
		{
			try
			{
				Console.WriteLine("mafengstart");
				string filepath = SiteView.Enterprise.Reg.GetSubKey("RootPath_SC")+"/Configuration/Global.DgWebRequestAlertSmsSet.config";
				Console.WriteLine("filepath:"+filepath);
				if(!File.Exists(filepath)) throw(new ApplicationException("���������ļ�������!")); //�ж��ļ��Ƿ����
				XmlDocument dom = new XmlDocument();
				dom.Load(filepath);
				XmlNode smsnode = dom.SelectSingleNode("//item[@id='SmsSendSet']");
				string sUrl = smsnode.Attributes["url"].Value;
				string sSmallCode = smsnode.Attributes["smallCode"].Value;
				string sSrcMobile = smsnode.Attributes["srcMobile"].Value;
				string sLinkId = smsnode.Attributes["linkId"].Value;
				string sWorkFlage = smsnode.Attributes["workFlage"].Value;
				string sUser = smsnode.Attributes["user"].Value;
				string sPassword = smsnode.Attributes["password"].Value;

				System.Text.Encoding gb2312=System.Text.Encoding.GetEncoding("gb2312");
				string URL=sUrl+"smallCode="+sSmallCode+"&srcMobile="+sSrcMobile+"&destMobile="+MobileNumber+"&content="+HttpUtility.UrlEncode(context,gb2312)+"&linkId="+sLinkId+"&workFlage="+sWorkFlage+"&user="+sUser+"&password="+sPassword; 
				Console.WriteLine("URL:"+URL);
				WebRequest getweb=WebRequest.Create(URL);
				WebResponse resp=(HttpWebResponse)getweb.GetResponse(); 
				Console.WriteLine("resp:"+resp);
			}
			catch(Exception ex)
			{
				throw new Exception(ex.Message+"Send�r����͵�");
			}
			finally
			{
			}
		}
	}
}
