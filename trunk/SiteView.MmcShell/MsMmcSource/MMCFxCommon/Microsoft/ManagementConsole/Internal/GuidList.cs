namespace Microsoft.ManagementConsole.Internal
{
    using System;

    internal sealed class GuidList
    {
        private int _currentIndex;
        private Guid[] _list = new Guid[0x10];
        private const int _sizeThreshold = 0x1000;

        public void Add(Guid item)
        {
            this.Grow(1);
            this._list[this._currentIndex] = item;
            this._currentIndex++;
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
                Guid[] destinationArray = new Guid[length];
                Array.Copy(this._list, 0, destinationArray, 0, this._list.Length);
                this._list = destinationArray;
            }
        }

        public int IndexOf(Guid item)
        {
            return Array.IndexOf<Guid>(this._list, item, 0, this._currentIndex);
        }

        public Guid[] ToArray()
        {
            Guid[] destinationArray = new Guid[this._currentIndex];
            Array.Copy(this._list, 0, destinationArray, 0, this._currentIndex);
            return destinationArray;
        }

        public int Count
        {
            get
            {
                return this._currentIndex;
            }
        }
    }
}

