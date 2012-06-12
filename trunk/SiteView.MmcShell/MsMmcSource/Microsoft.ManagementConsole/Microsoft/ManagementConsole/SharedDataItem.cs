namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Advanced;
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.CompilerServices;

    public class SharedDataItem : SharedDataItemBase
    {
        private int _dataObjectId;
        private ISnapInPlatform _snapInPlatform;

        internal event SharedDataChangedEventHandler Changed;

        public SharedDataItem(string clipboardFormatId) : base(clipboardFormatId)
        {
        }

        public override byte[] GetData()
        {
            if (this._snapInPlatform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.AdvancedSharedDataItemNotInitialized));
            }
            ReadDataCommand command = new ReadDataCommand();
            command.DataObjectId = this._dataObjectId;
            command.ClipboardFormatId = base.ClipboardFormatId;
            try
            {
                ReadDataCommandResult result = (ReadDataCommandResult) this._snapInPlatform.ProcessCommand(command);
                base.InternalSetData(result.Data.GetValue());
            }
            catch (Microsoft.ManagementConsole.Internal.PrimarySnapInDataException exception)
            {
                throw new Microsoft.ManagementConsole.Advanced.PrimarySnapInDataException(exception.Message, exception);
            }
            return base.GetData();
        }

        internal void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this, new SharedDataChangedEventArgs(SharedDataChangeType.Modify, this));
            }
        }

        public void RequestDataUpdate(byte[] value)
        {
            if (this._snapInPlatform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.AdvancedSharedDataItemNotInitialized));
            }
            ClipboardData data = new ClipboardData();
            data.ClipboardFormatId = base.ClipboardFormatId;
            data.SetValue(value);
            RequestWriteDataCommand command = new RequestWriteDataCommand();
            command.DataObjectId = this._dataObjectId;
            command.RequestedValue = data;
            try
            {
                this._snapInPlatform.ProcessCommand(command);
            }
            catch (Microsoft.ManagementConsole.Internal.PrimarySnapInDataException exception)
            {
                throw new Microsoft.ManagementConsole.Advanced.PrimarySnapInDataException(exception.Message, exception);
            }
        }

        internal void SetSnapInPlatform(ISnapInPlatform snapInPlatform, int dataObjectId)
        {
            this._snapInPlatform = snapInPlatform;
            this._dataObjectId = dataObjectId;
        }

        internal delegate void SharedDataChangedEventHandler(object sender, SharedDataChangedEventArgs e);
    }
}

