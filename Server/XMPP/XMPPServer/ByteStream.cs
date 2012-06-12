using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;

namespace Logistics
{
    namespace SubServer
    {
        public class ByteStream
        {
            //private string StreamID = null;
            private Socket m_Initiator = null;
            private Socket m_Target = null;

            //private long m_TransferSize = 0;
            //private long m_TransferCount = 0;

            private readonly int BUFFERSIZE = 1024;
            private byte[] m_ReadBuffer = null;

            Queue<Byte[]> m_WriteBuffer = null;

            private bool m_Sending = false;
            private bool m_Closing = false;

            public ByteStream()
            {
                m_Sending = false;
                m_Closing = false;

                m_ReadBuffer = new byte[BUFFERSIZE];
                m_WriteBuffer = new Queue<byte[]>();

            }

            public Socket Initiator
            {
                get
                {
                    return this.m_Initiator;
                }
                set
                {
                    this.m_Initiator = value;
                }
            }


            public Socket Target
            {
                get
                {
                    return this.m_Target;
                }
                set
                {
                    this.m_Target = value;
                }

            }

            //public long TransferSize
            //{
            //    get
            //    {
            //        return this.m_TransferSize;
            //    }
            //    set
            //    {
            //        this.m_TransferSize = value;
            //    }
            //}

            //public bool ActiveStream()
            //{
            //    //m_TransferCount = 0;
            //    m_Sending = false;
            //    m_Closing = false;
            //    try
            //    {
            //        if (this.m_Initiator != null && this.m_Initiator.Connected)
            //        {
            //            this.m_Initiator.BeginReceive(m_ReadBuffer, 0, BUFFERSIZE, 0, new AsyncCallback(ReadStart), null);
            //            return true;
            //        }
            //        else
            //        {
            //            return false;
            //        }
            //    }
            //    catch (Exception ex)
            //    {
            //        Console.WriteLine(ex.Message);
            //        return false;
            //    }
            //}

            public bool IsValidByteStream()
            {
                if (this.m_Initiator != null && this.m_Initiator.Connected
                        && this.m_Target != null && this.m_Target.Connected)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            public void ActiveByteStream()
            {
                //m_TransferCount = 0;
                try
                {
                    int len = 0;
                    while ((len = this.m_Initiator.Receive(this.m_ReadBuffer, BUFFERSIZE, SocketFlags.None)) > 0)
                    {
                        this.m_Target.Send(this.m_ReadBuffer, len, SocketFlags.None);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
                finally
                {
                    DisableByteStream();
                }
            }

            public void DisableByteStream()
            {
                if (this.m_Initiator != null)
                {
                    if (this.m_Initiator.Connected)
                    {
                        this.m_Initiator.Shutdown(SocketShutdown.Both);
                        this.m_Initiator.Close();
                    }
                }

                if (this.m_Target != null)
                {
                    if (this.m_Target.Connected)
                    {
                        this.m_Target.Shutdown(SocketShutdown.Both);
                        this.m_Target.Close();
                    }
                }
            }


            public void ReadStart(IAsyncResult ar)
            {
                // Retrieve the state object and the handler socket
                // from the asynchronous state object

                // Read data from the client socket. 
                int bytesRead = m_Initiator.EndReceive(ar);

                if (bytesRead > 0)
                {
                    Byte[] buffer = null;
                    buffer = new byte[bytesRead];
                    Buffer.BlockCopy(m_ReadBuffer, 0, buffer, 0, bytesRead);

                    System.Threading.Monitor.Enter(m_WriteBuffer);
                    m_WriteBuffer.Enqueue(buffer);
                    System.Threading.Monitor.Exit(m_WriteBuffer);

                    WriteStart();

                    // Not all data received. Get more.
                    this.m_Initiator.BeginReceive(m_ReadBuffer, 0, BUFFERSIZE, 0, new AsyncCallback(ReadStart), null);
                }
                else
                {
                    this.m_Initiator.Shutdown(SocketShutdown.Both);
                    this.m_Initiator.Close();

                    m_Closing = true;
                }
            }

            private void WriteStart()
            {

                if (m_WriteBuffer.Count > 0 && !m_Sending)
                {
                    m_Sending = true;

                    System.Threading.Monitor.Enter(m_WriteBuffer);
                    Byte[] buffer = m_WriteBuffer.Dequeue();
                    System.Threading.Monitor.Exit(m_WriteBuffer);

                    m_Target.BeginSend(buffer, 0, buffer.Length, 0, new AsyncCallback(WriteEnd), null);
                }

            }

            private void WriteEnd(IAsyncResult ar)
            {
                try
                {
                    // Complete sending the data to the remote device.
                    int bytesSent = m_Target.EndSend(ar);

                    m_Sending = false;

                    if (this.m_WriteBuffer.Count > 0)
                    {
                        WriteStart();
                    }
                    else
                    {
                        if (m_Closing)
                        {
                            this.m_Target.Shutdown(SocketShutdown.Both);
                            this.m_Target.Close();
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }

        }
    }
}
