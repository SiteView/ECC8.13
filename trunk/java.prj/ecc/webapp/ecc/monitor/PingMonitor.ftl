<link rel="stylesheet" type="text/css" href="/crmimages/yui/build/fonts/fonts-min.css" />
<link rel="stylesheet" type="text/css" href="/crmimages/yui/build/datatable/assets/skins/sam/datatable.css" />
<script type="text/javascript" src="/crmimages/yui/build/yahoo-dom-event/yahoo-dom-event.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/dragdrop/dragdrop-min.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/element/element-beta-min.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/datasource/datasource-beta-min.js"></script>
<script type="text/javascript" src="/crmimages/yui/build/datatable/datatable-beta-min.js"></script>

<style type="text/css">
<!--
.STYLE1 {color: #FFFFFF}
-->
</style>

<table width="90%" border="0" cellspacing="1" cellpadding="1">
  <tr>
    <td colspan="4" bgcolor="#0066FF" scope="col"><span class="STYLE1">&nbsp;������Ϣ��</span></td>
  </tr>
  <tr>
    <th width="10%" scope="col">&nbsp;</th>
    <td width="15%" scope="col"><div align="right">�豸���ƣ�</div></td>
    <td width="70%" scope="col">${DeviceName}</td>
    <th width="5%" scope="col">&nbsp;</th>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td><div align="right">���Ƶ�ʣ�</div></td>
    <td><label>
      <input name="textfield" type="text" value="${frequency}" size="10" />
      <select name="select">
        <option>����</option>
        <option>��</option>
      </select>
    </label></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td><div align="right">��������⣺</div></td>
    <td><label>
      <input name="textfield2" type="text" value="${monitorTitle}�� ${DeviceName}" size="80" />
    </label></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td colspan="4" bgcolor="#0066FF" scope="row"><span class="STYLE1">&nbsp;����������</span></td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td valign="top"><div align="right">����</div></td>
    <td><label>
      <textarea name="textarea" cols="80" rows="4">${conditionError}</textarea>
      <input type="submit" name="Submit3" value="�༭" />
    </label></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td valign="top"><div align="right">Σ�գ�</div></td>
    <td><textarea name="textarea2" cols="80" rows="4">${conditionWarn}</textarea>
    <input type="submit" name="Submit32" value="�༭" /></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td valign="top"><div align="right">������</div></td>
    <td valign="top"><textarea name="textarea3" cols="80" rows="4">${conditionGood}</textarea>
    <input type="submit" name="Submit33" value="�༭" /></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td valign="top">&nbsp;</td>
    <td valign="top">&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td colspan="4" bgcolor="#0066FF" scope="row"><span class="STYLE1">&nbsp;�߼�ѡ�</span></td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td valign="top">&nbsp;</td>
    <td valign="top">&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td colspan="4" scope="row"><label>
      <div align="center">
        <input type="submit" name="Submit0" value="��һ��" />
        &nbsp;
        <input type="submit" name="Submit" value="���" />
        &nbsp;
        <input type="submit" name="Submit2" value="ȡ��" />
        &nbsp;
        <input type="submit" name="Submit22" value="��Ӳ�����" />
        &nbsp;
        <input type="submit" name="Submit23" value="���ñ���ȱʡֵ" />
      </div>
    </label></td>
  </tr>
</table>

