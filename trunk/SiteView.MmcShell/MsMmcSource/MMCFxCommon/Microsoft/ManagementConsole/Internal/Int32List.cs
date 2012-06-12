namespace Microsoft.ManagementConsole.Internal
{
    using System;

    internal sealed class Int32List
    {
        private int _currentIndex;
        private int[] _list = new int[0x10];
        private const int _sizeThreshold = 0x1000;

        public void Add(int item)
        {
            this.Grow(1);
            this._list[this._currentIndex] = item;
            this._currentIndex++;
        }

        public void AddRange(int[] items)
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
                int[] destinationArray = new int[length];
                Array.Copy(this._list, 0, destinationArray, 0, this._list.Length);
                this._list = destinationArray;
            }
        }

        public int[] ToArray()
        {
            int[] destinationArray = new int[this._currentIndex];
            Array.Copy(this._list, 0, destinationArray, 0, this._currentIndex);
            return destinationArray;
        }
    }
}

