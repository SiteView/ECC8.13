using System;
using System.Text;
using System.Collections;
using System.Security.Cryptography;

using agsXMPP;
using agsXMPP.util;

namespace Logistics
{
    namespace SubServer
    {
        /// <summary>
        /// Summary description for SessionId.
        /// </summary>
        class SessionID
        {
            // Lenght of the Session ID on bytes,
            // 4 bytes equaly 8 chars
            // 16^8 possibilites for the session IDs (4.294.967.296)
            // This should be unique enough
            private static int m_lenght = 4;

            public static string CreateNewId()
            {
                RandomNumberGenerator RNG = RandomNumberGenerator.Create();
                byte[] buf = new byte[m_lenght];
                RNG.GetBytes(buf);

                return agsXMPP.util.Hash.HexToString(buf);
            }

        }
    }
}
