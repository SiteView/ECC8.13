namespace Microsoft.ManagementConsole.Internal
{
    using Microsoft.ManagementConsole;
    using System;
    using System.Collections.Specialized;
    using System.ComponentModel;
    using System.Configuration;
    using System.Diagnostics;
    using System.Globalization;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public static class GlobalConfiguration
    {
        [EditorBrowsable(EditorBrowsableState.Never)]
        public static class SnapInHostingOptions
        {
            private const string _assertOnUnhandledExceptionsKey = "assertOnUnhandledExceptions";
            private const string _hangIntervalKey = "hangInterval";
            private const string _marshalByRefObjectLeaseTime = "marshalByRefObjectLeaseTime";
            private const string _marshalByRefObjectRenewOnCallTime = "marshalByRefObjectRenewOnCallTime";
            private const string _marshalByRefObjectSponsorshipTimeout = "marshalByRefObjectSponsorshipTimeout";
            private const string _modalLoopEndNowPromptInterval = "modalLoopEndNowPromptInterval";
            private static NameValueCollection _section;
            private const string _waitDialogDelayKey = "waitDialogDelay";
            public static readonly TimeSpan MaxWaitDialogDelay = new TimeSpan(0, 0, 20);

            private static NameValueCollection GetSection()
            {
                if (_section == null)
                {
                    try
                    {
                        _section = ConfigurationManager.AppSettings;
                        if (_section == null)
                        {
                            TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Information, 0, "mmc.exe.config: section <appSettings> does not exist");
                        }
                    }
                    catch (ConfigurationException exception)
                    {
                        TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 0, "mmc.exe.config: ConfigurationException thrown reading section appSettings. It should be declared as <appSettings>.  Exception message : {1}", new object[] { exception.Message });
                    }
                }
                return _section;
            }

            private static bool ReadBoolSetting(string settingKey, bool defaultValue)
            {
                bool flag = defaultValue;
                string s = ReadStringSetting(settingKey);
                if (s == null)
                {
                    return flag;
                }
                int result = 0;
                if (!int.TryParse(s, NumberStyles.None, CultureInfo.InvariantCulture, out result))
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 0, "mmc.exe.config: Key {0} with value {1} is not a valid int", new object[] { settingKey, s });
                }
                return (result > 0);
            }

            private static string ReadStringSetting(string settingKey)
            {
                string str = null;
                NameValueCollection section = GetSection();
                if (section != null)
                {
                    str = section[settingKey];
                    if (str == null)
                    {
                        TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Information, 0, "mmc.exe.config: Key {0} not defined for section <appSettings>", new object[] { settingKey });
                    }
                }
                return str;
            }

            private static TimeSpan ReadTimeSpanSetting(string settingKey, TimeSpan defaultValue, TimeSpan minValue, TimeSpan maxValue)
            {
                TimeSpan span = defaultValue;
                string s = ReadStringSetting(settingKey);
                if (s == null)
                {
                    return span;
                }
                int result = 0;
                if (!int.TryParse(s, NumberStyles.None, CultureInfo.InvariantCulture, out result))
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 0, "mmc.exe.config: Key {0} with value {1} is not a valid int", new object[] { settingKey, s });
                    return span;
                }
                TimeSpan span2 = TimeSpan.FromMilliseconds((double) result);
                if ((span2 < minValue) || (span2 > maxValue))
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 0, "mmc.exe.config: Key {0} with value {1} must be >= {2} and <= {3}", new object[] { settingKey, span2.ToString(), minValue.ToString(), maxValue.ToString() });
                    return span;
                }
                return span2;
            }

            public static bool AssertOnUnhandledExceptions
            {
                get
                {
                    return ReadBoolSetting("assertOnUnhandledExceptions", false);
                }
            }

            public static TimeSpan HangInterval
            {
                get
                {
                    return ReadTimeSpanSetting("hangInterval", new TimeSpan(0, 0, 20), new TimeSpan(0, 0, 5), new TimeSpan(0, 5, 0));
                }
            }

            public static TimeSpan MarshalByRefObjectLeaseTime
            {
                get
                {
                    return ReadTimeSpanSetting("marshalByRefObjectLeaseTime", new TimeSpan(0, 1, 0), new TimeSpan(0, 0, 5), new TimeSpan(0, 30, 0));
                }
            }

            public static TimeSpan MarshalByRefObjectRenewOnCallTime
            {
                get
                {
                    return ReadTimeSpanSetting("marshalByRefObjectRenewOnCallTime", new TimeSpan(0, 0, 2), new TimeSpan(0, 0, 0), new TimeSpan(0, 2, 0));
                }
            }

            public static TimeSpan MarshalByRefObjectSponsorshipTimeout
            {
                get
                {
                    return ReadTimeSpanSetting("marshalByRefObjectSponsorshipTimeout", new TimeSpan(0, 2, 0), new TimeSpan(0, 0, 5), new TimeSpan(0, 5, 0));
                }
            }

            public static TimeSpan ModalLoopEndNowPromptInterval
            {
                get
                {
                    return ReadTimeSpanSetting("modalLoopEndNowPromptInterval", new TimeSpan(0, 0, 20), new TimeSpan(0, 0, 5), new TimeSpan(0, 5, 0));
                }
            }

            public static TimeSpan WaitDialogDelay
            {
                get
                {
                    return ReadTimeSpanSetting("waitDialogDelay", new TimeSpan(0, 0, 5), new TimeSpan(0, 0, 0), MaxWaitDialogDelay);
                }
            }
        }
    }
}

