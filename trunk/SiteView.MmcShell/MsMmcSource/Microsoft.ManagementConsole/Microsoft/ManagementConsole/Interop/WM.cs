namespace Microsoft.ManagementConsole.Interop
{
    using System;

    internal enum WM : uint
    {
        ACTIVATEFIRSTCONTROL = 0x465,
        ACTIVATELASTCONTROL = 0x466,
        CHANGEUISTATE = 0x127,
        CLOSE = 0x10,
        COMMAND = 0x111,
        CREATE = 1,
        CUSTOMSETACTIVE = 0x467,
        DESTROY = 2,
        ERASEBKGND = 20,
        INITDIALOG = 0x110,
        KEYFIRST = 0x100,
        KEYLAST = 0x109,
        MOUSEACTIVATE = 0x21,
        MOUSEFIRST = 0x200,
        MOUSELAST = 0x20d,
        MOVE = 3,
        NCMOUSEFIRST = 160,
        NCMOUSELAST = 0xad,
        NOTIFY = 0x4e,
        PAINT = 15,
        QUERYUISTATE = 0x129,
        SHOWWINDOW = 0x18,
        SIZE = 5,
        SYSCOMMAND = 0x112
    }
}

