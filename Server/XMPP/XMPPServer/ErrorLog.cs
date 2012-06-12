using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
namespace Logistics
{
      namespace SubServer
      {
            public class ErrorLog
            {

                  public ErrorLog()
                  {
                  }

                  public void WriteFiles(string content)
                  {

                        try
                        {
                              FileStream fi = new FileStream(AppDomain.CurrentDomain.BaseDirectory + "\\cache.txt", FileMode.Append);
                              StreamWriter sw = new StreamWriter(fi, Encoding.UTF8);

                              sw.WriteLine(content);
                              sw.WriteLine("-------------------------------------------------------");

                              if (fi.Length >= (1024 * 1024 * 5))
                              {
                                    sw.Close();
                                    fi.Close();
                                    if (File.Exists(AppDomain.CurrentDomain.BaseDirectory + "\\cache.txt"))
                                    {
                                          File.Delete(AppDomain.CurrentDomain.BaseDirectory + "\\cache.txt");
                                    }
                                    return;
                              }
                              sw.Close();
                              fi.Close();
                        }
                        catch (Exception ex)
                        {

                        }
                  }

                  public string ReadFile()
                  {
                        try
                        {
                              FileStream fi = new FileStream(AppDomain.CurrentDomain.BaseDirectory + "\\Config.ini", FileMode.Open);
                              StreamReader sw = new StreamReader(fi, Encoding.UTF8);
                              string ReStr = sw.ReadLine();
                              sw.Close();
                              fi.Close();
                              return ReStr;
                        }
                        catch (Exception ex)
                        {
                              return "";
                        }
                  }
            }
      }
}
