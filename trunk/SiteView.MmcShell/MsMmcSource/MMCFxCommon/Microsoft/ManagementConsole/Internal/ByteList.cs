namespace Microsoft.ManagementConsole.Internal
{
    using System;

    internal sealed class ByteList
    {
        private int _currentIndex;
        private byte[] _list = new byte[0x10];
        private const int _sizeThreshold = 0x1000;

        public void Add(byte item)
        {
            this.Grow(1);
            this._list[this._currentIndex] = item;
            this._currentIndex++;
        }

        public void AddRange(byte[] items)
        {
            this.Grow(items.Length);
            Array.Copy(items, 0, this._list, this._currentIndex, items.Length);
            this._currentIndex += items.Length;
        }

        private void Grow(int delta)
        {
            int num = this._currentIndex + delta;
            if (num > this._list.Length)
            {
                int length = this._list.Length;
                while (num > length)
                {
                    if (length > 0x1000)
                    {
                        length += 0x1000;
                    }
                    else
                    {
                        length *= 2;
                    }
                }
                byte[] destinationArray = new byte[length];
                Array.Copy(this._list, 0, destinationArray, 0, this._list.Length);
                this._list = destinationArray;
            }
        }

        public byte[] ToArray()
        {
            byte[] destinationArray = new byte[this._currentIndex];
            Array.Copy(this._list, 0, destinationArray, 0, this._currentIndex);
            return destinationArray;
        }
    }
}

