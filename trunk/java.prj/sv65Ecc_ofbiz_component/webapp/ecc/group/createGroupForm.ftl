<form method="post"  action="submitAddGroup"  class="basic-form" onSubmit="javascript:submitFormDisableSubmits(this)">
<INPUT TYPE=HIDDEN NAME=groupId VALUE="${parameters.groupId?if_exists}">

<div id="_G41_"><table cellspacing="0" class="basic-table">

  <tr>
   <td class="label">${Static["com.dragonflow.SiteView.Group"].pName.getLabel()}</td>
   <td colspan="4"><input type="text" name="_name" size="50"/>
   <span class="tooltip">
	${Static["com.dragonflow.SiteView.Group"].pName.getDescription()}
	</span>
   </td>
  </tr>

  <tr>
   <td class="label">&nbsp;</td>
   <td><input type="submit" class="buttontext" name="submitButton" value="${uiLabelMap.CommonSave}"/></td>
   <td class="label"></td>
   <td><a class="buttontext" href="machineList">${uiLabelMap.CommonCancel}</a></td>
  </tr>
  
  <tr>
   <td class="label">${Static["com.dragonflow.SiteView.Group"].pDescription.getLabel()}</td>
   <td colspan="4"><TEXTAREA name=_description rows=4 cols=70></TEXTAREA>
   <span class="tooltip">
	${Static["com.dragonflow.SiteView.Group"].pDescription.getDescription()}
	</span>
   </td>
  </tr>

  <#assign useTree = Static["com.dragonflow.Page.treeControl"].useTree()>
  <#if useTree>
	  <tr>
	   <td class="label">${Static["com.dragonflow.SiteView.Group"].pDependsOn.getLabel()}</td>
	   <td colspan="4"><select size=1 name=_dependsOn>
	   </select>
	   <span class="tooltip">
			${Static["com.dragonflow.SiteView.Group"].pDependsOn.getDescription()}
		</span>
	   </td>
	  </tr>
  <#else>
	  <tr>
	   <td class="label">${Static["com.dragonflow.SiteView.Group"].pDependsOn.getLabel()}</td>
	   <td colspan="4"><select size=1 name=_dependsOn>
   		${Static["com.dragonflow.Page.groupPage"].getOptionsHTML(Static["com.dragonflow.SiteView.Group"].getScalarValues(Static["com.dragonflow.SiteView.Group"].pDependsOn,parameters.groupId?if_exists), parameters._method?if_exists)}
	   </select>
	   <span class="tooltip">
		${Static["com.dragonflow.SiteView.Group"].pDependsOn.getDescription()}
		</span>
	   </td>
	  </tr>
  </#if>

	  <tr>
	   <td class="label">${Static["com.dragonflow.SiteView.Group"].pDependsCondition.getLabel()}</td>
	   <td colspan="4"><select size=1 name=_dependsCondition>
   		${Static["com.dragonflow.Page.groupPage"].getOptionsHTML(Static["com.dragonflow.SiteView.Group"].getScalarValues(Static["com.dragonflow.SiteView.Group"].pDependsCondition,parameters.groupId?if_exists), parameters._method?if_exists)}
	   </select>
	   <span class="tooltip">
		${Static["com.dragonflow.SiteView.Group"].pDependsCondition.getDescription()}
		</span>
	   </td>
	  </tr>
 
	  <tr>
	   <td class="label">${Static["com.dragonflow.SiteView.Group"].pFrequency.getLabel()}</td>
	   <td colspan="4"><input type="text" name="_frequency" size=5 maxlength=4/><select name=_frequencyUnits size=1><OPTION >seconds<OPTION SELECTED>minutes<OPTION >hours<OPTION >days</SELECT>
	   <span class="tooltip">
		${Static["com.dragonflow.SiteView.Group"].pFrequency.getDescription()}
		</span>
	   </td>
	  </tr>
 
 </table>
</div>


</form>
