namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public interface IRequestStatus
    {
        void ProcessResponse(RequestResponse response);
        void ReportProgress(int workProcessed, int totalWork, string statusText);
        void SetCompletionText(string completionText, bool isSuccess);

        bool CanCancel { get; set; }

        bool IsCancelExposed { get; }

        bool IsCancelSignaled { get; }

        Microsoft.ManagementConsole.Internal.RequestState RequestState { get; set; }

        string Title { get; set; }
    }
}

