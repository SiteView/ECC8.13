/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Page;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class healthPage extends com.dragonflow.Page.CGI {

    public healthPage() {
    }

    public void printBody() throws Exception {
        for (int i = 0; i < 2; i ++) {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup
                    .currentSiteView();
            jgl.Array array = siteviewgroup.getRawElements();
            boolean flag = false;
            int j = 0;
            while (array != null && j < array.size()) {
                Object obj = array.at(j);
                if ((obj instanceof com.dragonflow.SiteView.MonitorGroup)
                        && ((com.dragonflow.SiteView.MonitorGroup) obj)
                                .isTopLevelGroup()
                        && ((com.dragonflow.SiteView.MonitorGroup) obj)
                                .isHealthGroup()) {
                    ((com.dragonflow.SiteView.MonitorGroup) obj).printPage(
                            outputStream, request, true);
                    flag = true;
                    break;
                }
                j++;
            } 
            
            if (flag) {
                break;
            }
            com.dragonflow.SiteView.Health.getHealth();
            com.dragonflow.SiteView.Health.createHealthGroup();
            com.dragonflow.Api.APISiteView.forceConfigurationRefresh();
        } 
    }
}
