using System;
using System.Collections.Generic;
using System.Text;

using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Logistics
{
    namespace SubServer
    {
        public delegate void Socket5Handler(Socket5 sender, bool result);

        public class Socket5
        {
            private readonly int BUFFERSIZE = 1024;
            private byte[] m_ReadBuffer = null;

            private Socket objSocket = null;
            private string strBindAddress = null;
            private string strBindPort = null;

            private event Socket5Handler socket5Handler = null;

            public Socket5()
            {
                objSocket = null;
                strBindAddress = null;
                strBindPort = null;

                m_ReadBuffer = new byte[BUFFERSIZE];
            }

            public Socket5(Socket socket)
                : this()
            {
                objSocket = socket;

            }

            public void Start()
            {
                if (this.objSocket == null)
                {
                    return;
                }

                try
                {
                    //***********************************
                    this.objSocket.BeginReceive(m_ReadBuffer, 0, BUFFERSIZE, 0, new AsyncCallback(ClientRequest1), null);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }

            }

            public void Stop()
            {
                if (this.objSocket == null)
                {
                    return;
                }

                try
                {
                    //***********************************
                    if (this.objSocket.Connected)
                    {
                        this.objSocket.Shutdown(SocketShutdown.Both);
                        this.objSocket.Close();
                    }

                    this.objSocket = null;
                 
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }

            public event Socket5Handler OnSocket5Processed
            {
                add
                {
                    socket5Handler += value;
                }
                remove
                {
                    socket5Handler -= value;
                }
            }

            public Socket SocketConnection
            {
                get
                {
                    return this.objSocket;
                }
            }

            public string BindAddress
            {
                get
                {
                    return this.strBindAddress;
                }
            }

            public string BindPort
            {
                get
                {
                    return this.strBindPort;
                }
            }

            private void ClientRequest1(IAsyncResult ar)
            {
                try
                {
                    // Retrieve the state object and the handler socket
                    // from the asynchronous state object

                    // Read data from the client socket. 
                    int bytesRead = objSocket.EndReceive(ar);
                    
                    if (bytesRead > 0)
                    {
                        // Not all data received. Get more.

                        if (m_ReadBuffer[0] != 5)
                        {
                            throw new Exception("wrong proxy version");
                        }

                        if (m_ReadBuffer[1] != 1)
                        {

                        }

                        if (m_ReadBuffer[2] != 0)
                        {

                        }

                        Byte[] buffer = new byte[2];
                        buffer[0] = 5;
                        buffer[1] = 0;
                        objSocket.BeginSend(buffer, 0, buffer.Length, 0, new AsyncCallback(ServerRepsone1), null);
                    }
                    else
                    {
                        objSocket.Shutdown(SocketShutdown.Both);
                        objSocket.Close();
                    }
                }
                catch (SocketException ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }

            private void ServerRepsone1(IAsyncResult ar)
            {
                try
                {
                    objSocket.EndSend(ar);
                    // setup the next receive callback
                    objSocket.BeginReceive(m_ReadBuffer, 0, BUFFERSIZE, SocketFlags.None, new AsyncCallback(ClientRequest2), null);
                }
                catch (Exception ex)
                {
                    //    ProtocolComplete(e);
                    //    return;
                    Console.WriteLine(ex.Message);
                }
            }

            private void ClientRequest2(IAsyncResult ar)
            {
                try
                {
                    // Receive 3 byte Auth
                    int rec = objSocket.EndReceive(ar);

                    if (rec > 0)
                    {
                        // VER
                        if (m_ReadBuffer[0] != 0x05)
                        {
                            throw new Exception("wrong proxy version");
                        }

                        if (m_ReadBuffer[1] != 0x01)
                        {

                        }

                        if (m_ReadBuffer[2] != 0x00)
                        {

                        }

                        if (m_ReadBuffer[3] != 0x03)
                        {

                        }

                        int nlen = m_ReadBuffer[4];

                        this.strBindAddress = Encoding.UTF8.GetString(m_ReadBuffer, 5, nlen);

                        Console.WriteLine("Key:-->" + this.strBindAddress);

                        this.strBindPort = m_ReadBuffer[5 + nlen].ToString();

                        int end = m_ReadBuffer[6 + nlen];

                        byte[] buffer = new byte[2];
                        buffer[0] = 0x05;
                        buffer[1] = 0x00;

                        objSocket.BeginSend(buffer, 0, buffer.Length, SocketFlags.None, new AsyncCallback(ServerRepsone2), null);
                    }
                    else
                    {

                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }

            private void ServerRepsone2(IAsyncResult ar)
            {
                try
                {
                    objSocket.EndSend(ar);

                    if (this.socket5Handler != null)
                    {
                        this.socket5Handler(this, true);
                    }

                }
                catch (Exception ex)
                {
                    //    ProtocolComplete(e);
                    //    return;
                    Console.WriteLine(ex.Message);
                }
            }
        }
    }
}